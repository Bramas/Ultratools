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


#ifndef WORD_H
#define WORD_H

#include "uSetting.h"

class Sentence;




class Word : public UAbstractLine
{
public:
    Word(Sentence * parent,int time,int length, int pitch, bool gold=false);

    int setTime(int newTime, bool definitly = true);
    int setLength(int newlength, bool definitly = true);
    int setPitch(int newPitch, bool definitly = true);
    bool setGold(bool newGold=true);
    void setWord(QString word);

    bool isGold(void) const;
    int getTime(void) const;
    int getLength(void) const;
    int getPitch(void) const;
    QString getWord(void) const;
    bool _selected;



    int getOTime() const { return _oTime; };
    int getOPitch() const { return _oPitch; };
    int getOLength() const { return _oLength; };

    void hold(void) { _oTime=time; _oPitch=pitch; _oLength=length; }

    void setOver(quint8 n) { _over = n; }
    quint8 getOver(void) const { return _over; }


    bool equal(const Word& t2) const
    {
        return (this->getLength()  ==t2.getLength()
                && this->getPitch()==t2.getPitch()
                && this->getTime() ==t2.getTime()
                && this->getWord() ==t2.getWord());
    }
    bool operator==(const Word& t2) const
    {
        return this->equal(t2);
    }
    bool operator!=(const Word& t2) const
    {
        return !this->equal(t2);
    }

    bool hasBeenModified(void) { return _oTime!=time || _oPitch!=pitch || _oLength!=length; }

    Sentence * getParent() { return _parent; };
    void setParent(Sentence * par);

    bool isFree(void) { return free; }
    void setFree(bool in);

    static bool wordLessThanPtr(const Word * a,const Word * b);

private:

    Sentence * _parent;

    quint8 _over;
    int _oTime;
    int _oPitch;
    int _oLength;

    bool gold;
    bool free;
    int time;
    int length;
    int pitch;
    QString word;



public:
    static int  ** rangeTime(QList<Word*> * wlist);
    static int minIndexOfWords(QList<Word*>,QList<Word*>);
    static int maxIndexOfWords(QList<Word*>,QList<Word*>);


};




#endif // WORD_H
