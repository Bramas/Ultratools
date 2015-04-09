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


#include "uShowSentenceWydget.h"
#include "editorwindow.h"
#include <QMoveEvent>
#include <QMessageBox>
#include <QPainter>
#include <math.h>
#include <QDebug>
#include <QScrollBar>
#include <QMenu>
#include <QAction>

#define TAILLE_FENETRE 1000
#define HAUTEUR_NOTE 20

//#define UPDATE_BY_TIMER
//#define DISPLAY_FPS

double mod(double in, double m)
{
    if(m<0) m=-m;

    if(in<0)
    {
        while((in=in+m)<m);
        return in;

    }

    while((in=in-m)>m);

    return in;
}

double max(double a,double b)
{
    return (a>b?a:b);
}
double abs(double in_x)
{
    return (in_x<0?-in_x:in_x);
}

double min(double a,double b)
{
    return (a<b?a:b);
}


ShowSentenceWidget::ShowSentenceWidget(UEditorWindow * parent)
{
    hScale=100;// nombre de deciseconds visible sur une fenettre
    vScale=500;
    _seekPosition=0;
    lyrics=0;
    setMouseTracking(true);
   this->parent=parent;
   mouseTime=0;

   _nextClick=0;
_previousDisplayed=2;
   mousePitch=0;
   time.start();

    this->setContextMenuPolicy(Qt::DefaultContextMenu);
#ifdef UPDATE_BY_TIMER
   QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(update()));
     timer->start();
#endif


     _mousePressed = _isPlaying = _clickAndMoveSelection = false;

     _fPointPress=QPointF(0.0,0.0);
     _timePress=QTime::currentTime();
    _hSizeCursor=_hSplitHCursor=_sizeAllCursor=_timeLocked=false;
     _overed=NULL;
     _overSep=NULL;


        _wordsDisplayed = new QList<Word*>();

        connect(&UInputManager::Instance, SIGNAL(keyPressEvent(QKeyEvent*)), this, SLOT(onKeyPressEvent(QKeyEvent*)));

}
ShowSentenceWidget::~ShowSentenceWidget()
{

}
void ShowSentenceWidget::mouseDoubleClickEvent(QMouseEvent * /*event*/)
{
    //QMessageBox::warning(NULL,"","LOL");

    if(_selected.empty())
    {
        emit doubleClik(-1);
        return;
    }


    emit doubleClik(_wordsDisplayed->indexOf(_selected.first()));

}

void ShowSentenceWidget::mousePressEvent(QMouseEvent *event)
{
    emit singleClik();
    _clickAndMoveSelection = false;
    _fPointPress = QPointF(event->x(),event->y());
    _timePress = QTime::currentTime();
    _mousePressed = true;

    if(_nextClick)
    {
        mouseTime=((float)(_lastBeatDisplayed-_firstBeatDisplayed))*(((float)event->x())/((float)width()))+_firstBeatDisplayed;
        mousePitch=(((-(float)vScale)/10.0))*(((float)event->y())/((float)height()))+(256-vScroll);

        if(_nextClick==ShowSentenceWidget::NEXT_CLICK_ADD_NOTE)
        {
            Word * w = new Word(NULL,mouseTime,4,mousePitch);
            w->setText("~");
            lyrics->addWord(w);
            _selected.push_back(w);
            emit modified();

        }else
        if(_nextClick==ShowSentenceWidget::NEXT_CLICK_ADD_SEPARATOR)
        {
            _overSep = lyrics->addSeparator(mouseTime);

        }

        _nextClick = 0;
        return;
    }

    if(!UInputManager::Instance.isKeyPressed(Qt::Key_Control) && (_selected.count()== 1 || !_selected.contains(_overed)) )
    {
        deselect();
        emit selection(-1,-1);
    }

    if(UInputManager::Instance.isKeyPressed(Qt::Key_Control) && _selected.contains(_overed) )
    {
        _selected.removeOne(_overed);
        _overed->setSelected(false);
        if(!_selected.empty())
        {
            emit selection(Word::minIndexOfWords(_selected,lyrics->words()),Word::maxIndexOfWords(_selected,lyrics->words()));
        }
    }
    else
    if(!_selected.contains(_overed) && _overed)
    {
        _overed->setSelected(true);
        _selected.push_back(_overed);
        emit selection(Word::minIndexOfWords(_selected,lyrics->words()),Word::maxIndexOfWords(_selected,lyrics->words()));
    }
    else
    if(!_overed)
    {
        emit emptyClik();
    }
    QWidget::mousePressEvent(event);
}

