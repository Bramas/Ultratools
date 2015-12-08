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


#include "uWydget_timeline.h"
#include "uFile.h"
#include "uShowSentenceWydget.h"
#include "editorwindow.h"
#include <QDebug>
#include <QMouseEvent>
#include "uNoteManager.h"
#include <QPainter>
#include <cmath>

UWydget_Timeline::UWydget_Timeline(UEditorWindow *parent)
{
    this->setGeometry(0,0,400,50);
    _parent = parent;
    min=max=0;
    _bpm = 272;
    _gapSelected = _seekSelected = false;
    _seekOver = _gapOver = false;
    _gapLocked = true;
    _lastGap = _gap = 0;
    _seek = 0;
    setMouseTracking(true);
    _showSentenceWidget = 0;
    update();
}


void UWydget_Timeline::mouseMoveEvent(QMouseEvent *event)
{


    quint64 start = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScroll()) - _showSentenceWidget->getLyrics()->getGap();
    quint64 duration = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScale()) - _showSentenceWidget->getLyrics()->getGap();

    int seekXPos = width()*(_seek-start)/(qreal)duration;
    int gapXPos = width()*(_gap-start)/(qreal)duration;


   if( event->x() > gapXPos - 5 && event->x() < gapXPos + 5)
    {
       _gapOver=true;
    }
    else
    {
        _gapOver=false;
    }
    if( event->x() > seekXPos - 5 && event->x() < seekXPos + 5)
    {
        _seekOver=true;
    }
    else
    {
        _seekOver=false;
    }
    if(_seekOver || _gapOver)
    {
        this->setCursor(Qt::SizeHorCursor);
    }
    else
        if( event->x() > gapXPos +10 && event->x() < gapXPos + 35)
        {
            this->setCursor(Qt::PointingHandCursor);
        }
        else
        {
            this->setCursor(Qt::ArrowCursor);
        }

    if(_gapSelected)
    {
        if(_gapLocked)
        {
            _gap = event->x()*_showSentenceWidget->duration()/(qreal)width() + _showSentenceWidget->startTime();
           this->_parent->getFile()->setGap(_gap);
            emit gapModified(_gap);
        }
        else
        {
            double diff = _gap-event->x()*_showSentenceWidget->duration()/(qreal)width() - _showSentenceWidget->startTime();

            diff = (diff/1000.0) * _bpm/15.0;
            if(diff>=1 || diff<=-1)
            {
                if(_parent->getFile())
                {
                    int delay = _parent->getFile()->lyrics->setDelay(diff>=1?floor(diff):ceil(diff));
                    if(delay)
                    {
                        _gap -= delay*1000.0 * 15.0/_bpm;
                        _parent->getFile()->setGap(_gap);
                        emit gapModified(_gap);
                    }
                }
            }
        }
    }
    if(_seekSelected)
    {
        double diff = event->x()*_showSentenceWidget->duration()/(qreal)width() + _showSentenceWidget->startTime()-_seek;
        diff = (diff/1000.0) * _bpm/15.0;
        if(diff>=1 || diff<=-1)
        {
            if(_parent->getFile())
            {
                int delay = _parent->getFile()->lyrics->setDelay(diff>=1?floor(diff):ceil(diff),_seek);
                if(delay)
                {
                    _seek+=delay*1000.0 * 15.0/_bpm;
                }
            }
        }
    }

    update();
}

void UWydget_Timeline::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    if(_gapSelected)
    {
        _gapSelected = false;

        _gap = _gap<0?0:_gap;
        emit gapModified(_gap);
     }
    if(_seekSelected)
    {
        _seekSelected = false;
     }

}

void UWydget_Timeline::mousePressEvent(QMouseEvent *event)
{

    quint64 start = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScroll()) - _showSentenceWidget->getLyrics()->getGap();
    quint64 duration = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScale()) - _showSentenceWidget->getLyrics()->getGap();

    int seekXPos = width()*(_seek-start)/(qreal)duration;
    int gapXPos = width()*(_gap-start)/(qreal)duration;


    if( event->x() > seekXPos - 5 && event->x() < seekXPos + 5)
    {
       _seekSelected = true;
    }
    else
    if( event->x() > gapXPos - 5 && event->x() < gapXPos + 5)
    {
       _gapSelected = true;
       _lastGap = _gap;
    }
    else
    if( event->x() > gapXPos +10 && event->x() < gapXPos + 35)
    {
        _gapLocked=!_gapLocked;
    }

    update();

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




