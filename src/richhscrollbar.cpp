#include "richhscrollbar.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QMouseEvent>

RichHScrollBar::RichHScrollBar(QWidget *parent) : QAbstractSlider(parent)
{
    this->setOrientation(Qt::Horizontal);
    this->setMinimumHeight(22);
    this->setMouseTracking(true);
    _mousePressed = false;
}

void RichHScrollBar::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    //painter.setBrush(QBrush(QColor(0,0,0)));
    painter.setPen(QPen(QColor(0,0,0)));
    painter.drawRect(this->value(), 0, this->pageStep(), 20);
}

void RichHScrollBar::mousePressEvent(QMouseEvent *event)
{
    _mousePressed = true;
    _mousePressPoint = event->pos();
    _mousePressSliderValue = this->value();
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
        this->setValue(_mousePressSliderValue + diff.x());
    }
}