void ShowSentenceWidget::wheelEvent(QWheelEvent * event)
{
    if(event->orientation() == Qt::Horizontal)
    {
        int value = parent->horizontalScrollBar()->value();
        value -= event->delta()/2;
        parent->horizontalScrollBar()->setValue(value);
    }
    else
    {
        int value = parent->verticalScrollBar()->value();
        value -= event->delta()/2;
        parent->verticalScrollBar()->setValue(value);
    }
    event->accept();
}

double ShowSentenceWidget::posXToBeat(double in_x)
{
    return ((in_x)*_lastBeatDisplayed + ((width()-in_x))*_firstBeatDisplayed)/((qreal)width());
}
qreal ShowSentenceWidget::startTime()
{
    return lyrics->beatToMsc(hScroll) - lyrics->getGap();
}
qreal ShowSentenceWidget::duration()
{
    return lyrics->beatToMsc(hScale)-lyrics->getGap();
}

qreal ShowSentenceWidget::posXToMs(double in_x)
{
    return duration() * in_x/(qreal)width() + startTime();
}

void ShowSentenceWidget::mouseReleaseEvent(QMouseEvent *event)
{
     _mousePressed = false;
   QPointF pointRealease(event->x(),event->y());


   if((pointRealease-_fPointPress).manhattanLength()<10 && _timePress.msecsTo(QTime::currentTime())<500 && _overed==NULL)
   {
       //it is a single click

       _seekPosition = posXToBeat(event->x());

        emitSeek();
        _clickAndMoveSelection = false;
        emit floatSelection(-1, -1);

   }


   if(!_selected.empty() && _selected.first()->hasBeenModified())
   {
       Word * w;
       foreach(w,_selected)
       {
           w->hold();// finish the modification
           lyrics->removeWord(w);
       }
       foreach(w,_selected)
       {
           lyrics->addWord(w);
       }
       emit modified();
   }
   if(_overSep)
   {
       _overSep->hold();
       lyrics->resortWord(_overSep);

     //  qDebug()<<_overSep->getLength();
   }

    if(_clickAndMoveSelection)
    {
        _seekPosition = posXToBeat(min(_fPointPress.x(),event->x()));
        emitSeek();

    }


    if(!_clickAndMoveSelection && !_selected.empty() && !_isPlaying)
    {
        QPair<int,int> range = Word::rangeTime(&_selected);
        _floatSelection[0] = range.first;// - _gap;
        _floatSelection[1] = range.second;// - _gap;
        emit floatSelection(lyrics->beatToMsc(range.first), lyrics->beatToMsc(range.second));
        _seekPosition = range.first;
        emitSeek();


    }

    QWidget::mouseReleaseEvent(event);

#ifndef UPDATE_BY_TIMER
    update();
#endif
}

void ShowSentenceWidget::emitSeek()
{
    quint64 msc=(1000.0f*(_seekPosition+_gap)*15.0f/lyrics->getBpm());

    emit click(msc);
}

void ShowSentenceWidget::onKeyPressEvent(QKeyEvent * event)
{
    if(_selected.isEmpty())
    {
        return;
    }
    if(event->key() == Qt::Key_Up)
    {
        foreach(Word * w, _selected)
        {
            w->setPitch(w->getPitch() + 1);
        }
    }
    else if(event->key() == Qt::Key_Down)
    {
        foreach(Word * w, _selected)
        {
            w->setPitch(w->getPitch() - 1);
        }
    }
    else if(event->key() == Qt::Key_Left)
    {
        foreach(Word * w, _selected)
        {
            w->setTime(w->getTime() - 1);
            lyrics->resortWord(w);
        }
    }
    else if(event->key() == Qt::Key_Right)
    {
        foreach(Word * w, _selected)
        {
            w->setTime(w->getTime() + 1);
            lyrics->resortWord(w);
        }
    }
    update();
}

