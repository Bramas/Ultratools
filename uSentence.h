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


#ifndef SENTENCE_H
#define SENTENCE_H
 #include <QList>
#include "uWord.h"

class Lyrics;

class Sentence
{
public:

    void modified(QString sender="");

    Sentence(Lyrics * parent, int timeBefore=0, int timeAfter=0);
    void setExtremity(int before,int after);
    int getStart(void);
    int getEnd(void);
    int getPitchMax(void);
    int getPitchMin(void);
    void addWord(Word * w);
    void addWords(QList<Word*> ws);

    Lyrics * getParent(){ return _parent; };

   static Sentence * parseSentence(Lyrics * parent,QString code);
QList<Word*> * getWords(void);

void setSepAfter(USeparateur * sep) { _sepAfter = sep; if(_sepAfter) _sepAfter->setLeftSentence(this); };
void setSepBefore(USeparateur * sep) { _sepBefore = sep; if(_sepBefore) _sepBefore->setRightSentence(this); };

USeparateur * getSepAfter() { return _sepAfter; }
USeparateur * getSepBefore() { return _sepBefore; }

int compare(Sentence * other) {
    if(words.count() != other->getWords()->count())
    {
        return words.count()-other->getWords()->count();
    }
    if(*words.first() != * other->getWords()->first())
    {
        return 1;
    }
    return 0; }


private:

    Lyrics * _parent;
    USeparateur * _sepBefore;
    USeparateur * _sepAfter;
    QString sourceCode;
    QList<Word*> words;
    int timeBefore, timeAfter, pitchMax, pitchMin;

};

#endif // SENTENCE_H
