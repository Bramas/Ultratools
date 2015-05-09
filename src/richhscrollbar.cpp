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

    //painter.setBrush(QBrush(QColor(0,0,0)));
    painter.setPen(QPen(QColor(0,0,0)));
    painter.drawRect(_left, 0, _right - _left, 50);

    if(!_lyrics)
        return;

    qreal xGap = _lyrics->timeToBeat(_lyrics->getGap()) * width() / (qreal)maximum();

    painter.setPen(QPen(QColor(0,173,232,170)));
    foreach(const Word & w, _lyrics->words())
    {
        if(w.isSeparator())
            continue; //   ignore separators

        qreal x = xGap + w.getTime() * width() / (qreal)maximum();
        qreal y = (w.getPitch() % 12) * 2 + 5;
        qreal length = w.getLength() * width() / (qreal)maximum();
        painter.drawRect(x, y, length, 2);
    }
}

void RichHScrollBar::mousePressEvent(QMouseEvent *event)
{
    _mousePressed = true;
    _mousePressPoint = event->pos();
    _mousePressSliderValue = this->value();
    _mousePressPageStep = this->pageStep();
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
            break;
        case OverRight:
            v = _mousePressPageStep + valueDiff;
            v = qMin(v, maximum()-value());
            v = qMax(v, 20);
            this->setPageStep(v);
            emit pageStepChanged(pageStep());
            break;
        case OverLeft:
            v = _mousePressSliderValue + valueDiff;
            v = qMin(v, _mousePressSliderValue + _mousePressPageStep - 20);
            v = qMax(v, 0);
            this->setValue(v);
            this->setPageStep(_mousePressSliderValue - v + _mousePressPageStep);
            emit pageStepChanged(pageStep());
            break;
        }

        return;
    }
    if(abs(event->pos().x() + 1 - _left) < 4)
    {
        this->setCursor(Qt::SizeHorCursor);
        _overType = OverLeft;
    }
    else
    if(abs(event->pos().x() - 1 - _right) < 4)
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
}

void RichHScrollBar::updateLeftRight()
{
    _left = this->value()*width()/maximum();
    _right = _left + this->pageStep()*width()/maximum();
}

void RichHScrollBar::setMaximum(int m)
{
    QAbstractSlider::setMaximum(m);
    updateLeftRight();
}

void RichHScrollBar::setValue(int v)
{
    QAbstractSlider::setValue(v);
    updateLeftRight();
}
void RichHScrollBar::setPageStep(int p)
{
    QAbstractSlider::setPageStep(p);
    updateLeftRight();
}