void ShowSentenceWidget::mouseMoveEvent ( QMouseEvent * event )
{
    _fMousePosition.setX(event->x());
    _fMousePosition.setY(event->y());






   mouseTime=((float)(_lastBeatDisplayed-_firstBeatDisplayed))*(((float)event->x())/((float)width()))+_firstBeatDisplayed;
   mousePitch=(256-vScroll) - (vScale/10)*(((qreal)event->y())/((qreal)height()));

   //qDebug()<<(((qreal)event->y())/((qreal)height()))<<" "<<(vScale/10)*(((qreal)event->y())/((qreal)height()))<<" "<<(256-vScroll);
   //qDebug()<<mousePitch;

    if(_mousePressed && !_isPlaying && (_fMousePosition-_fPointPress).manhattanLength()<10 && _timePress.msecsTo(QTime::currentTime())<500 && _overed==NULL)
    {
        _clickAndMoveSelection = true;
    }

    if(_mousePressed && _overSep)
    {

        //int diffY = floor(mousePitch) - floor((((-(float)vScale)/10.0))*(((float)_fPointPress.y())/((float)height()))+256-vScroll);
        int diffX = floor(mouseTime) - floor(((float)(_lastBeatDisplayed-_firstBeatDisplayed))*(((float)_fPointPress.x())/((float)width()))+_firstBeatDisplayed);


        if(_overSep->getOver() & ShowSentenceWidget::OVER_LEFT)
        {
            if(_overSep->getOLength()-diffX>0)
            {
                _overSep->setLength(_overSep->getOLength()-diffX,false);
                _overSep->setTime(_overSep->getOTime()+diffX,false);
            }
            else
            {
                _overSep->setLength(0,false);
                _overSep->setTime(_overSep->getOTime()+_overSep->getOLength(),false);
            }
        }
        else
        if(_overSep->getOver() & ShowSentenceWidget::OVER_RIGHT)
        {
            if(_overSep->getOLength()+diffX>0)
            {
                _overSep->setLength(_overSep->getOLength()+diffX,false);
            }
            else
            {
                _overSep->setLength(0,false);
            }
        }
        else
        {
            _overSep->setTime(_overSep->getOTime()+diffX,false);
        }
    }
    else
    if(_mousePressed && _clickAndMoveSelection)
    {
        _floatSelection[0] = posXToBeat(min(_fPointPress.x(),_fMousePosition.x()));
        _floatSelection[1] = posXToBeat(max(_fPointPress.x(),_fMousePosition.x()));
        emit floatSelection(posXToMs(min(_fPointPress.x(),_fMousePosition.x())), posXToMs(max(_fPointPress.x(),_fMousePosition.x())));


        deselect();

        foreach(Word * w, *_wordsDisplayed)
        {
             if(w->getTime()<_floatSelection[1]
                 && w->getTime()+w->getLength()>_floatSelection[0])
             {
                 //QMessageBox::warning(NULL,"" ,"lol");
                     _selected.push_back(w);
                     w->setSelected();
              }
        }
        emit selection(Word::minIndexOfWords(_selected,lyrics->words()),Word::maxIndexOfWords(_selected,lyrics->words()));

    }
    else
   if(_mousePressed && !_selected.empty() && (!UInputManager::Instance.isKeyPressed(Qt::Key_Control) || _selected.count()==1))
   {
       Word * w;


       int diffY = floor(mousePitch) - floor((((-(float)vScale)/10.0))*(((float)_fPointPress.y())/((float)height()))+256-vScroll);
       int diffX = floor(mouseTime) - floor(((float)(_lastBeatDisplayed-_firstBeatDisplayed))*(((float)_fPointPress.x())/((float)width()))+_firstBeatDisplayed);

       if(_selected.count()==1 && _selected.first()->getOver())
       {
           w=_selected.first();
           if(w->getOver() & ShowSentenceWidget::OVER_LEFT )
           {
               if(w->getOLength()-diffX>0)
               {
                   w->setLength(w->getOLength()-diffX,false);
                   w->setTime(w->getOTime()+diffX,false);
               }
               else
               {
                   w->setLength(1,false);
                   w->setTime(w->getOTime()+w->getOLength()-1,false);
               }

           }
           else
           if(w->getOver() & ShowSentenceWidget::OVER_RIGHT )
           {
               if(w->getOLength()+diffX>0)
               {
                   w->setLength(w->getOLength()+diffX,false);
               }
               else
               {
                   w->setLength(1,false);
               }
           }
       }
       else
       {

          // qDebug()<<_selected.count()<<"  "<<_selected.first()->getOver();
            foreach(w,_selected)
            {
                w->setPitch(w->getOPitch()+diffY,false);
                if(!_timeLocked)
                {
                    w->setTime(w->getOTime()+diffX,false);
                }
            }
       }
   }
    else
    if(_isPlaying && _mousePressed)
    {
        _seekPosition = ((event->x())*_lastBeatDisplayed + ((width()-event->x()))*_firstBeatDisplayed)/((qreal)width());
         emitSeek();

    }



#ifndef UPDATE_BY_TIMER
    update();
#endif
/*
    QListIterator<Word *> Iwords(words);
            Word* tWord;

         while(Iwords.hasNext())
         {
              tWord=Iwords.next();
               if(tWord->getTime()+tWord->getLength()>=realHStartView)
              {
                  if(
                   break;
               }

         }
         while(Iwords.hasNext())
         {

            tWord=Iwords.next();
            if(tWord->getTime()+tWord->getLength()>realHEndView) break;
             renderWord(painter,tWord);

         }
*/

}

QRectF ShowSentenceWidget::scaleRect(qreal x, qreal y, qreal w, qreal h)
{
    return QRectF(scaledCoordinates(x,y), scaledCoordinates(x+w, y+h));
}
qreal ShowSentenceWidget::scaleWidth(qreal w)
{
    return w*(qreal)width()/(qreal)hScale;
}
qreal ShowSentenceWidget::scaleHeight(qreal h)
{
    return h*(qreal)height()/(qreal)vScale;
}

