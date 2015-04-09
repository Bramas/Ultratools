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
#include "uFile.h"
#include "uShowSentenceWydget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <math.h>

UWydget_Timeline::UWydget_Timeline(UFile * file)
{
    _file=file;
    this->setGeometry(0,0,400,50);
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
    float duration = 15.0f/_bpm;
     //float longueur=(max-min) * duration; // longueur en second
     float fMin = min * duration;
     float fMax = max * duration;
    float fTempsR = ((float)(fMax-fMin))/((float)width());


   if(((((event->x()+5)*fTempsR)+fMin)*1000.0)>_gap &&
      ((((event->x()-5)*fTempsR)+fMin)*1000.0)<_gap
      )
    {
       _gapOver=true;
    }
    else
   {
        _gapOver=false;
    }
    if(((((event->x()+5)*fTempsR)+fMin)*1000.0)>_seek &&
       ((((event->x()-5)*fTempsR)+fMin)*1000.0)<_seek
       )
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
        if(((((event->x()-10)*fTempsR)+fMin)*1000.0)>_gap &&
        ((((event->x()-35)*fTempsR)+fMin)*1000.0)<_gap
        )
        {
            this->setCursor(Qt::PointingHandCursor);
        }
        else
        {
            this->setCursor(Qt::ArrowCursor);
        }

    if(_gapSelected)
    {
<<<<<<< HEAD

        if(_gapLocked)
        {
            _gap = event->x()*_showSentenceWidget->duration()/(qreal)width() + _showSentenceWidget->startTime();
           this->_file->setGap(_gap);
            emit gapModified(_gap);
            emit click(_gap);
        }
        else
        {
            float diff = _gap-(((event->x())*fTempsR)+fMin)*1000.0;
            diff = (diff/1000.0) * _bpm/15.0f;
            if(diff>=1 || diff<=-1)
            {
                if(_file)
                {

                    if(_file->lyrics->setDelay(diff>=1?floor(diff):ceil(diff)))
                    {
                        qDebug()<<_gap;
                        //_gap = ((((event->x())*fTempsR)+fMin)*1000.0);
                        _gap -= ((diff>=1?floor(diff):ceil(diff))*1000.0 * 15.0f/_bpm);
                        qDebug()<<_gap;
                        qDebug()<<((diff>=1?floor(diff):ceil(diff))*1000.0 * 15.0f/_bpm);

                        qDebug()<<"--";
                        _file->setGap(_gap);
                        emit gapModified();
                    }
                }
                // + _lastGap;
                //QMessageBox::information(NULL,"lol",QString::number(diff));
            }
        }
    }
    if(_seekSelected)
    {
        float diff = (((event->x())*fTempsR)+fMin)*1000.0-_seek;
        diff = (diff/1000.0) * _bpm/15.0f;
        if(diff>=1 || diff<=-1)
        {
            if(_file)
            {
               // qDebug()<<floor(diff)<<" - "<<ceil(diff)<<" - "<<(diff>=1?floor(diff):ceil(diff));
                if(_file->lyrics->setDelay(diff>=1?floor(diff):ceil(diff),_seek))
                {
                    _seek+=(diff>=1?floor(diff):ceil(diff))*1000.0 * 15.0f/_bpm;
                }
            }
            //QMessageBox::information(NULL,"lol",QString::number(diff));
        }
        //_gap = ((((event->x())*fTempsR)+fMin)*1000.0);// + _lastGap;
        //emit gapModified(_gap);
    }

    update();
}

void UWydget_Timeline::mouseReleaseEvent(QMouseEvent *event)
{
    if(_gapSelected)
    {
        //_gap = ((((event->x())*fTempsR)+fMin)*1000.0);// + _lastGap;
        _gapSelected = false;

        _gap = _gap<0?0:_gap;
        emit gapModified();
     }
    if(_seekSelected)
    {
        _seekSelected = false;
     }

}

void UWydget_Timeline::mousePressEvent(QMouseEvent *event)
{

    float duration = 15.0f/_bpm;
     float fMin = min * duration;
     float fMax = max * duration;
    float fTempsR = ((float)(fMax-fMin))/((float)width());

    qreal gap = _showSentenceWidget->getLyrics()->getGap();

    if(((((event->x()+5)*fTempsR)+fMin)*1000.0)>_seek &&
      ((((event->x()-5)*fTempsR)+fMin)*1000.0)<_seek
      )
    {
       _seekSelected = true;
    }
    else
    if(width()*(gap-_showSentenceWidget->startTime())/_showSentenceWidget->duration() + 5 > event->x()
            && width()*(gap-_showSentenceWidget->startTime())/_showSentenceWidget->duration() - 5 < event->x()
      )
    {
       _gapSelected = true;
       _lastGap = _gap = gap;
       qDebug()<<"select "<<_gap;
    }
    else
    if(((((event->x()-10)*fTempsR)+fMin)*1000.0)>_gap &&
      ((((event->x()-35)*fTempsR)+fMin)*1000.0)<_gap
      )
    {
        _gapLocked=!_gapLocked;
    }

}

