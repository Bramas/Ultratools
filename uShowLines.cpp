/****************************************************************************
**
** Contact: Quentin BRAMAS (contact@bramas.fr)
**
** This file is part of ExUlt.
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


#include "uShowLines.h"

ShowLines::ShowLines()
{
    this->setGeometry(0,0,50,400);
    min=max=0;
    update();
}
void ShowLines::paintEvent(QPaintEvent * event)
{
 QPainter * painter = new QPainter(this);

     painter->setPen(QPen(QColor(0,173,232,170)));

     painter->setBrush(QBrush(QColor(255,255,255,255)));
//painter->drawText(QRect::QRect(0,0,50,50),QString::number(255));

     float tempsR = ((float)height())/((float)(max-min));
     int deca=0;
if(min%2)
deca=((float)height())/((float)(max-min));
for(int i=min+1;i<=max;i+=2)
     {
         painter->drawText(QRect(0,((float)(i-min))*tempsR+deca,50,50),QString::number(255-i));
  //  //qDebug()<<(max-i);
      painter->drawLine(0,((float)(i-min))*tempsR+deca,25,((float)(i-min))*tempsR+deca);

  }
for(int i=min;i<=max;i+=2)
     {
         painter->drawText(QRect(30,((float)(i-min))*tempsR+deca,50,50),QString::number(255-i));
  //  //qDebug()<<(max-i);
      painter->drawLine(25,((float)(i-min))*tempsR+deca,50,((float)(i-min))*tempsR+deca);

  }


delete painter;
}

void ShowLines::setMin(int v)
{
    min=v;
  //  //qDebug()<<"min: "<<min<<"   max: "<<max;
update();
}


void ShowLines::setMax(int v)
{
    max=v;
    update();
}