QPointF ShowSentenceWidget::scaledCoordinates(qreal x, qreal y)
{
    return QPoint((x - realHStartView + _gap)*(qreal)width()/(qreal)hScale, (y-vScroll*10.0)*(qreal)height()/(qreal)vScale);
}
QPointF ShowSentenceWidget::scaledCoordinates(const QPointF &point)
{
    return scaledCoordinates(point.x(), point.y());
}
QPointF ShowSentenceWidget::scaledCoordinates(const QPoint &point)
{
    return scaledCoordinates(point.x(), point.y());
}

void ShowSentenceWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);
     //painter.scale((float)width()/(float)hScale, (float)height()/(float)vScale);

    //painter.translate(-realHStartView+_gap,-vScroll*10.0);

//qDebug()<<(lyrics->getGap()/1000.0-floor(lyrics->getGap()/1000.0));
_firstBeatDisplayed = hScroll - _gap;
_lastBeatDisplayed = hScroll + hScale  - _gap;

_hSplitHCursor=_hSizeCursor=_sizeAllCursor=false;



int pas=100;
int opacity=200,sc=vScroll*10.0; //sc=vScroll*vScale/12, sc2=vScale+vScroll*vScale/8;


//backgroud Test_______________________


if(UInputManager::Instance.isKeyPressed(Qt::Key_S))
{


    painter.setPen(QPen(QColor(0,173,232,170)));

    painter.setBrush(QBrush(QColor(255,255,255,255)));


    painter.drawRect(QRectF(scaledCoordinates(_firstBeatDisplayed,sc),scaledCoordinates(_firstBeatDisplayed+30,sc+30)));


}

//____________________



     painter.setPen(QPen(QColor(0,0,0,170)));
     painter.setBrush(QBrush(QColor(0,255,255,255)));




     painter.setPen(QPen(QColor(0,173,232,170)));

     painter.setBrush(QBrush(QColor(255,255,255,255)));



      QTextOption numbreTextOption;
      numbreTextOption.setWrapMode(QTextOption::NoWrap);

      for(int i=ceil(vScroll*10.0/20);i<=ceil((vScroll*10.0+vScale)/20);i++)
     {
         painter.drawLine(scaledCoordinates(_firstBeatDisplayed,i*20),scaledCoordinates(_lastBeatDisplayed,i*20));
         


     }


      painter.setPen(QPen(QColor(0,0,0,linearRangeOpacity(1500, 7000,250,80))));
      //1500, 7000


// RENDER verticale lines
       if(!_isPlaying  || _mousePressed) //to go faster while playing
      {
           for(int i=_firstBeatDisplayed - ceil(mod(_firstBeatDisplayed,pas)) ; i<=_lastBeatDisplayed;i+=pas)
            {
                 painter.drawLine(scaledCoordinates(i,0).x(),0,scaledCoordinates(i,0).x(),height());
            }


            if(( opacity=expRangeOpacity(100,2000,200))>20)
            {
                //opacity=expRangeOpacity(100,1000,200);
                painter.setPen(QPen(QColor(0,0,0,opacity)));
               pas=10;
                for(int i=max(0,_firstBeatDisplayed-ceil(mod(_firstBeatDisplayed,pas)));i<=_lastBeatDisplayed;i+=pas)
                {
                     painter.drawLine(scaledCoordinates(i,0).x(), 0,scaledCoordinates(i,0).x(), height());
                }

                 if((opacity=expRangeOpacity(20,340,200))>20)
                {
                     ////qDebug()<<opacity;
                    painter.setPen(QPen(QColor(0,0,0,opacity)));

                   pas=1;

                   if(this->hScale>100) pas=2;

                    for(int i=max(0,_firstBeatDisplayed-ceil(mod(_firstBeatDisplayed,pas)));i<=_lastBeatDisplayed;i+=pas)
                    {
                         painter.drawLine(scaledCoordinates(i,0).x(), 0,scaledCoordinates(i,0).x(), height());
                    }
                }
           }
        }// if( RENDER verticale lines )

       if(!_mousePressed)
           _overSep=NULL;

       if(lyrics)
       {
            renderLyrics(&painter);
            sortSelected();
            renderPreviousSentence(&painter);
        }