void UWydget_Timeline::paintEvent(QPaintEvent * event)
{
 QPainter painter(this);
if(!_showSentenceWidget)
{
    return;
}

 quint64 start = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScroll()) - _showSentenceWidget->getLyrics()->getGap();
 quint64 duration = _showSentenceWidget->getLyrics()->beatToMsc(_showSentenceWidget->getHScale()) - _showSentenceWidget->getLyrics()->getGap();

//painter.drawText(QRect(0,0,50,50),QString::number(255));

 qreal tempsR = ((qreal)width())/((qreal)(max-min));
 qreal longueur = duration/1000.0; // longueur en second
 qreal fMin = min * duration;
 qreal fMax = max * duration;
 qreal fTempsR = ((float)width())/((float)(fMax-fMin));



 painter.setPen(QPen(QColor(240,240,240,255)));
 painter.setBrush(QBrush(QColor(240,240,240,255)));
 painter.drawRect(0,0,width(),40);

<<<<<<< HEAD

 painter.setPen(QPen(QColor(255,60,60,255)));

  painter.setBrush(QBrush(QColor(255,60,60,255)));


// gap Cursor
if(start < gap && gap < start + duration)
{
    painter.setPen(QPen(QColor(255,60,60,255)));
    painter.setBrush(QBrush(QColor(255,60,60,255)));
    // gap Cursor
    painter.drawRect(QRectF(width()*(_gap-start)/(qreal)duration - 5,0,10,20));
    painter.drawRect(QRectF(width()*(_gap-start)/(qreal)duration,20,0,20));
}
// gap Lock
if(_gapLocked)
{
    QVector<QPoint> arrowPoints;
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+15,18));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+15,30));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+30,30));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+30,18));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+19,18));

    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+19,7));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+26,7));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+26,18));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+28,18));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+28,5));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+17,5));

    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+17,18));

    painter.drawPolygon(QPolygon(arrowPoints));
}
else
{
    QVector<QPoint> arrowPoints;
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+15,18));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+15,30));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+30,30));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+30,18));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+19,18));

    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+19,7));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+12,7));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+12,18));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+10,18));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+10,5));
    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+17,5));

    arrowPoints.push_back(QPoint(((_gap/1000.0 - fMin)*fTempsR)+17,18));

    painter.drawPolygon(QPolygon(arrowPoints));
}


// seek Cursor
painter.setPen(QPen(QColor(0,173,232,255)));
painter.setBrush(QBrush(QColor(0,173,232,255)));

painter.drawRect(QRectF(((_seek/1000.0 - fMin)*fTempsR)-5,0,10,20));
painter.drawRect(QRectF(((_seek/1000.0 - fMin)*fTempsR),20,0,20));

// seek over
if(_seekOver)
{
    QVector<QPoint> arrowPoints;
    arrowPoints.push_back(QPoint(((_seek/1000.0 - fMin)*fTempsR)+15,5));
    arrowPoints.push_back(QPoint(((_seek/1000.0 - fMin)*fTempsR)+20,5));
    arrowPoints.push_back(QPoint(((_seek/1000.0 - fMin)*fTempsR)+20,0));
    arrowPoints.push_back(QPoint(((_seek/1000.0 - fMin)*fTempsR)+25,10));
    arrowPoints.push_back(QPoint(((_seek/1000.0 - fMin)*fTempsR)+20,20));
    arrowPoints.push_back(QPoint(((_seek/1000.0 - fMin)*fTempsR)+20,15));
    arrowPoints.push_back(QPoint(((_seek/1000.0 - fMin)*fTempsR)+15,15));
    painter.drawPolygon(QPolygon(arrowPoints));
}


painter.setPen(QPen(QColor(0,173,232,255)));

 painter.setBrush(QBrush(QColor(255,255,255,255)));
 painter.translate(-width()*(start/1000.0-floor(start/1000.0))/(duration/1000.0), 0);

 int pas;
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


     //SECONDS
/*if(longueur<200)
for(int i=min-min%10;i<=max;i+=10)
{
   if(!(i%60)) continue;

    painter.drawText(QRect(((float)(i-min))*tempsR+2,0,50,50),QString::number((i-i%60)/60)+":"+QString::number(i%60));
//  //qDebug()<<(max-i);
  painter.drawLine(((float)(i-min))*tempsR,0,((float)(i-min))*tempsR,25);

}
else
if(longueur<1000)
for(int i=min-min%30;i<=max;i+=30)
{
    if(!(i%60)) continue;


     painter.drawText(QRect(((float)(i-min))*tempsR+2,0,50,50),QString::number((i-i%60)/60)+":"+QString::number(i%60));
//  //qDebug()<<(max-i);
  painter.drawLine(((float)(i-min))*tempsR,0,((float)(i-min))*tempsR,25);

}

//MINUTES
for(int i=min-min%60;i<=max;i+=60)
{
    painter.drawText(QRect(((float)(i-min))*tempsR+2,0,50,50),QString::number((i-i%60)/60)+":00");
//  //qDebug()<<(max-i);
  painter.drawLine(((float)(i-min))*tempsR,0,((float)(i-min))*tempsR,25);

}

*/

}

void UWydget_Timeline::setSeek(quint64 time)
{
    _seek = time;
    update();
}
