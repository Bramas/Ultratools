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


#include "uShowSentenceWydget.h"
#include "editorwindow.h"
#include <QMoveEvent>
#include <QMessageBox>
#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QScrollBar>
#include <QMenu>
#include <QAction>

#define TAILLE_FENETRE 1000
#define HAUTEUR_NOTE 2

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


ShowSentenceWidget::ShowSentenceWidget(UEditorWindow * parent) :
    _octaveOffset(0),
    _previousHistoryState(0),
    _verticalScrollBarValue(0)
{
    hScale=100;// nombre de deciseconds visible sur une fenettre
    vScale=20;
    _seekPosition=0;
    lyrics=0;
    setMouseTracking(true);
   this->parent=parent;
   mouseTime=0;
   _mousePressdOnSelectedWord = false;

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

    _overType = _overTypeOnMousePressed = 0;
     _mousePressed = _isPlaying = _clickAndMoveSelection = false;

     _fPointPress=QPointF(0.0,0.0);
     _timePress=QTime::currentTime();
    _hSizeCursor=_hSplitHCursor=_sizeAllCursor=_timeLocked=false;


        connect(&UInputManager::Instance, SIGNAL(keyPressEvent(QKeyEvent*, ulong)), this, SLOT(onKeyPressEvent(QKeyEvent*)));

}
ShowSentenceWidget::~ShowSentenceWidget()
{

}
void ShowSentenceWidget::mouseDoubleClickEvent(QMouseEvent * /*event*/)
{
    if(_selected.isEmpty())
    {
        emit doubleClik(-1);
        return;
    }


    emit doubleClik(_wordsDisplayed.indexOf(_selected.first()));

}

void ShowSentenceWidget::mousePressEvent(QMouseEvent *event)
{
    emit singleClik();
    _clickAndMoveSelection = false;
    _fPointPress = QPointF(event->x(),event->y());
    _timePress = QTime::currentTime();
    _mousePressed = true;
    _mousePressdOnSelectedWord = !_overed.isNull();
    _overTypeOnMousePressed = _overType;
    if(_previousHistoryState != lyrics->history().index())
    {
        _previousHistoryState = lyrics->history().index();
        lyrics->createEditGroup();
    }
    if(_nextClick)
    {
        if(_nextClick==ShowSentenceWidget::NEXT_CLICK_ADD_NOTE)
        {
            Word w(NULL,mouseTime,4,mousePitch);
            w.setText("~");
            lyrics->addWord(w);
            _selected << w;
            emit modified();

        }else
        if(_nextClick==ShowSentenceWidget::NEXT_CLICK_ADD_SEPARATOR)
        {
            lyrics->addSeparator(mouseTime);
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
        _selected.remove(_overed);

        if(!_selected.isEmpty())
        {
            emit selection(_selected.firstIndex(),_selected.lastIndex());
        }
    }
    else
    if(!_selected.contains(_overed) && !_overed.isNull())
    {
        _selected << _overed;
        emit selection(_selected.firstIndex(),_selected.lastIndex());;
    }
    else
    if(_overed.isNull())
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
        value -= event->delta()/30.0;
        parent->horizontalScrollBar()->setValue(value);
    }
    else
    {
        int value = parent->verticalScrollBar()->value();
#ifdef __APPLE__
        value -= event->delta()/20.0;
#else
        value -= event->delta()/30.0;
#endif
        parent->verticalScrollBar()->setValue(value);
    }
    event->accept();
}