painter.setPen(QPen(QColor(255,60,60,255)));

 painter.setBrush(QBrush(QColor(255,60,60,255)));

int gapXPos = width()*(_gap-start)/(qreal)duration;
// gap Cursor
painter.setPen(QPen(QColor(0,0,0,150)));
painter.setBrush(QBrush(QColor(0,0,0,150)));
if(start < _gap + 5 && _gap < start + duration - 50)
{
    // gap Cursor
    painter.drawRect(QRectF(gapXPos - 5,0,10,20));
    painter.drawRect(QRectF(gapXPos,20,0,20));
    // gap Lock
    if(_gapLocked)
    {
       QVector<QPoint> arrowPoints;
       arrowPoints.push_back(QPoint(gapXPos+15,18));
       arrowPoints.push_back(QPoint(gapXPos+15,30));
       arrowPoints.push_back(QPoint(gapXPos+30,30));
       arrowPoints.push_back(QPoint(gapXPos+30,18));
       arrowPoints.push_back(QPoint(gapXPos+19,18));

       arrowPoints.push_back(QPoint(gapXPos+19,7));
       arrowPoints.push_back(QPoint(gapXPos+26,7));
       arrowPoints.push_back(QPoint(gapXPos+26,18));
       arrowPoints.push_back(QPoint(gapXPos+28,18));
       arrowPoints.push_back(QPoint(gapXPos+28,5));
       arrowPoints.push_back(QPoint(gapXPos+17,5));

       arrowPoints.push_back(QPoint(gapXPos+17,18));

       painter.drawPolygon(QPolygon(arrowPoints));
    }
    else
    {
       QVector<QPoint> arrowPoints;
       arrowPoints.push_back(QPoint(gapXPos+15,18));
       arrowPoints.push_back(QPoint(gapXPos+15,30));
       arrowPoints.push_back(QPoint(gapXPos+30,30));
       arrowPoints.push_back(QPoint(gapXPos+30,18));
       arrowPoints.push_back(QPoint(gapXPos+19,18));

       arrowPoints.push_back(QPoint(gapXPos+19,7));
       arrowPoints.push_back(QPoint(gapXPos+12,7));
       arrowPoints.push_back(QPoint(gapXPos+12,18));
       arrowPoints.push_back(QPoint(gapXPos+10,18));
       arrowPoints.push_back(QPoint(gapXPos+10,5));
       arrowPoints.push_back(QPoint(gapXPos+17,5));

       arrowPoints.push_back(QPoint(gapXPos+17,18));

       painter.drawPolygon(QPolygon(arrowPoints));
    }
}

int seekXPos = width()*(_seek-start)/(qreal)duration;

// seek Cursor
painter.setPen(QPen(QColor(255,60,60,180)));
painter.setBrush(QBrush(QColor(255,60,60,180)));

painter.drawRect(QRectF(seekXPos-5,0,10,20));
painter.drawRect(QRectF(seekXPos,20,0,20));

// seek over
if(_seekOver)
{
   QVector<QPoint> arrowPoints;
   arrowPoints.push_back(QPoint(seekXPos+15,5));
   arrowPoints.push_back(QPoint(seekXPos+20,5));
   arrowPoints.push_back(QPoint(seekXPos+20,0));
   arrowPoints.push_back(QPoint(seekXPos+25,10));
   arrowPoints.push_back(QPoint(seekXPos+20,20));
   arrowPoints.push_back(QPoint(seekXPos+20,15));
   arrowPoints.push_back(QPoint(seekXPos+15,15));
   painter.drawPolygon(QPolygon(arrowPoints));
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

void UWydget_Timeline::setSeek(quint64 time)
{
    _seek = time;
    update();
}
