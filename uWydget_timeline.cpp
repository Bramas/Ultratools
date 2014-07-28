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
#include <QDebug>
#include <QMouseEvent>
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
        _gap = ((((event->x())*fTempsR)+fMin)*1000.0);// + _lastGap;
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
        emit gapModified(_gap);
     }

}

void UWydget_Timeline::mousePressEvent(QMouseEvent *event)
{

    float duration = 15.0f/_bpm;
     float fMin = min * duration;
     float fMax = max * duration;
    float fTempsR = ((float)(fMax-fMin))/((float)width());


    if(((((event->x()+5)*fTempsR)+fMin)*1000.0)>_gap &&
      ((((event->x()-5)*fTempsR)+fMin)*1000.0)<_gap
      )
    {
       _gapSelected = true;
       _lastGap = _gap;
    }

}

void UWydget_Timeline::paintEvent(QPaintEvent * event)
{
 QPainter painter(this);


float duration = 15.0f/_bpm;


//painter.drawText(QRect::QRect(0,0,50,50),QString::number(255));

 float tempsR = ((float)width())/((float)(max-min));
 float longueur=(max-min) * duration; // longueur en second
 float fMin = min * duration;
 float fMax = max * duration;
 float fTempsR = ((float)width())/((float)(fMax-fMin));



 painter.setPen(QPen::QPen(QColor::QColor(240,240,240,255)));
 painter.setBrush(QBrush::QBrush(QColor::QColor(240,240,240,255)));
 painter.drawRect(0,0,width(),40);


 painter.setPen(QPen::QPen(QColor::QColor(255,60,60,255)));

  painter.setBrush(QBrush::QBrush(QColor::QColor(255,60,60,255)));


// gap Cursor
painter.drawRect(QRectF(((_gap/1000.0 - fMin)*fTempsR)-5,0,10,20));
painter.drawRect(QRectF(((_gap/1000.0 - fMin)*fTempsR),20,0,20));





painter.setPen(QPen::QPen(QColor::QColor(0,173,232,255)));

 painter.setBrush(QBrush::QBrush(QColor::QColor(255,255,255,255)));


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
for(int i=((int)ceil(fMin))-((int)ceil(fMin))%pas;i<fMax;i+=pas)
 {
    if(i%30)
    {
        painter.setFont(QFont::QFont("Arial",10,QFont::Light,false));
    }
    else
    {
        painter.setFont(QFont::QFont("Arial",11,QFont::Bold,false));
    }
    painter.drawText(QRect::QRect(((float)(i/duration-min))*tempsR+2,0,50,50),QString::number((i-i%60)/60)+":"+QString::number(i%60));

          painter.drawLine(((float)(i/duration-min))*tempsR,0,((float)(i/duration-min))*tempsR,40);

 }


     //SECONDS
/*if(longueur<200)
for(int i=min-min%10;i<=max;i+=10)
{
   if(!(i%60)) continue;

    painter.drawText(QRect::QRect(((float)(i-min))*tempsR+2,0,50,50),QString::number((i-i%60)/60)+":"+QString::number(i%60));
//  //qDebug()<<(max-i);
  painter.drawLine(((float)(i-min))*tempsR,0,((float)(i-min))*tempsR,25);

}
else
if(longueur<1000)
for(int i=min-min%30;i<=max;i+=30)
{
    if(!(i%60)) continue;


     painter.drawText(QRect::QRect(((float)(i-min))*tempsR+2,0,50,50),QString::number((i-i%60)/60)+":"+QString::number(i%60));
//  //qDebug()<<(max-i);
  painter.drawLine(((float)(i-min))*tempsR,0,((float)(i-min))*tempsR,25);

}

//MINUTES
for(int i=min-min%60;i<=max;i+=60)
{
    painter.drawText(QRect::QRect(((float)(i-min))*tempsR+2,0,50,50),QString::number((i-i%60)/60)+":00");
//  //qDebug()<<(max-i);
  painter.drawLine(((float)(i-min))*tempsR,0,((float)(i-min))*tempsR,25);

}

*/

}