// Draw cursor
        painter.setPen(QPen(QColor(255,0,0,255)));
        {
            qreal x = scaledCoordinates(_seekPosition,0).x();
            painter.drawLine(x,0,x,height());
        }






        // THE SELECTION____________________

        if(_clickAndMoveSelection || !_selected.empty())
        {
            //QMessageBox::warning(NULL,"","lol");
            painter.setBrush(QBrush(QColor(0,0,255,60)));
            painter.drawRect(QRectF(scaledCoordinates(_floatSelection[0],0).x(),0,scaleWidth(_floatSelection[1]-_floatSelection[0]), height()));
        }

        // END THE SELECTION__________________________


        if(_hSizeCursor)
        {
            this->setCursor(Qt::SizeHorCursor);
        }
        else
        if(_hSplitHCursor)
        {
            this->setCursor(Qt::SplitHCursor);
        }
        else
        if(_sizeAllCursor)
        {
            this->setCursor(Qt::SizeAllCursor);
        }
        else
        {
            this->setCursor(Qt::ArrowCursor);
        }


#ifdef DISPLAY_FPS
    parent->setWindowTitle(QString::number(time.restart()));
#endif



}


void ShowSentenceWidget::renderLyrics(QPainter * painter)
{
    _wordsDisplayed->clear();
    _overed=NULL;
    QFont font;
    font.setPixelSize(15);
    font.setFamily("Niagara");
    painter->setFont(font);

    foreach(Word* tWord,lyrics->words())
    {
        painter->setPen(QPen(QColor(0,0,0,170)));
        painter->setBrush(QBrush(QColor(0,173,232,170)));
        if(tWord->getTime()+tWord->getLength()>=_firstBeatDisplayed && tWord->getTime()<_lastBeatDisplayed)
        {
            _wordsDisplayed->push_back(tWord);
            if(tWord->isSeparator())
            {
                renderSeparator(painter, tWord);
            }
            else
            {
                renderWord(painter,tWord);
            }
        }

    }
}

void ShowSentenceWidget::deselect()
{
    Word * w;
    foreach(w,_selected)
    {
        w->setSelected(false);
    }
    _selected.clear();
}


bool ShowSentenceWidget::renderWord(QPainter * painter,Word * w)
{


    painter->setBrush(QBrush(QColor(0,173,232,170)));


    if(!_nextClick && mouseTime>w->getTime() && mouseTime<w->getTime()+w->getLength() &&
      mousePitch>w->getPitch() && mousePitch<w->getPitch()+2)
    {
        painter->setBrush(QBrush(QColor(232,173,0,170)));
        _overed=w;

       _sizeAllCursor=true;
    }
    else if(w->isGold())
    {
        painter->setBrush(QBrush(QColor(255,255,0,210)));
    }
    else if(w->isFree())
    {
        painter->setBrush(QBrush(QColor(232,173,0,170)));

        painter->setBrush(QBrush(QColor(0,0,0,40)));
    }
   else
   {
        painter->setBrush(QBrush(QColor(0,173,232,170)));
    }

   if(w->isSelected())
   {
       painter->setBrush(QBrush(QColor(255,173,0,255)));
   }


   QPointF p = scaledCoordinates(w->getTime(),(255-w->getPitch())*10+HAUTEUR_NOTE/2+5);
   painter->drawText(p.x(), p.y(),
           200,
           30,
           Qt::TextWordWrap,w->getText());

   p = scaledCoordinates(w->getTime(),(255-w->getPitch())*10-HAUTEUR_NOTE/2);
   QRectF r(p.x(), p.y(), scaleWidth(w->getLength()), scaleHeight(HAUTEUR_NOTE));
    if(80<this->hScale)
    {
          painter->drawRect(r);
    }
    else
    {
        painter->drawRoundedRect(r,
                                 scaleWidth(10.0/((float)width()/(float)hScale)),
                                 scaleHeight(10.0/((float)height()/(float)vScale)));
    }


    if(!_mousePressed && !_nextClick)
    {
        w->setOver(0);//if the mouse is pressed the word must remember where the mouse has begined to drop it

        if(mouseTime>w->getTime() && mouseTime<w->getTime() + min(w->getLength()/2.0,1.5) &&
          mousePitch>w->getPitch() && mousePitch<w->getPitch()+1  )
        {

            painter->setBrush(QBrush(QColor(0,0,0,100)));
            w->setOver(ShowSentenceWidget::OVER_LEFT);
            painter->drawRect(scaleRect(w->getTime(),(255-w->getPitch())*10,min(w->getLength()/2.0,1.5),HAUTEUR_NOTE/2));

            _hSizeCursor=true;
        }
        if(mouseTime<w->getTime()+w->getLength() && mouseTime>w->getTime()+w->getLength() - min(w->getLength()/2.0,1.5) &&
          mousePitch>w->getPitch() && mousePitch<w->getPitch()+1 )
        {

            painter->setBrush(QBrush(QColor(0,0,0,100)));
            w->setOver(ShowSentenceWidget::OVER_RIGHT);
            painter->drawRect(scaleRect(w->getTime()+w->getLength()-min(w->getLength()/2.0,1.5),(255-w->getPitch())*10,min(w->getLength()/2.0,1.5),HAUTEUR_NOTE/2));

            _hSizeCursor=true;
        }
    }


    return true;
// //qDebug()<<w->getPitch();
}


