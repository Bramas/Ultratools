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

#include "uWidgetSongData.h"
#include "uShowSentenceWydget.h"
#include <QPainter>
#include <QWheelEvent>
#include <QPointF>
#include <QPolygonF>
#include <QDebug>
#include <QElapsedTimer>
#include <cmath>

WidgetSongData::WidgetSongData(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumHeight(100);
    this->setMinimumWidth(400);
    _hScale = 2500;
    _hScroll = 0;
    _max = 0;
    _floatSelection[0] = -1;
    _floatSelection[1] = -1;
}
void WidgetSongData::onFloatSelection(double a, double b)
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
    connect(_showSentenceWidget, SIGNAL(floatSelection(double,double)), this, SLOT(onFloatSelection(double, double)));
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
        polyI.append(QPointF((i-startBytes)/byteDensity, height()/2.0 + binRightMax * height()/2.0 - 1));
    }
    poly.append(QPointF(width(), height()/2.0));
    polyI.append(QPointF(width(), height()/2.0));
    QPainter painter(this);
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
