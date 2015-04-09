#include "uWidgetSongData.h"
#include "uShowSentenceWydget.h"
#include <QPainter>
#include <QWheelEvent>
#include <QPointF>
#include <QPolygonF>
#include <QDebug>
#include <QElapsedTimer>
#include <math.h>

WidgetSongData::WidgetSongData(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumHeight(100);
    this->setMinimumWidth(400);
    _hScale = 2500;
    _hScroll = 0;
    _max = 0;
    _scaleX = 1;
    _translateX = 0;
    _floatSelection[0] = -1;
    _floatSelection[1] = -1;
}
void WidgetSongData::onFloatSelection(float a, float b)
{
    //qDebug()<<a<<b;
    _floatSelection[0] = a;
    _floatSelection[1] = b;
    update();
}
void WidgetSongData::setSeekPosition(quint64 seek)
{
    _seek = seek;
    update();
}
void WidgetSongData::setWidgetSentence(ShowSentenceWidget *showSentenceWidget)
{
    _showSentenceWidget = showSentenceWidget;
    connect(_showSentenceWidget, SIGNAL(floatSelection(float,float)), this, SLOT(onFloatSelection(float, float)));
    connect(_showSentenceWidget, SIGNAL(click(quint64)), this, SLOT(setSeekPosition(quint64)));
}
void WidgetSongData::setHScroll(int s)
{
    _hScroll = s;
    update();
}

void WidgetSongData::setHScale(int s)
{
    _hScale = s;
    update();
}

void WidgetSongData::addData(qreal leftData, qreal rightData)
{
    _leftData << leftData;
    _rightData << rightData;
}


void WidgetSongData::paintEvent(QPaintEvent * /*event*/)
{
    if(_leftData.size() < 2)
    {
        return;
    }


    int start = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScroll()) - _showSentenceWidget->getLyrics()->getGap();
    int duration = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScale()) - _showSentenceWidget->getLyrics()->getGap();
    int startBytes = start * 0.441;
    int nbAvailableBytes = duration * 0.882;
    int endBytes = min(_leftData.size(), nbAvailableBytes + startBytes);
    int binSize = max(1, nbAvailableBytes / 1000.0);
    qreal byteDensity = nbAvailableBytes / (2.0*width());
    QPolygonF poly, polyI;
    poly.append(QPointF(0, height()/2.0));
    polyI.append(QPointF(0, height()/2.0));
    for(int i = startBytes; i < endBytes; i += binSize)
    {
        qreal binLeftMax = _leftData[i];
        for(int idm = 1; idm < binSize && idm + i < endBytes; ++idm)
        {
            binLeftMax = fmax(binLeftMax, _leftData[i + idm]);
        }
        qreal binRightMax = _rightData[i];
        for(int idm = 1; idm < binSize && idm + i < endBytes; ++idm)
        {
            binRightMax = fmax(binRightMax, _rightData[i + idm]);
        }
        poly.append(QPointF((i-startBytes)/byteDensity, height()/2.0 - binLeftMax * height()/2.0));
        polyI.append(QPointF((i-startBytes)/byteDensity, height()/2.0 + binRightMax * height()/2.0));
    }
    poly.append(QPointF(width(), height()/2.0));
    polyI.append(QPointF(width(), height()/2.0));
    QPainter painter(this);
    quint64 ms = _showSentenceWidget->getLyrics()->beatToMsc(_hScroll) - (quint64)_showSentenceWidget->getLyrics()->getGap();
    _translateX = -((qreal)ms)*0.882/(qreal)binSize;
    //qDebug()<<_hScroll<<" "<<ms<<" "<<_translateX;
    //painter.translate(_translateX,0);
    QPen pen(QColor(100,0,0,150));
    painter.setPen(pen);
    pen.setWidth(1);
    QBrush leftbrush(QColor(255,0,0,100));
    painter.setBrush(leftbrush);
    painter.drawPolygon(poly);
    QPen rightpen(QColor(0,100,0,150));
    rightpen.setWidth(1);
    painter.setPen(rightpen);
    QBrush rightbrush(QColor(0,255,0,100));
    painter.setBrush(rightbrush);
    painter.drawPolygon(polyI);

    if(_floatSelection[1] >= 0)
    {
        painter.setPen(QPen(QColor(255,60,60,155)));
        painter.setBrush(QBrush(QColor(255,60,60,55)));
        painter.drawRect(QRectF(width()*(_floatSelection[0]-start)/(qreal)duration, 0,width()*(_floatSelection[1] - _floatSelection[0])/(qreal)duration, height()));
    }
    else
    if(((quint64)start) < _seek && _seek < (quint64)(start + duration))
    {
        painter.setPen(QPen(QColor(255,60,60,255)));
        painter.setBrush(QBrush(QColor(255,60,60,255)));
        painter.drawRect(QRectF(width()*(_seek-start)/(qreal)duration, 0, 1 , height()));
    }
}

void WidgetSongData::wheelEvent(QWheelEvent * event)
{
    if(event->orientation() == Qt::Vertical)
    {
        _scaleX *= (event->delta() > 0 ? 1.1 : 0.9);
    }
    else
    {
        _translateX += event->delta();
    }
    update();
}
