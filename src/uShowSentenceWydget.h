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

#ifndef SHOWSENTENCEWYDGET_H
#define SHOWSENTENCEWYDGET_H


#include <QTime>
#include <QTimer>
#include <QSet>

#include "uShowLines.h"
#include "uWord.h"
#include "wordselection.h"

double min(double a,double b);
double max(double a,double b);
class UEditorWindow;

class ShowSentenceWidget : public QWidget
{
 Q_OBJECT

signals:

     void click(quint64);
     void autoScroll(int);
     void modified(void);
     void doubleClik(int);
     void selection(int,int);
     void haveToStop(void);
     void singleClik(void);
     void emptyClik(void);
     void floatSelection(double, double);
     void octaveChanged(int);

public slots:
     void onKeyPressEvent(QKeyEvent*);
     void setGold(void);
     void setFree(void);
     void setNormal(void);

     void fusion(void);
     void split(void);
     void setPreviousDisplayed(int n);
     void calquer(void);

void nextClickAddSeparator(void);
void nextClickAddNote(void);

       void setHScale(int);
       void setVScale(qreal);
       void setHScroll(int);
       void setVScroll(double);
       void setSeekPosition(qreal);

       void deleteNotes();

       void play(void) { _isPlaying = true; }
       void stop(void) { _isPlaying = false; }

       void lockTime(bool n) { _timeLocked = n; }
public:
       qreal duration();
       qreal startTime();

       int octaveOffset();

       quint32 getHScale(void) { return hScale; }
       int getHScroll(void) { return (int)hScroll; }
    void emitSeek();
    ShowSentenceWidget(UEditorWindow * parent);


    ~ShowSentenceWidget();
    void renderLyrics(QPainter * painter);
    void renderPreviousSentence(QPainter * painter);
    void renderSentence(QPainter *painter, const QList<Word> &words, int octave);
    bool renderWord(QPainter * painter, const Word &w, int octave);
    void setLyrics(Lyrics * lyrics);
    Lyrics * getLyrics() { return lyrics; }
    void updateGap(void);
    int currentBeat() { return _seekPosition; }

    int getMaximumHScroll();
    int getMaximumVScroll();

    QList<Word> &getWordsDisplayedPtr(void);

    void deselect();

    enum { NEXT_CLICK_ADD_SEPARATOR=1, NEXT_CLICK_ADD_NOTE=2 };



protected:


    quint8 _nextClick;

    quint8 _previousDisplayed;

    void renderSeparator(QPainter * painter, const Word &w);
    bool _mousePressed, _isPlaying, _mousePressdOnSelectedWord;
    double _gap;
    qreal _seekPosition;

    QList<Word> _wordsDisplayed;
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseDoubleClickEvent(QMouseEvent * event );
    void wheelEvent(QWheelEvent *);
    void paintEvent(QPaintEvent * event);
    void contextMenuEvent(QContextMenuEvent * event);

    int hScale;
    qreal vScale;
    int hScroll;
    double vScroll;

    WordSelection _selected;
    Word _overed;
    quint8 _overType, _overTypeOnMousePressed;

    QPointF _fPointPress;
    QPointF _fMousePosition;
    QTime _timePress;

    int _octaveOffset;


    private:

    QRectF scaleRect(qreal x, qreal y, qreal w, qreal h);
    qreal scaleWidth(qreal w);
    qreal scaleHeight(qreal h);
    QPointF scaledCoordinates(qreal x, int y);
    QPointF scaledCoordinates(const QPointF &);
    QPointF scaledCoordinates(const QPoint &);


    enum{
      OVER_LEFT=1<<1,OVER_RIGHT=1<<2
    };
    bool _hSizeCursor;
    bool _hSplitHCursor;
    bool _sizeAllCursor;
    bool _clickAndMoveSelection;
    bool _timeLocked;

    int _previousHistoryState;

    double posXToBeat(double in_x);
    qreal posXToMs(double in_x);


    QTime time;
    Lyrics * lyrics;


    quint16 realVStartView;
    quint16 realVEndView;
    quint16 realHStartView;
    quint16 realHEndView;
    double mouseTime;
    double mousePitch;
    double _verticalScrollBarValue;
    UEditorWindow * parent;
    void updateRangeView(void);

    double _floatSelection[2];

    double _firstBeatDisplayed,_lastBeatDisplayed;

    int expRangeOpacity(int a, int b,int opaque=255);
    int linearRangeOpacity(int a, int b,int op1=255,int op2=0);


};

#endif // SHOWSENTENCEWYDGET_H