void ShowSentenceWidget::renderPreviousSentence(QPainter * /*painter*/)
{
    if(_wordsDisplayed->empty() || !_previousDisplayed) return;

    return;
    /** FIXEME*/
/*
    painter->setBrush(QBrush(QColor(0,0,0,40)));
    painter->setPen(QPen(QColor(0,0,0,0)));

    int add;

    foreach(Sentence * s,*lyrics->sentencesOfWords(_wordsDisplayed))
    {
        if(lyrics->getSentences()->indexOf(_wordsDisplayed->first()->getParent())<_previousDisplayed) continue;
        foreach(Word * w,*prevSent->getWords())
        {
            painter->drawRect(w->getTime()+add,(255-w->getPitch())*10-HAUTEUR_NOTE/2,w->getLength(),HAUTEUR_NOTE);
        }
    }*/
}

void ShowSentenceWidget::setHScale(int s)
{

        double temp=s;
    this->hScale=exp(temp/100.0);
    updateRangeView();
#ifndef UPDATE_BY_TIMER
    update();
#endif
}
void ShowSentenceWidget::setVScale(int s)
{

    this->vScale=s;

#ifndef UPDATE_BY_TIMER
    update();
#endif

}

int ShowSentenceWidget::expRangeOpacity(int a, int b,int opaque)
{
    if(hScale < (quint32)b && hScale > (quint32)a)
    {

        return ((float)(opaque))*exp(-(((float)(hScale-a))/(((float)(b-hScale))/3)));
    }
    if(hScale <= (quint32)a)
    {
        return  opaque;
    }
    return 0;
}

int ShowSentenceWidget::linearRangeOpacity(int a, int b,int op1,int op2)
{
   // bool sign=a<b

    if(hScale< (quint32)b && hScale> (quint32)a)
    {

        return   op1 + ((float)(op2-op1))*((float)(hScale-a))/((float)(b-a));//(((float)(b-hScale))/3)));
    }
    if(hScale<= (quint32)a)
    {
        return  op1;
    }
    return op2;
}


void ShowSentenceWidget::setLyrics(Lyrics * lyrics)
{
    this->lyrics=lyrics;

     _gap = (floor(lyrics->getGap())/1000.0)*lyrics->getBpm()/15.0f;

#ifndef UPDATE_BY_TIMER
    update();
#endif
}
void ShowSentenceWidget::updateGap(void)
{

     _gap = (floor(lyrics->getGap())/1000.0)*lyrics->getBpm()/15.0;


#ifndef UPDATE_BY_TIMER
    update();
#endif
}

void ShowSentenceWidget::setHScroll(int s)
{
   this->hScroll=s;
   updateRangeView();
#ifndef UPDATE_BY_TIMER
    update();
#endif
}

void ShowSentenceWidget::setVScroll(int s)
{
   this->vScroll=s;
#ifndef UPDATE_BY_TIMER
    update();
#endif
}

int ShowSentenceWidget::getMaximumHScroll()
{

    return 0;

}
int ShowSentenceWidget::getMaximumVScroll()
{
    return 0;
}

void ShowSentenceWidget::updateRangeView()
{
    this->realHEndView=(hScroll+hScale);
    this->realHStartView=(hScroll);
}
void ShowSentenceWidget::setSeekPosition(qreal beat)
{
    beat-=_gap;



    if(_seekPosition<_lastBeatDisplayed && beat>=_lastBeatDisplayed)
    {
        setHScroll(hScroll+hScale);
        emit autoScroll(hScroll);
    }

    if((!_selected.empty() || _clickAndMoveSelection) && _seekPosition < _floatSelection[1] && beat >= _floatSelection[1])
    {
        stop();
        _seekPosition = _floatSelection[0];

        emit haveToStop();
        emitSeek();
    }


    _seekPosition = beat;



#ifndef UPDATE_BY_TIMER
    update();
#endif

}