int ShowSentenceWidget::octaveOffset()
{
    return _octaveOffset;
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
    if(_previousHistoryState != lyrics->history().index())
    {
        _previousHistoryState = lyrics->history().index();
        lyrics->createEditGroup();
    }
   _mousePressed = false;
   QPointF pointRealease(event->x(),event->y());


   if((pointRealease-_fPointPress).manhattanLength()<10 && _timePress.msecsTo(QTime::currentTime())<500 && _overed.isNull())
   {
       //it is a single click

       _seekPosition = posXToBeat(event->x());

        emitSeek();
        _clickAndMoveSelection = false;
        emit floatSelection(-1, -1);

   }

    if(_clickAndMoveSelection)
    {
        _seekPosition = posXToBeat(min(_fPointPress.x(),event->x()));
        emitSeek();

    }


    if(!_clickAndMoveSelection && !_selected.isEmpty() && !_isPlaying)
    {
        QPair<int,int> range(_selected.first().getTime(), _selected.last().getTime2());
        _floatSelection[0] = range.first;
        _floatSelection[1] = range.second;
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
    quint64 msc=(1000.0f*(_seekPosition+_gap)*15.0/lyrics->getBpm());

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
        _selected.translate(0,1);
    }
    else if(event->key() == Qt::Key_Down)
    {
        _selected.translate(0,-1);
    }
    else if(event->key() == Qt::Key_Left)
    {
        _selected.translate(-1,0);
    }
    else if(event->key() == Qt::Key_Right)
    {
        _selected.translate(1,0);
    }
    update();
}

