/****************************************************************************
**
** Author & Contact: Quentin BRAMAS ( contact@bramas.fr )
**
** This file is part of Ultratools.
**
** GNU General Public License Usage
** ExUlt is free software: you can redistribute it and/or modify it under the
** terms of General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** ExUlt is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** If you have questions regarding the use of this file, please contact
** Quentin BRAMAS (contact@bramas.fr).
**
****************************************************************************/


#include "uWydget_timeline.h"
#include "uShowSentenceWydget.h"
#include <QDebug>
#include <QMouseEvent>
#include "uNoteManager.h"
#include <QPainter>
#include <math.h>

UWydget_Timeline::UWydget_Timeline()
{

    this->setGeometry(0,0,400,50);
    min=max=0;
    _bpm = 272;
    _gapSelected = false;

    _lastGap = _gap = 0;

    setMouseTracking(true);
    _showSentenceWidget = 0;
    update();
}


void UWydget_Timeline::mouseMoveEvent(QMouseEvent *event)
{
    float duration = 15.0f/_bpm;
     //float longueur=(max-min) * duration; // longueur en second
     float fMin = min * duration;
     float fMax = max * duration;
    float fTempsR = ((float)(fMax-fMin))/((float)width());


   if(((((event->x()+5)*fTempsR)+fMin)*1000.0)>_gap &&
      ((((event->x()-5)*fTempsR)+fMin)*1000.0)<_gap
      )
    {
       this->setCursor(Qt::SizeHorCursor);
    }
    else
   {
        this->setCursor(Qt::ArrowCursor);
    }

    if(_gapSelected)
    {
        _gap = event->x()*_showSentenceWidget->duration()/(qreal)width() + _showSentenceWidget->startTime();
        emit click(_gap);
    }

    update();
}

void UWydget_Timeline::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    if(_gapSelected)
    {
        //_gap = ((((event->x())*fTempsR)+fMin)*1000.0);// + _lastGap;
        _gapSelected = false;
        _gap = _gap<0?0:_gap;
        emit gapModified(_gap);
     }

}

void UWydget_Timeline::mousePressEvent(QMouseEvent *event)
{


    qreal gap = _showSentenceWidget->getLyrics()->getGap();
    if(width()*(gap-_showSentenceWidget->startTime())/_showSentenceWidget->duration() + 5 > event->x()
            && width()*(gap-_showSentenceWidget->startTime())/_showSentenceWidget->duration() - 5 < event->x()
      )
    {
       _gapSelected = true;
       _lastGap = _gap = gap;
       qDebug()<<"select "<<_gap;
    }

}

void UWydget_Timeline::paintEvent(QPaintEvent * /*event*/)
{
 QPainter painter(this);
if(!_showSentenceWidget)
{
    return;
}

 quint64 start = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScroll()) - _showSentenceWidget->getLyrics()->getGap();
 quint64 duration = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScale()) - _showSentenceWidget->getLyrics()->getGap();

//painter.drawText(QRect(0,0,50,50),QString::number(255));

 qreal longueur = duration/1000.0; // longueur en second



 painter.setPen(QPen(QColor(240,240,240,255)));
 painter.setBrush(QBrush(QColor(240,240,240,255)));
 painter.drawRect(0,0,width(),40);





painter.setPen(QPen(QColor(0,173,232,255)));

 painter.setBrush(QBrush(QColor(255,255,255,255)));
 painter.translate(-width()*(start/1000.0-floor(start/1000.0))/(duration/1000.0), 0);

 int pas = 120;
 if(longueur<20)
 {
     pas = 1;
 }else
 if(longueur<40)
 {
     pas = 2;
 }else
 if(longueur<80)
 {
     pas = 5;
 }else
 if(longueur<160)
 {
     pas = 10;
 }else
 if(longueur<450)
 {
     pas = 30;
 }else
 if(longueur<1000)
 {
     pas = 60;
 }
for(int i = 0; i < duration/1000.0; ++i)
 {
    int s = floor(start/1000.0) + i;
    if(pas > 1 && s%pas) continue;

    if(s%30)
    {
        painter.setFont(QFont("Arial",10,QFont::Light,false));
    }
    else
    {
        painter.setFont(QFont("Arial",11,QFont::Bold,false));
    }
    QString num = (s%60 < 10 ? "0": "");
    num+=QString::number(s%60);
    painter.drawText(QRect(width()*i/(duration/1000.0),0,50,50),QString::number((s-s%60)/60)+":"+num);
    painter.drawLine(width()*i/(duration/1000.0),0,width()*i/(duration/1000.0),40);

 }

//reset the painter translation
painter.setTransform(QTransform());

qreal gap = _gap;//_showSentenceWidget->getLyrics()->getGap();
 if(start < gap && gap < start + duration)
 {
     // gap Cursor
     painter.setPen(QPen(QColor(0,0,0,180)));
     painter.setBrush(QBrush(QColor(0,0,0,180)));
     painter.drawRect(QRectF(width()*(_gap-start)/(qreal)duration - 5,0,10,20));
     painter.drawRect(QRectF(width()*(_gap-start)/(qreal)duration,20,0,20));
 }

 if(start < _seek && _seek < start + duration)
 {
     // time Cursor
     qreal left = width()*(_seek-start)/(qreal)duration;
     painter.setPen(QPen(QColor(255,60,60,255)));
     painter.setBrush(QBrush(QColor(255,60,60,255)));
     painter.drawRect(QRectF(left,0,1,height()));

     if(!UNoteManager::Instance.isPlaying())
     {
        //draw a cursor to move all the notes before the current time
         qreal h = height()/2.0;

         QPolygonF arrow;
         arrow.append(QPointF(left+7, h-2));
         arrow.append(QPointF(left+20, h-2));
         arrow.append(QPointF(left+20, h-10));
         arrow.append(QPointF(left+30, h));
         arrow.append(QPointF(left+20, h+10));
         arrow.append(QPointF(left+20, h+2));
         arrow.append(QPointF(left+7, h+2));
         arrow.append(QPointF(left+7, h-2));
         painter.drawPolygon(arrow);
     }
 }


}

void UWydget_Timeline::setWidgetSentence(ShowSentenceWidget *showSentenceWidget)
{
   _showSentenceWidget = showSentenceWidget;
   connect(_showSentenceWidget, SIGNAL(click(quint64)), this, SLOT(setSeekPosition(quint64)));
}

void UWydget_Timeline::setSeekPosition(quint64 seek)
{
    _seek = seek;
    update();
}
