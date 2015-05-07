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
#include <QDebug>

ShowLines::ShowLines()
{
    this->setGeometry(0,0,50,400);
    min=max=0;
    _octaveOffset = 0;
    update();
}
void ShowLines::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    painter.setPen(QPen(QColor(0,173,232,170)));
    painter.setBrush(QBrush(QColor(255,255,255,255)));

    qreal tempsR = ((qreal)height())/((qreal)(max-min));

    qreal offset = min*tempsR;
   /* for(int i=min+1;i<=max;i+=2)
    {
        qreal y = height() - i*tempsR + offset;
        painter.drawText(QRect(0, y, 50, 50),QString::number(i));
        //  //qDebug()<<(max-i);
        painter.drawLine(0, y, 25, y);

    }
    for(int i=min;i<=max;i+=2)
    {
        qreal y = height() - i*tempsR + offset;
         painter.drawText(QRect(30, y, 50, 50),QString::number(i));
        //  //qDebug()<<(max-i);
        painter.drawLine(25, y, 50, y);
    }*/

    for(int i=min;i<=max;i++)
    {
        qreal y = height() - i*tempsR + offset;
        painter.drawText(55, y + QFontMetrics(painter.font()).height()/2.0-1, QString::number(i+_octaveOffset*12));
        drawPianoNote(&painter, y, i);
    }

}
void ShowLines::drawPianoNote(QPainter *painter, qreal y, int n)
{
    painter->save();
    qreal h = height()/(qreal)(max - min) - 1;
    painter->setPen(QPen(QColor(150,150,150)));
    n += _octaveOffset*12;
    int o = n > 0 ? floor(n/12) : ceil(n/12);
    n = n > 0 ? n%12 : -(n%12);

    QString notes[12]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    QString note = notes[n];
    switch(n)
    {
    case 1:
    case 3:
    case 6:
    case 8:
    case 10: // black notes
        painter->setBrush(QBrush(QColor(0,0,0)));
        painter->drawRect(0, y-h/2, 30, h);
        painter->setPen(QPen(QColor(200,200,200)));
        break;
    default: //white notes
        painter->setBrush(QBrush(QColor(255,255,255)));
        painter->drawRect(0, y-h/2, 50, h);
        painter->setPen(QPen(QColor(80,80,80)));
    }
    QFont f = painter->font();
    f.setBold(true);
    painter->setFont(f);
    painter->drawText(5, y+QFontMetrics(painter->font()).height()/2.0-1, note);
    f.setBold(false);
    painter->setFont(f);
    painter->setPen(QPen(QColor(140,140,140,150)));
    painter->drawText(5+QFontMetrics(painter->font()).width(note)+3, y+QFontMetrics(painter->font()).height()/2.0-1, QString::number(o));

    painter->restore();
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