QList<Word*> * ShowSentenceWidget::getWordsDisplayedPtr()
{
    return _wordsDisplayed;



}
void ShowSentenceWidget::renderSeparator(QPainter * painter, Word * w)
{
    painter->setPen(QPen(QColor(100,255,100,210)));
    painter->setBrush(QBrush(QColor(100,255,100,210)));
    QRectF rect[3];


    qreal middle =  scaledCoordinates((w->getTime1()+w->getTime2())/2.0,0).x();
    qreal m = max(scaleWidth(w->getLength()+2), 20);
    rect[0] = QRectF(middle-m/2,0, m,15);

    qreal s = max(scaleWidth(w->getLength()/2.0), 8);
    rect[1] = QRectF(middle - s - 5, 18, s, 15);

    rect[2] = QRectF(middle+5, 18, s, 15);


    if(!_nextClick && _fMousePosition.x() > rect[0].left() - 1 &&
            _fMousePosition.x() < rect[0].right() + 1 &&
            _fMousePosition.y() > rect[0].top() &&
            _fMousePosition.y() < rect[0].bottom() &&
     (!_overSep || (_overSep == w && _overSep->getOver() == 0)) // if it's currently selected
     )
    {
        painter->setBrush(QBrush(QColor(255,100,100,210)));
        _hSplitHCursor=true;
        _overSep = w;
        w->setOver(0);
    }
    else
    {
        painter->setBrush(QBrush(QColor(100,255,100,210)));
    }

    painter->drawRect(rect[0]);


    if(!_nextClick && _fMousePosition.x() > rect[1].left() - 1 &&
      _fMousePosition.x() < rect[1].right() &&
      _fMousePosition.y() > rect[1].top() &&
      _fMousePosition.y() < rect[1].bottom() + 1 &&
     (!_overSep || (_overSep == w && _overSep->getOver() & ShowSentenceWidget::OVER_LEFT)) )
    {
        painter->setBrush(QBrush(QColor(255,100,100,210)));
        _hSizeCursor=true;
        _overSep = w;
        w->setOver(ShowSentenceWidget::OVER_LEFT);
    }
    else
    {
        painter->setBrush(QBrush(QColor(100,255,100,210)));
    }

    painter->drawRect(rect[1]);

    if(!_nextClick &&  _fMousePosition.x() > rect[2].left() - 1 &&
            _fMousePosition.x() < rect[2].right() + 1 &&
            _fMousePosition.y() > rect[2].top() &&
            _fMousePosition.y() < rect[2].bottom() &&
     (!_overSep || (_overSep == w && _overSep->getOver() & ShowSentenceWidget::OVER_RIGHT)))
    {
        painter->setBrush(QBrush(QColor(255,100,100,210)));
        _hSizeCursor=true;
        _overSep = w;
        w->setOver(ShowSentenceWidget::OVER_RIGHT);
    }
    else
    {
        painter->setBrush(QBrush(QColor(100,255,100,210)));
    }


    painter->drawRect(rect[2]);

    painter->setBrush(QBrush(QColor(100,255,100,210)));
    painter->drawRect(scaledCoordinates(w->getTime1(),0).x(),35,scaleWidth(w->getLength()+0.1),height()-30);

}

void ShowSentenceWidget::setNormal()
{
    Word * w;
    foreach(w,_selected)
    {
        w->setFree(false);
        w->setGold(false);
    }
}
void ShowSentenceWidget::setGold()
{
    Word * w;
    foreach(w,_selected)
    {
        w->setFree(false);
        w->setGold(true);
    }
}
void ShowSentenceWidget::setFree()
{
    Word * w;
    foreach(w,_selected)
    {
        w->setFree(true);
        w->setGold(false);
    }
}
void ShowSentenceWidget::fusion()
{
    if(_selected.count()<2)
    {
        QMessageBox::warning(this,tr("Attention"),tr("Il faut selectionner au moin deux notes"));
        return;
    }
    Word * newW = new Word(NULL,0,0,0);

    Word * w;

int fTime = _selected.first()->getTime()
        , lTime = _selected.first()->getTime() + _selected.first()->getLength()
        ,fPitch = _selected.first()->getPitch();

    foreach(w,_selected)
    {
        newW->setText(newW->getText()+w->getText());
        if(w->getTime() < fTime)
        {
            fTime = w->getTime();
            fPitch = w->getPitch();
        }
        if(w->getTime() + w->getLength() > lTime)
        {
            lTime = w->getTime() + w->getLength();
        }
        lyrics->removeWord(w);
        _selected.removeAll(w);
       delete w;

    }
    newW->setTime(fTime);
    newW->setLength(lTime - fTime);
    newW->setPitch(fPitch);
    lyrics->addWord(newW);

#ifndef UPDATE_BY_TIMER
    update();
#endif
}
void ShowSentenceWidget::scinder()
{
    if(_selected.count()>1 || _selected.empty())
    {
        QMessageBox::warning(this,tr("Attention"),tr("Il faut selectionner une seule note"));
        return;
    }

    Word * w =_selected.first();

    if(w->getLength()<2)
    {
        QMessageBox::warning(this,tr("Attention"),tr("La note doit avoir une longueur d'au moin 2"));
        return;
    }

    Word * newW = new Word(w->getParent(),w->getTime()+floor(w->getLength()/2),floor(w->getLength()/2),w->getPitch());

    QRegExp reg("[, -:!.]");

    QStringList strlist = w->getText().split(reg,QString::SkipEmptyParts);

    w->setLength(ceil(w->getLength()/2));

    if(strlist.count()<2)
    {
        lyrics->addWord(newW);
        newW->setText("~");
        return;
    }

    //newW->setText(strlist.last());
    newW->setText(w->getText().section(reg,-2,-1,QString::SectionSkipEmpty | QString::SectionIncludeLeadingSep));

    w->setText(w->getText().section(reg,0,-3,QString::SectionSkipEmpty | QString::SectionIncludeLeadingSep));
    lyrics->addWord(newW);

#ifndef UPDATE_BY_TIMER
    update();
#endif
}


