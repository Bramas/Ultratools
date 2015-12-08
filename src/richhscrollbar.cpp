/* Copyright (c) 2015 Quentin Bramas
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

 #include "richhscrollbar.h"

#include "uLyrics.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>
#include <QDebug>

const int RichHScrollBar::HBorder = 5;
const int RichHScrollBar::VBorder = 5;
const int RichHScrollBar::MinVisible = 10;

RichHScrollBar::RichHScrollBar(QWidget *parent) : QAbstractSlider(parent), _lyrics(0)
{
    this->setOrientation(Qt::Horizontal);
    this->setMinimumHeight(52);
    this->setMouseTracking(true);
    _mousePressed = false;
    _left = _right = 0;
    updateLeftRight();
    _overType = OverNothing;

}

void RichHScrollBar::paintEvent(QPaintEvent *event){
    QPainter painter(this);



    painter.setBrush(QBrush(QColor(200,200,200)));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,_left, 50);
    painter.drawRect(_right,0, width() - _right, 50);

    if(_overType == OverLeft)
    {
        painter.setPen(QPen(QColor(100,100,100)));
        painter.setBrush(QBrush(QColor(100,100,100)));
    }
    else
    {
        painter.setPen(QPen(QColor(200,200,200)));
        painter.setBrush(QBrush(QColor(200,200,200)));
    }
    painter.drawRect(_left - HBorder, 0, HBorder, 50);
    painter.setPen(QPen(QColor(100,100,100)));
    painter.setBrush(QBrush(QColor(100,100,100)));
    painter.drawRect(_left-1, 0, 1, 50);
    if(_overType == OverRight)
    {
        painter.setPen(QPen(QColor(100,100,100)));
        painter.setBrush(QBrush(QColor(100,100,100)));
    }
    else
    {
        painter.setPen(QPen(QColor(200,200,200)));
        painter.setBrush(QBrush(QColor(200,200,200)));
    }
    painter.drawRect(_right, 0, HBorder, 50);
    painter.setPen(QPen(QColor(100,100,100)));
    painter.setBrush(QBrush(QColor(100,100,100)));
    painter.drawRect(_right, 0, 1, 50);

    if(_overType == OverCenter)
    {
        painter.setBrush(QBrush(QColor(220,220,220)));
        painter.drawRect(_left, 0, _right - _left, 50);
    }


    if(!_lyrics)
        return;

    qreal xGap = _lyrics->timeToBeat(_lyrics->getGap());
    int yfactor = qMax(1, (height() - 2 * VBorder) / 12);
    qreal xfactor;

    if (useableWidth() > 0 && total() > 0)
    {
        xfactor = useableWidth() / (qreal)total();
    }
    else
    {
        xfactor = 0;
    }

    painter.setPen(QPen(QColor(0,173,232,170)));
    painter.setBrush(QBrush(QColor(0,173,232,170)));
    foreach(const Word & w, _lyrics->words())
    {
        if(w.isSeparator())
            continue; //   ignore separators

        qreal x = HBorder + ((xGap + w.getTime()) - minimum()) * xfactor;
        int p = w.getPitch() % 12;
        qreal y = (11 - (p < 0 ? p + 12 : p)) * yfactor + VBorder;
        qreal length = w.getLength() * xfactor;
        painter.drawRect(x, y, length, yfactor);
    }
}

void RichHScrollBar::mousePressEvent(QMouseEvent *event)
{
    mouseMoveEvent(event);
    _mousePressed = true;
    _mousePressPoint = event->pos();
    _mousePressSliderValue = this->value();
    _mousePressPageStep = this->pageStep();
    if(_overType == OverCenter && event->button() == Qt::RightButton)
        _overType = OverScaleCenter;
}

void RichHScrollBar::mouseReleaseEvent(QMouseEvent *event)
{
    _mousePressed = false;
}

void RichHScrollBar::mouseMoveEvent(QMouseEvent *event)
{
    if(_mousePressed)
    {
        QPoint diff = event->pos() - _mousePressPoint;
        qreal valueDiff = 0;
        int v;

        if(useableWidth() > 0)
        {
            valueDiff = diff.x() * total() / useableWidth();
        }
        switch(_overType)
        {
        case OverCenter:
            v = _mousePressSliderValue + valueDiff;
            setValue(v);
            this->setCursor(Qt::ClosedHandCursor);
            break;
        case OverScaleCenter:
        {
            qreal diff = event->y() - _mousePressPoint.y();
            qreal weight;

            if (useableWidth() > 0 && _mousePressPageStep > 0)
            {
                weight = ((qreal)(_mousePressPoint.x() - HBorder) * total() + minimum()) / useableWidth();
                weight = (weight - _mousePressSliderValue) / _mousePressPageStep;
            }
            else
            {
                weight = 0.5;
            }

            if(diff > 0) // zoomOut
            {
                diff /= 0.1;
            }
            else
            {
                diff /= 100.0/_mousePressPageStep;
            }
            if(_mousePressPageStep + diff < 15)
            {
                diff = 15 - _mousePressPageStep;
            }
            setViewport(_mousePressSliderValue - diff * weight, _mousePressPageStep + diff);
            break;
        }
        case OverRight:
            changePageStep(_mousePressPageStep + valueDiff);
            this->setCursor(Qt::SizeHorCursor);
            break;
        case OverLeft:
            v = _mousePressSliderValue + valueDiff;
            v = qMin(v, _mousePressSliderValue + _mousePressPageStep - MinVisible);
            setViewport(v, _mousePressSliderValue - v + _mousePressPageStep);
            this->setCursor(Qt::SizeHorCursor);
            break;
        }

        return;
    }
    int beforeOverType = _overType;
    if(abs(event->pos().x() +2.5 - _left) <= 5)
    {
        this->setCursor(Qt::SizeHorCursor);
        _overType = OverLeft;
    }
    else
    if(abs(event->pos().x() - 2.5 - _right) <= 5)
    {
        this->setCursor(Qt::SizeHorCursor);
        _overType = OverRight;
    }
    else
    if(event->pos().x() < _right && event->pos().x() > _left)
    {
        this->setCursor(Qt::OpenHandCursor);
        _overType = OverCenter;
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
        _overType = OverNothing;
    }
    if(beforeOverType != _overType)
        update();
}

void RichHScrollBar::updateLeftRight()
{
    int w = total();

    if(w > 0)
    {
        _left = HBorder + (value() - minimum()) * useableWidth() / w;
        _right = HBorder + (value() - minimum() + pageStep()) * useableWidth() / w;
    }
    else
    {
        _left = HBorder;
        _right = width() - HBorder;
    }
}

void RichHScrollBar::setTotalMaximum(int m)
{
    int w = m - minimum();

    if(pageStep() > w)
    {
        changePageStep(w);
        m = minimum() + pageStep();
    }
    setMaximum(m - pageStep());
}

void RichHScrollBar::setViewport(int v, int p)
{
    if (v < value())
        setValue(v);
    changePageStep(p);
    if (v > value())
        setValue(v);
}

void RichHScrollBar::changePageStep(int p)
{
    p = qMax(p, MinVisible);
    p = qMin(p, maximum() - value() + pageStep());
    if(p != pageStep())
    {
        setMaximum(maximum() + pageStep() - p);
        setPageStep(p);
    }
}

void RichHScrollBar::sliderChange(SliderChange change)
{
    updateLeftRight();
    if (change == QAbstractSlider::SliderStepsChange)
    {
        emit pageStepChanged(pageStep());
    }
    update();
}