void ShowSentenceWidget::mouseMoveEvent ( QMouseEvent * event )
{
    _fMousePosition.setX(event->x());
    _fMousePosition.setY(event->y());


    mouseTime=(_lastBeatDisplayed-_firstBeatDisplayed)*event->x()/(qreal)width()+_firstBeatDisplayed;
    mousePitch=vScroll+ (vScale)*((qreal)(height()-event->y()))/((qreal)height());

    qreal fDiffY = mousePitch - (vScale*(height()-_fPointPress.y())/(qreal)height()+vScroll);
    qreal fDiffX = mouseTime - ((_lastBeatDisplayed-_firstBeatDisplayed)*_fPointPress.x()/(qreal)width()+_firstBeatDisplayed);

    int diffY = fDiffY > 0 ? floor(fDiffY) : ceil(fDiffY);
    int diffX = fDiffY > 0 ? floor(fDiffX) : ceil(fDiffX);


   if(_mousePressed && !_isPlaying && (_fMousePosition-_fPointPress).manhattanLength()<10 && _timePress.msecsTo(QTime::currentTime())<500 && !_mousePressdOnSelectedWord)
    {
        _clickAndMoveSelection = true;
    }

    if(_mousePressed && _mousePressdOnSelectedWord)
    {
        if(diffX != 0 || diffY != 0)
        {
            if(_selected.count() == 1 && _overTypeOnMousePressed == ShowSentenceWidget::OVER_LEFT)
            {
                if(diffX)
                {
                    int effectiveXMove = -_selected.expandLeft(-diffX);
                    _fPointPress += QPointF(effectiveXMove*width()/(_lastBeatDisplayed-_firstBeatDisplayed), 0);
                }
            }
            else
            if(_selected.count() == 1 && _overTypeOnMousePressed == ShowSentenceWidget::OVER_RIGHT)
            {
                if(diffX)
                {
                    int effectiveXMove = _selected.expandRight(diffX);
                    _fPointPress += QPointF(effectiveXMove*width()/(_lastBeatDisplayed-_firstBeatDisplayed), 0);
                }
            }
            else
            {
                 QPoint effectiveMove = _selected.translate(_timeLocked ? 0 : diffX, diffY);
                _fPointPress += QPointF(effectiveMove.x()*width()/(_lastBeatDisplayed-_firstBeatDisplayed), -effectiveMove.y()*height()/vScale);
            }
        }
    }
    else
    if(_mousePressed && _clickAndMoveSelection)
    {
        _floatSelection[0] = posXToBeat(min(_fPointPress.x(),_fMousePosition.x()));
        _floatSelection[1] = posXToBeat(max(_fPointPress.x(),_fMousePosition.x()));
        emit floatSelection(posXToMs(min(_fPointPress.x(),_fMousePosition.x())), posXToMs(max(_fPointPress.x(),_fMousePosition.x())));


        deselect();

        foreach(const Word & w, _wordsDisplayed)
        {
             if(w.getTime()<_floatSelection[1]
                 && w.getTime()+w.getLength()>_floatSelection[0])
             {
                     _selected << w;
              }
        }
        if(_selected.isEmpty())
        {

        }
        else
        {
            emit selection(_selected.firstIndex(),_selected.lastIndex());
        }

    }
    else
   if(_mousePressed && !_selected.isEmpty() && (!UInputManager::Instance.isKeyPressed(Qt::Key_Control) || _selected.count()==1))
   {

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
}

QRectF ShowSentenceWidget::scaleRect(qreal x, qreal y, qreal w, qreal h)
{
    return QRectF(scaledCoordinates(x,y+h), scaledCoordinates(x+w, y));
}
qreal ShowSentenceWidget::scaleWidth(qreal w)
{
    return w*(qreal)width()/(qreal)hScale;
}
qreal ShowSentenceWidget::scaleHeight(qreal h)
{
    return h*(qreal)height()/(qreal)vScale;
}

QPointF ShowSentenceWidget::scaledCoordinates(qreal x, int y)
{
    return QPoint((x - realHStartView + _gap)*(qreal)width()/(qreal)hScale, height() - (y-vScroll)*height()/(qreal)vScale);
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

    _firstBeatDisplayed = hScroll - _gap;
    _lastBeatDisplayed = hScroll + hScale  - _gap;

    _hSplitHCursor=_hSizeCursor=_sizeAllCursor=false;





    int pas=100;
    int opacity=200;

    //backgroud Test_______________________


    if(UInputManager::Instance.isKeyPressed(Qt::Key_S))
    {
        painter.setPen(QPen(QColor(0,173,232,170)));
        painter.setBrush(QBrush(QColor(255,255,255,255)));
        //painter.drawRect(QRectF(scaledCoordinates(_firstBeatDisplayed,sc),scaledCoordinates(_firstBeatDisplayed+30,sc+30)));
    }

    //____________________


     painter.setPen(QPen(QColor(0,173,232,170)));
     painter.setBrush(QBrush(QColor(255,255,255,255)));



    QTextOption numbreTextOption;
    numbreTextOption.setWrapMode(QTextOption::NoWrap);

// RENDER horizontal lines
    for(int i = vScroll - (((int)vScroll)%2); i<=vScroll+vScale; i+=2)
    {
        painter.drawLine(scaledCoordinates(_firstBeatDisplayed,i),scaledCoordinates(_lastBeatDisplayed,i));
    }


      painter.setPen(QPen(QColor(0,0,0,linearRangeOpacity(1500, 7000,250,80))));


// RENDER verticale lines
      if(!_isPlaying  || _mousePressed) //to go faster while playing
      {
           pas=32;
           for(int i=max(0,_firstBeatDisplayed - ceil(mod(_firstBeatDisplayed,pas))) ; i<=_lastBeatDisplayed;i+=pas)
            {
                 painter.drawLine(scaledCoordinates(i,0).x(),0,scaledCoordinates(i,0).x(),height());
            }

            if(( opacity=expRangeOpacity(100,2000,200))>20)
            {
               painter.setPen(QPen(QColor(0,0,0,opacity)));
               pas=8;
                for(int i=max(0,_firstBeatDisplayed-ceil(mod(_firstBeatDisplayed,pas)));i<=_lastBeatDisplayed;i+=pas)
                {
                     painter.drawLine(scaledCoordinates(i,0).x(), 0,scaledCoordinates(i,0).x(), height());
                }

                 if((opacity=expRangeOpacity(20,340,200))>20)
                {
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


       if(lyrics)
       {
            renderLyrics(&painter);
            renderPreviousSentence(&painter);
        }

// Draw cursor
        painter.setPen(QPen(QColor(255,0,0,255)));
        {
            qreal x = scaledCoordinates(_seekPosition,0).x();
            painter.drawLine(x,0,x,height());
        }




        // THE SELECTION____________________

        if(_clickAndMoveSelection || !_selected.isEmpty())
        {
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
    parent->setWindowTitle(QString::number(1000/time.restart()));
#endif



}


void ShowSentenceWidget::renderLyrics(QPainter * painter)
{
    _overType = 0;
    _overed = Word();

    _wordsDisplayed.clear();
    QFont font;
    font.setPixelSize(15);
    font.setFamily("Niagara");
    painter->setFont(font);

    if(lyrics->words().isEmpty())
        return;

    int octaveMax, octaveMin;
    octaveMin = octaveMax = floor(lyrics->words().first().getPitch()/12.0);

    auto wordIt = lyrics->words().constBegin();

    QList<Word> currentSentence;
    while(wordIt != lyrics->words().constEnd())
    {
        if((*wordIt).isSeparator())
        {
            currentSentence << *wordIt;
            renderSentence(painter, currentSentence, octaveMin);
            if(_seekPosition >= currentSentence.first().getTime() && _seekPosition < currentSentence.last().getTime())
            {
                if(_octaveOffset != octaveMin)
                {
                    _octaveOffset = octaveMin;
                    emit octaveChanged(_octaveOffset);
                }
            }
            currentSentence.clear();
            if(wordIt + 1 != lyrics->words().constEnd())
            {
                octaveMin = octaveMax = (*(wordIt+1)).getPitch()/12;
            }
        }
        else
        {
            octaveMin = min(octaveMin, floor((*(wordIt)).getPitch()/12.0));
            octaveMax = max(octaveMax, floor((*(wordIt)).getPitch()/12));
        }
        if((*wordIt).getTime()+(*wordIt).getLength()>=_firstBeatDisplayed && (*wordIt).getTime()<_lastBeatDisplayed)
        {
            currentSentence << *wordIt;
            _wordsDisplayed << *wordIt;
        }
        else if(wordIt->isSeparator())
              currentSentence << *wordIt; // awlays add the first separator of the sentence even if it is not displayed
        ++wordIt;
    }
    renderSentence(painter, currentSentence, octaveMin);
}

void ShowSentenceWidget::deselect()
{
    _selected = WordSelection(lyrics);
}

void ShowSentenceWidget::renderSentence(QPainter *painter, const QList<Word> &words, int octave)
{
    /*if(words.count() >= 3)
    {
        painter->save();
        QFont f = painter->font();
        f.setPixelSize(13);
        painter->setFont(f);
        qreal left = 0;
        if(words.first().isSeparator()) //if it is not the first sentence
            left = scaledCoordinates(words.first().getTime1(),0).x();
        qreal right = scaledCoordinates(words.last().getTime1(),0).x();

        painter->setPen(QPen(QColor(100,100,100)));
        //painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(QColor(200,200,200)));
        //painter->drawRect(scaledCoordinates(left,0).x(), height(),scaleWidth(right-left), 30);

        QString text = tr("Octave offset %1 (pitch + %2)").arg(QString::number(octave)).arg(QString::number(octave*12));
        painter->drawText(min(max(0,left), right - QFontMetrics(painter->font()).width(text) - 10), height()+28, text);

        painter->restore();
    }*/

    foreach(const Word & w, words)
    {
        if(w.isSeparator()){
            renderSeparator(painter, w);
        } else {
            renderWord(painter, w, octave);
        }
    }
}

bool ShowSentenceWidget::renderWord(QPainter * painter, const Word & w, int octave)
{

    painter->setPen(QPen(QColor(0,0,0,170)));
    painter->setBrush(QBrush(QColor(0,173,232,170)));

    int pitch = -octave*12 + w.getPitch();
    if(!_nextClick && mouseTime>w.getTime() && mouseTime<w.getTime()+w.getLength() &&
      mousePitch > pitch-1 && mousePitch < pitch + 1)
    {
        painter->setBrush(QBrush(QColor(232,173,0,170)));
        _overed=w;
       _sizeAllCursor=true;
    }
    else if(w.isGold())
    {
        painter->setBrush(QBrush(QColor(255,255,0,210)));
    }
    else if(w.isFree())
    {
        painter->setBrush(QBrush(QColor(232,173,0,170)));
        painter->setBrush(QBrush(QColor(0,0,0,40)));
    }
   else
   {
        painter->setBrush(QBrush(QColor(0,173,232,170)));
    }

   if(_selected.contains(w))
   {
       painter->setBrush(QBrush(QColor(255,173,0,255)));
   }


   QPointF p = scaledCoordinates(w.getTime(),pitch+HAUTEUR_NOTE/2);
   painter->drawText(p.x(), p.y()-QFontMetrics(painter->font()).height(),
           200,
           QFontMetrics(painter->font()).height(),
           Qt::TextWordWrap,w.getText());

   p = scaledCoordinates(w.getTime(),pitch+HAUTEUR_NOTE/2);
   QRectF r(p.x(), p.y(), scaleWidth(w.getLength()), scaleHeight(HAUTEUR_NOTE));
    if(150<this->hScale)
    {
          painter->drawRect(r);
    }
    else
    {
        painter->drawRoundedRect(r,
                                 scaleWidth(10.0/((double)width()/(double)hScale)),
                                 scaleHeight(10.0/((double)height()/(double)vScale)));
    }


    if(!_mousePressed && !_nextClick)
    {

        if(mouseTime>w.getTime() && mouseTime<w.getTime() + min(w.getLength()/2.0,1.5) &&
          mousePitch>pitch && mousePitch<pitch+1  )
        {

            painter->setBrush(QBrush(QColor(0,0,0,100)));
            _overType = ShowSentenceWidget::OVER_LEFT;
            painter->drawRect(scaleRect(w.getTime(),pitch,min(w.getLength()/2.0,1.5),HAUTEUR_NOTE/2));

            _hSizeCursor=true;
        }
        if(mouseTime<w.getTime()+w.getLength() && mouseTime>w.getTime()+w.getLength() - min(w.getLength()/2.0,1.5) &&
          mousePitch>pitch && mousePitch<pitch+1 )
        {

            painter->setBrush(QBrush(QColor(0,0,0,100)));
            _overType = ShowSentenceWidget::OVER_RIGHT;
            painter->drawRect(scaleRect(w.getTime()+w.getLength()-min(w.getLength()/2.0,1.5),pitch,min(w.getLength()/2.0,1.5),HAUTEUR_NOTE/2));

            _hSizeCursor=true;
        }
    }
    return true;
}


void ShowSentenceWidget::renderPreviousSentence(QPainter * painter)
{
    if(_wordsDisplayed.empty() || !_previousDisplayed) return;

    painter->setBrush(QBrush(QColor(0,0,0,40)));
    painter->setPen(QPen(QColor(0,0,0,0)));

    foreach(const Word & wd, _wordsDisplayed)
    {
        QList<Word> sentence = lyrics->sentencesOfWord(wd);

        if(wd.isSeparator() || (wd != sentence.first() && wd != _wordsDisplayed.first()))
        {
            // we draw the sentence once
            continue;
        }

        auto wordIt = lyrics->find(sentence.first());

        int nbSkip = _previousDisplayed + 1;
        while(nbSkip > 0 && wordIt != lyrics->words().constBegin())
        {
            --wordIt;
            while(wordIt != lyrics->words().constBegin() && !(*wordIt).isSeparator())
                --wordIt;
            --nbSkip;
        }
        if(nbSkip > 0)
        {
            continue;
        }
        if(!(*wordIt).isSeparator())
        {
            wordIt = lyrics->words().constBegin();
        }
        else
        {
            ++wordIt;
        }
        if((*wordIt).isSeparator())
        {
            continue;
        }

        int add = sentence.first().getTime() - (*wordIt).getTime();

        auto lastIt = lyrics->find(sentence.last());
        int maxTime = (*lastIt).getTime2() + add;
        if(lastIt + 1 != lyrics->words().constEnd())
        {
            maxTime =  (*(lastIt+1)).getTime();
        }


        while(wordIt != lyrics->words().constEnd() && !(*wordIt).isSeparator())
        {
            if((*wordIt).getTime()+add >= maxTime)
            {
                break;
            }
            QPointF p = scaledCoordinates((*wordIt).getTime()+add,(*wordIt).getPitch()+HAUTEUR_NOTE/2);
            QRectF r(p.x(), p.y(), scaleWidth((*wordIt).getLength()), scaleHeight(HAUTEUR_NOTE));

            painter->drawRect(r);
            ++wordIt;
        }
    }
}

void ShowSentenceWidget::setHScale(int s)
{

        this->hScale=s;//exp(s/100.0);


    updateRangeView();
#ifndef UPDATE_BY_TIMER
    update();
#endif
}
void ShowSentenceWidget::setVScale(qreal s)
{

    this->vScale = max(1, s);

#ifndef UPDATE_BY_TIMER
    update();
#endif

}

int ShowSentenceWidget::expRangeOpacity(int a, int b,int opaque)
{
    if(hScale < b && hScale > a)
    {

        return opaque*exp(-(hScale-a)*3.0/(b-hScale));
    }
    if(hScale <= a)
    {
        return  opaque;
    }
    return 0;
}

int ShowSentenceWidget::linearRangeOpacity(int a, int b,int op1,int op2)
{
    if(hScale< b && hScale> a)
    {
        return   op1 + (op2-op1)*(hScale-a)/(double)(b-a);
    }
    if(hScale<= a)
    {
        return  op1;
    }
    return op2;
}


void ShowSentenceWidget::setLyrics(Lyrics * lyrics)
{
    this->lyrics=lyrics;
    _selected = WordSelection(lyrics);

     _gap = (floor(lyrics->getGap())/1000.0)*lyrics->getBpm()/15.0;
    connect(lyrics, SIGNAL(hasBeenModified()), this, SLOT(update()));
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

void ShowSentenceWidget::setVScroll(double s)
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

    if((!_selected.isEmpty() || _clickAndMoveSelection) && _seekPosition < _floatSelection[1] && beat >= _floatSelection[1])
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

QList<Word>&  ShowSentenceWidget::getWordsDisplayedPtr()
{
    return _wordsDisplayed;



}
void ShowSentenceWidget::renderSeparator(QPainter * painter, const Word & w)
{
    painter->setPen(QPen(QColor(100,255,100,210)));
    painter->setBrush(QBrush(QColor(100,255,100,60)));
    QRectF rect[3];


    qreal middle =  scaledCoordinates((w.getTime1()+w.getTime2())/2.0,0).x();
    qreal m = max(scaleWidth(w.getLength()+2), 20);
    rect[0] = QRectF(middle-m/2,0, m,15);

    qreal s = max(scaleWidth(w.getLength()/2.0), 8);
    rect[1] = QRectF(middle - s - 5, 18, s, 15);

    rect[2] = QRectF(middle+5, 18, s, 15);


    if(!_nextClick && _fMousePosition.x() > rect[0].left() - 1 &&
            _fMousePosition.x() < rect[0].right() + 1 &&
            _fMousePosition.y() > rect[0].top() &&
            _fMousePosition.y() < rect[0].bottom() &&
     (_overed.isNull() || (_overed == w && _overType == 0)) // if it's currently selected
     )
    {
        painter->setBrush(QBrush(QColor(255,100,100,60)));
        _hSplitHCursor=true;
        _overed = w;
    }
    else
    {
        painter->setBrush(QBrush(QColor(100,255,100,60)));
    }

    painter->drawRect(rect[0]);


    if(!_nextClick && _fMousePosition.x() > rect[1].left() - 1 &&
      _fMousePosition.x() < rect[1].right() &&
      _fMousePosition.y() > rect[1].top() &&
      _fMousePosition.y() < rect[1].bottom() + 1 &&
     (_overed.isNull() || (_overed == w && _overType & ShowSentenceWidget::OVER_LEFT)) )
    {
        painter->setBrush(QBrush(QColor(255,100,100,60)));
        _hSizeCursor=true;
        _overed = w;
        _overType = ShowSentenceWidget::OVER_LEFT;
    }
    else
    {
        painter->setBrush(QBrush(QColor(100,255,100,60)));
    }

    painter->drawRect(rect[1]);

    if(!_nextClick &&  _fMousePosition.x() > rect[2].left() - 1 &&
            _fMousePosition.x() < rect[2].right() + 1 &&
            _fMousePosition.y() > rect[2].top() &&
            _fMousePosition.y() < rect[2].bottom() &&
     (_overed.isNull() || (_overed == w && _overType & ShowSentenceWidget::OVER_RIGHT)))
    {
        painter->setBrush(QBrush(QColor(255,100,100,60)));
        _hSizeCursor=true;
        _overed = w;
        _overType = ShowSentenceWidget::OVER_RIGHT;
    }
    else
    {
        painter->setBrush(QBrush(QColor(100,255,100,60)));
    }


    painter->drawRect(rect[2]);

    painter->setBrush(QBrush(QColor(100,255,100,60)));
    painter->drawRect(scaledCoordinates(w.getTime1(),0).x(),35,scaleWidth(w.getLength()+0.1),height()-30);

}

void ShowSentenceWidget::setNormal()
{
    _selected.setType(Word::Normal);
}
void ShowSentenceWidget::setGold()
{
    _selected.setType(Word::Gold);
}
void ShowSentenceWidget::setFree()
{
    _selected.setType(Word::Free);
}
void ShowSentenceWidget::fusion()
{
    if(_selected.count()<2)
    {
        QMessageBox::warning(this,tr("Attention"),tr("Il faut selectionner au moin deux notes"));
        return;
    }

    _selected.merge();

#ifndef UPDATE_BY_TIMER
    update();
#endif
}
void ShowSentenceWidget::split()
{
    if(_selected.count()>1 || _selected.isEmpty())
    {
        QMessageBox::warning(this,tr("Attention"),tr("Il faut selectionner une seule note"));
        return;
    }

    Word w =_selected.first();

    if(w.getLength()<2)
    {
        QMessageBox::warning(this,tr("Attention"),tr("La note doit avoir une longueur d'au moin 2"));
        return;
    }

    lyrics->createEditGroup();
    int length = floor(w.getLength()/2);

    lyrics->removeWord(w);


    QRegExp reg("[, -:!.]");
    QStringList strlist = w.getText().split(reg,QString::SkipEmptyParts);

    w.setLength(w.getLength() - length);


    Word newW(w.getParent(),w.getTime2(),length,w.getPitch());
    if(strlist.count()<2)
    {
        newW.setText("~");
    }
    else
    {
        newW.setText(w.getText().section(reg,-2,-1,QString::SectionSkipEmpty | QString::SectionIncludeLeadingSep));
        w.setText(w.getText().section(reg,0,-3,QString::SectionSkipEmpty | QString::SectionIncludeLeadingSep));
    }



    lyrics->addWord(w);
    lyrics->addWord(newW);

    lyrics->createEditGroup();
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
    _selected.deleteSelectedWords();
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
    if(_selected.isEmpty()) { return; }

    Word firstWord = _selected.first();
    auto  firstSentenceWordIt = lyrics->words().constEnd();
    QList<Word> originSentence;
    QList<Word> destinationSentence;

    auto wordIt = lyrics->find(firstWord);
    // ignore _previousDisplay separator to find the origin sentence
    int nbSkip = _previousDisplayed + 1;
    while(nbSkip > 0 && wordIt != lyrics->words().constBegin())
    {
        --wordIt;
        while(wordIt != lyrics->words().constBegin() && !(*wordIt).isSeparator())
            --wordIt;
        if(firstSentenceWordIt == lyrics->words().constEnd())
        {
            firstSentenceWordIt = wordIt + 1;
        }
        --nbSkip;
    }
    if(nbSkip > 0)
    {
        return;
    }
    if(!(*wordIt).isSeparator())
    {
        wordIt = lyrics->words().constBegin();
    }
    else
    {
        ++wordIt;
    }
    if((*wordIt).isSeparator())
    {
        return;
    }

    // fill originSentence with the words of the sentence we want to match
    while(wordIt != lyrics->words().constEnd() && !(*wordIt).isSeparator())
    {
        originSentence << *wordIt;
        ++wordIt;
    }
    if(originSentence.empty())
    {
        return;
    }


    // time to add to the time of the word we want to match.
    int add = (*firstSentenceWordIt).getTime() - originSentence.first().getTime();

    wordIt = firstSentenceWordIt;
    // fill destinationSentence with the words of the sentence we want to replace
    while(wordIt != lyrics->words().constEnd()
          && !(*wordIt).isSeparator()
          && (destinationSentence.size() < originSentence.size()
              || (*wordIt).getTime() < originSentence.last().getTime() + add))
    {
        destinationSentence << *wordIt;
        ++wordIt;
    }
    if(destinationSentence.empty())
    {
        return;
    }

    // the maximum possible time is time of the next separator (or a dummy value if it is the last sentence)
    int maxAllowedTime = lyrics->words().last().getTime() + add;
    if(wordIt != lyrics->words().constEnd())
    {
        maxAllowedTime = (*wordIt).getTime();
    }



    QList<Word> wordAdded;
    foreach(const Word & w, originSentence) // create a new word for each word in the origin sentence
    {
        if( w.getTime() + add < maxAllowedTime)
        {
            Word newWord(0, w.getTime()+add, w.getLength(), w.getPitch());
            newWord.setText("~");
            wordAdded << newWord;
        }
    }

    QList<Word> wordRemoved;
    foreach(const Word &w, destinationSentence)
    {
        if(w.getTime() < maxAllowedTime)
        {
            wordRemoved << w;
        }
    }


    if(wordAdded.count()==wordRemoved.count())
    {
        for(int i=0;i<wordAdded.count();++i)
        {
            wordAdded[i].setText(wordRemoved.at(i).getText());
        }
    }
    else
    if(wordAdded.count()>wordRemoved.count())
    {
        for(int i=0;i<wordRemoved.count();++i)
        {
            wordAdded[i].setText(wordRemoved.at(i).getText());
        }

    }
    else
    {
        for(int i=0;i<wordAdded.count();++i)
        {
            wordAdded[i].setText(wordRemoved.at(i).getText());
        }
        for(int i=wordAdded.count();i<wordRemoved.count();++i)
        {
            wordAdded.back().setText(wordAdded.back().getText()+wordRemoved.at(i).getText());
        }

    }

    foreach(const Word &w,wordRemoved)
    {
        lyrics->removeWord(w);
    }
    foreach(const Word &w,wordAdded)
    {
        lyrics->addWord(w);
    }


#ifndef UPDATE_BY_TIMER
    update();
#endif
}




void ShowSentenceWidget::contextMenuEvent(QContextMenuEvent * event)
{
    event->ignore();
    /* maybe available in the next version
    event->accept();
    QMenu menu(this);
    menu.addAction("test");
    menu.exec(event->globalPos());
    */
}
