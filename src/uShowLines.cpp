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


#include "uShowLines.h"
#include <QPainter>
#include <QDebug>
#include <cmath>

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
=======
    int i=min+1 - (((int)min)%2);
    if(min < 0)
    {
        i=min+1 - (((int)min - 1)%2);
    }
    if(min <= -1)
    {
        i = -1;
    }
    for(;i<=max;i+=2)
>>>>>>> 82deaa2b090bee16fdca95a4d52c218a49a080d4
    {
        qreal y = height() - i*tempsR + offset;
        painter.drawText(QRect(0, y, 50, 50),QString::number(i));
        //  //qDebug()<<(max-i);
        painter.drawLine(0, y, 25, y);

    }
    i=min - (((int)min)%2);
    if(min <= -1)
    {
        //i=min - (((int)min - 1)%2);
    }
    for(;i<=max;i+=2)
    {
        qreal y = height() - i*tempsR + offset;
         painter.drawText(QRect(30, y, 50, 50),QString::number(i));
        //  //qDebug()<<(max-i);
        painter.drawLine(25, y, 50, y);
    }*/

    for(int i=(int)min;i<=max;i++)
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

void ShowLines::setMin(double v)
{
    min=v;
  //  //qDebug()<<"min: "<<min<<"   max: "<<max;
update();
}


void ShowLines::setMax(double v)
{
    max=v;
    update();
}
