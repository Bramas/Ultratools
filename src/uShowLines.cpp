/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Quentin Bramas <quentin@bramas.fr> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Quentin Bramas
 *
 * "LICENCE BEERWARE" (Révision 42):
 * Quentin Bramas <quentin@bramas.fr> a créé ce fichier. Tant que vous conservez cet avertissement,
 * vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
 * que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
 * retour. Quentin Bramas
 * ----------------------------------------------------------------------------
 */


#include "uShowLines.h"
#include <QPainter>

ShowLines::ShowLines()
{
    this->setGeometry(0,0,50,400);
    min=max=0;
    update();
}
void ShowLines::paintEvent(QPaintEvent * /*event*/)
{
 QPainter painter(this);

     painter.setPen(QPen(QColor(0,173,232,170)));
     painter.setBrush(QBrush(QColor(255,255,255,255)));
//painter.drawText(QRect(0,0,50,50),QString::number(255));

     float tempsR = ((float)height())/((float)(max-min));
     int deca=0;
if(min%2)
deca=((float)height())/((float)(max-min));
for(int i=min+1;i<=max;i+=2)
     {
         painter.drawText(QRect(0,((float)(i-min))*tempsR+deca,50,50),QString::number(255-i));

  //  //qDebug()<<(max-i);
      painter.drawLine(0,((float)(i-min))*tempsR+deca,25,((float)(i-min))*tempsR+deca);

  }
for(int i=min;i<=max;i+=2)
     {
         painter.drawText(QRect(30,((float)(i-min))*tempsR+deca,50,50),QString::number(255-i));
  //  //qDebug()<<(max-i);
      painter.drawLine(25,((float)(i-min))*tempsR+deca,50,((float)(i-min))*tempsR+deca);

  }

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
