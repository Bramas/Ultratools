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

#include "uSentence.h"

class Lyrics : public QObject
{
    Q_OBJECT

signals:

    void hasBeenModified(void);
public slots:

    void sortAll();
    void doublePresicion();

public:


    void modified(QString sender="") { _modified=true; emit hasBeenModified(); };
    bool isModified() { return _modified; };
    void setModified(bool b=true) { if(b==true) modified(); else _modified=false; }


    Lyrics(QWidget * parent=0);
    int * parseCode(QString code);
    int * fromLines(QList<UAbstractLine*>* lines);

     QList<Sentence*> * getSentences(void);

    QList<Word*> * getAllWords(void) { return &words; }

    int getPitchMax(void);
    int getPitchMin(void);
    void setGap(float in) { _gap = in; };
    float getGap(void) { return _gap; };
    void setBpm(float in) { _bpm = in; };
    float getBpm(void) { return _bpm; };

    void sortThisWord(Word * w);
    void sortThisSeparator(USeparateur * s);
    USeparateur * addSeparator(int time, int length);
    void deleteSeparator(USeparateur *s);
    void addSentence(Sentence * sent);
    void removeSentence(Sentence * sent);

    void removeWord(Word * w);
    void addWord(Word * w);

     QList<USeparateur*> *  separatorsOfWords(QList<Word*> * list);
     QList<Sentence*> *  sentencesOfWords(QList<Word*> * list);


    void moveLeft(Word * from);
    Word * moveRight(Word *from, int indexIWant=0);

   // int pitchMax(void);

private:
    QWidget * parent;
    QList<Sentence*> sentences;

    QList<Word*> words;

    QList<UAbstractLine*> _lines;

    bool _modified;

    int  pitchMax, pitchMin;
    float _gap;
    float _bpm;
};

#endif // LYRICS_H
