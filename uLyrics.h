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


#ifndef LYRICS_H
#define LYRICS_H

#include "uWord.h"

class Lyrics : public QObject
{
    Q_OBJECT

signals:

    void hasBeenModified(void);
public slots:

    void sortAll();
    void doublePresicion();

public:


    Lyrics(QWidget * parent=0);
    void parseLine(QString &line);
    void parseCode(QString &code);

    void modified(QString sender="") { _modified=true; emit hasBeenModified(); }
    bool isModified() { return _modified; }
    void setModified(bool b=true) { if(b==true) modified(); else _modified=false; }


    const QList<Word*>& words(void) const { return _words; }
    QList<Word*>& words(void) { return _words; }

    int getPitchMax(void);
    int getPitchMin(void);
    void setGap(qreal in) { _gap = (in < 0 ? 0 : in); }
    qreal getGap(void) { return _gap; }
    void setBpm(float in) { _bpm = in; }
    qreal getBpm(void) { return _bpm; }

    void resortWord(Word * w);
    Word* addSeparator(int time);
    void removeWord(Word * w);
    void addWord(Word *ws);

     QList<Word*> *  separatorsOfWords(QList<Word*> * list);
     QList<Word*> *  sentencesOfWords(QList<Word*> * list);

     bool setDelay(int delay, quint64 from=0);
     qreal timeToBeat(quint64 time)
     {
         return (time/1000.0) * _bpm/15.0f;
     }
     quint64 beatToMsc(int n)
     {
          return _gap + (n)*1000.0 * 15.0f/_bpm;
     }


    void moveLeft(Word * from);
    Word * moveRight(Word *from, int indexIWant=0);


private:
    QWidget * parent;
    QList<Word*> _words;

    bool _modified;

    int  pitchMax, pitchMin;
    qreal _gap;
    qreal _bpm;
};

#endif // LYRICS_H
