#include "richhscrollbar.h"

#include "uLyrics.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>
#include <QDebug>

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
    painter.drawRect(_left-5, 0, 5, 50);
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
    painter.drawRect(_right, 0, 5, 50);
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

    qreal xGap = _lyrics->timeToBeat(_lyrics->getGap()) * width() / (qreal)maximum();

    painter.setPen(QPen(QColor(0,173,232,170)));
    painter.setBrush(QBrush(QColor(0,173,232,170)));
    foreach(const Word & w, _lyrics->words())
    {
        if(w.isSeparator())
            continue; //   ignore separators

        qreal x = 5 + xGap + w.getTime() * (width() - 10) / (qreal)maximum();
        qreal y = (w.getPitch() % 12) * 2 + 5;
        qreal length = w.getLength() * (width() - 10) / (qreal)maximum();
        painter.drawRect(x, y, length, 2);
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
        qreal valueDiff = diff.x()*maximum()/width();
        int v;
        switch(_overType)
        {
        case OverCenter:
            v = _mousePressSliderValue + valueDiff;
            v = qMin(v, maximum()-pageStep());
            v = qMax(v, 0);
            this->setValue(v);
            this->setCursor(Qt::ClosedHandCursor);
            break;
        case OverScaleCenter:
        {
            int clickValue = _mousePressPoint.x()*maximum()/width();
            qreal diff = event->y() - _mousePressPoint.y();

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
            setValue(_mousePressSliderValue - diff * (clickValue - _mousePressSliderValue) / _mousePressPageStep);
            setPageStep(_mousePressPageStep + diff);
            break;
        }
        case OverRight:
            v = _mousePressPageStep + valueDiff;
            v = qMin(v, maximum()-value());
            v = qMax(v, 20);
            this->setPageStep(v);
            this->setCursor(Qt::SizeHorCursor);
            break;
        case OverLeft:
            v = _mousePressSliderValue + valueDiff;
            v = qMin(v, _mousePressSliderValue + _mousePressPageStep - 20);
            v = qMax(v, 0);
            this->setValue(v);
            this->setPageStep(_mousePressSliderValue - v + _mousePressPageStep);
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
    if(value() > maximum() - 10)
        setValue(maximum() - 10);
    if(value() + pageStep() > maximum())
        setPageStep(maximum() - value());

    _left = 5 + this->value()*(width() - 10)/maximum();
    _right = _left + this->pageStep()*(width() - 10)/maximum();
}

void RichHScrollBar::setMaximum(int m)
{
    m = qMax(10, m);
    QAbstractSlider::setMaximum(m);
    updateLeftRight();
    update();
}

void RichHScrollBar::setValue(int v)
{
    v = qMax(0, v);
    QAbstractSlider::setValue(v);
    updateLeftRight();
    update();
}
void RichHScrollBar::setPageStep(int p)
{
    p = p < 10 ? 10 : p;
    QAbstractSlider::setPageStep(p);
    updateLeftRight();
    emit pageStepChanged(pageStep());
    update();
}
