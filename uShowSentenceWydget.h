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


#ifndef SHOWSENTENCEWYDGET_H
#define SHOWSENTENCEWYDGET_H


#include <QTime>
 #include <QTimer>

#include "uShowLines.h"

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

public slots:
     void onKeyPressEvent(QKeyEvent*);
     void setGold(void);
     void setFree(void);
     void setNormal(void);

     void fusion(void);
     void scinder(void);
     void setPreviousDisplayed(int n);
     void calquer(void);

void nextClickAddSeparator(void);
void nextClickAddNote(void);

       void setHScale(int);
       void setVScale(int);
       void setHScroll(int);
       void setVScroll(int);
       void setSeekPosition(qreal);

       void deleteNotes();

       void play(void) { _isPlaying = true; };
       void stop(void) { _isPlaying = false; };

       void lockTime(bool n) { _timeLocked = n; };
public:

    quint16 getHScale(void) { return hScale; }
    void emitSeek();
    ShowSentenceWidget(UEditorWindow * parent);


    ~ShowSentenceWidget();
    void renderLyrics(QPainter * painter);
    void renderPreviousSentence(QPainter * painter);
    bool renderWord(QPainter * painter,Word * w);
    void setLyrics(Lyrics * lyrics);
    Lyrics * getLyrics() { return lyrics; }
    void updateGap(void);
    int currentBeat() { return _seekPosition; }

    int getMaximumHScroll();
    int getMaximumVScroll();

    QList<Word*> * getWordsDisplayedPtr(void);

    void deselect();

    enum { NEXT_CLICK_ADD_SEPARATOR=1, NEXT_CLICK_ADD_NOTE=2 };



protected:

    void sortSelected(void);

    quint8 _nextClick;

    quint8 _previousDisplayed;

    void renderSeparator(QPainter * painter, Word * w);
    bool _mousePressed, _isPlaying;
    float _gap;
    qreal _seekPosition;

    QList<Word*> * _wordsDisplayed;
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseDoubleClickEvent(QMouseEvent * event );
    void wheelEvent(QWheelEvent *);
    void paintEvent(QPaintEvent * event);

    quint32 hScale;
    quint16 vScale;
    quint16 hScroll;
    quint16 vScroll;

    QList<Word*> _selected;

    Word * _overed;
    Word * _overSep;

    QPointF _fPointPress;
    QPointF _fMousePosition;
    QTime _timePress;


    private:

    QRectF scaleRect(qreal x, qreal y, qreal w, qreal h);
    qreal scaleWidth(qreal w);
    qreal scaleHeight(qreal h);
    QPointF scaledCoordinates(qreal x, qreal y);
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

    double posXToBeat(double in_x);


    QTime time;
    Lyrics * lyrics;

    //QList<Word*> words;

    quint16 realVStartView;
    quint16 realVEndView;
    quint16 realHStartView;
    quint16 realHEndView;
    float mouseTime;
    float mousePitch;
    UEditorWindow * parent;
    void updateRangeView(void);

    float _floatSelection[2];

    double _firstBeatDisplayed,_lastBeatDisplayed;

    int expRangeOpacity(int a, int b,int opaque=255);
    int linearRangeOpacity(int a, int b,int op1=255,int op2=0);


};

#endif // SHOWSENTENCEWYDGET_H