void ShowSentenceWidget::nextClickAddNote()
{
    _nextClick=ShowSentenceWidget::NEXT_CLICK_ADD_NOTE;
            deselect();
}

void ShowSentenceWidget::nextClickAddSeparator()
{
    _nextClick=ShowSentenceWidget::NEXT_CLICK_ADD_SEPARATOR;
            deselect();
}

void ShowSentenceWidget::deleteNotes()
{
    foreach(Word *w, _selected)
    {
        lyrics->removeWord(w);
        _selected.removeOne(w);
        delete w;
    }
#ifndef UPDATE_BY_TIMER
    update();
#endif


}
void ShowSentenceWidget::setPreviousDisplayed(int n)
{
    _previousDisplayed = n;
#ifndef UPDATE_BY_TIMER
    update();
#endif
}

void ShowSentenceWidget::calquer()
{
    if(_selected.empty()) { return; }

    return;
    /** FIXEME */
/*
    if(lyrics->getSentences()->indexOf(_selected.first()->getParent())<_previousDisplayed) return;

         int add = _selected.first()->getParent()->getWords()->first()->getTime();

         Sentence * prevSent = lyrics->getSentences()->at(lyrics->getSentences()->indexOf(_selected.first()->getParent())-_previousDisplayed);


         if(prevSent->getWords()->empty()) return;

         if(prevSent->getSepBefore())
         {
             add-=prevSent->getWords()->first()->getTime();
         }



         int max = _floatSelection[1];


         if(_selected.first()->getParent() == _selected.last()->getParent()) // all the selected note are in the same sentence
         {
             //Sentence * p = _selected.first()->getParent();
             //if(p->getSepAfter());
         }
         else
         {
             if(_selected.first()->getParent()->getSepAfter())
             {
                max = _selected.first()->getParent()->getSepAfter()->getTime1();
             }
         }

         Word * newWord;

         QList<Word*> wordAdded;
       foreach(Word * w,*prevSent->getWords())
       {
           if(w->getTime()+add<max)
           {
               newWord = new Word(NULL,w->getTime()+add,w->getLength(),w->getPitch());
               wordAdded.push_back(newWord);
           }
       }

       if(wordAdded.empty()) return;

        QString str;

        foreach(Word*w,*_selected.first()->getParent()->getWords())
        {
            if(w->getTime()<max)
            {
                str.append(w->getText());
                lyrics->removeWord(w);
                _selected.removeAll(w);
                delete w;
            }
        }

        wordAdded.first()->setText(str);
        int k = 0;
        QString tempS;
        foreach(Word*w,wordAdded)
        {
            lyrics->addWord(w);
             if(k<str.count(QRegExp("[ ,'\"-;:!.]")))
            {
                 //QMessageBox::information(NULL,"",str.section(QRegExp("[ ,'\"-;:!.]"),k,k,QString::SectionIncludeLeadingSep));

                tempS = str.section(QRegExp("[ ,'\"-;:!.]"),k,k,QString::SectionIncludeLeadingSep);
                k++;
            }
            else
            {
                tempS="~";
            }

            if(k==wordAdded.count() && k<str.count(QRegExp("[ ,'\"-;:!.]")))
            {
                tempS=  str.section(QRegExp("[ ,'\"-;:!.]"),k,-1,QString::SectionIncludeLeadingSep);
            }

            w->setText((tempS.compare("")?tempS:"~"));
        }

        lyrics->addSeparator(wordAdded.first()->getTime()-2,0);


#ifndef UPDATE_BY_TIMER
    update();
#endif
*/
}
void ShowSentenceWidget::sortSelected()
{
    if(_selected.empty()) return;

    qSort(_selected.begin(),_selected.end(),Word::wordLessThanPtr);
}





void ShowSentenceWidget::contextMenuEvent(QContextMenuEvent * event)
{
    event->accept();
    QMenu menu(this);
    menu.addAction("test");
    menu.exec(event->globalPos());
}
