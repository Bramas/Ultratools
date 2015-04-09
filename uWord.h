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


class Lyrics;

class Word
{
public:
    typedef enum Type { Default = 7, Normal = 1, Free = 2, Gold = 4, Separator = 8 } Type;

    Word(Lyrics * parent,int time,int length, int pitch, Word::Type type = Word::Normal);


    int setTime(int newTime, bool definitly = true);
    int getTime(void) const  { return getTime1(); }
    int getTime1(void) const { return _time; }
    int getTime2(void) const { return _time + _length; }

    int setLength(int newlength, bool definitly = true);
    int getLength(void) const;
    int setPitch(int newPitch, bool definitly = true);
    int getPitch(void) const;

    void setGold(bool newGold=true) { _type = newGold ? Word::Gold : Word::Normal; }
    bool isGold(void) const { return _type & Word::Gold; }
    bool isFree(void) const { return _type & Word::Free; }
    void setFree(bool in) { _type = in ? Word::Free : Word::Normal; }
    bool isSeparator() const { return _type & Word::Separator; }
    Lyrics * getParent() { return _parent; }
    void setParent(Lyrics * par);

    void setText(QString text);
    QString getText(void) const { return _text; }
    void setSelected(bool selected = true) { _selected = selected; }
    bool isSelected(void) const { return _selected; }

    bool hasBeenModified(void) { return _oTime!=_time || _oPitch!=_pitch || _oLength!=_length; }



    int getOTime() const { return _oTime; }
    int getOPitch() const { return _oPitch; }
    int getOLength() const { return _oLength; }

    void hold(void) { _oTime=_time; _oPitch=_pitch; _oLength=_length; }

    void setOver(quint8 n) { _over = n; }
    quint8 getOver(void) const { return _over; }


    bool equal(const Word& t2) const
    {
        return (this->getLength()  ==t2.getLength()
                && this->getPitch()==t2.getPitch()
                && this->getTime() ==t2.getTime()
                && this->getText() ==t2.getText());
    }
    bool operator==(const Word& t2) const
    {
        return this->equal(t2);
    }
    bool operator!=(const Word& t2) const
    {
        return !this->equal(t2);
    }


    static bool wordLessThanPtr(const Word * a,const Word * b);

private:

    bool _selected;
    Lyrics * _parent;

    quint8 _over;
    int _oTime;
    int _oPitch;
    int _oLength;

    Word::Type _type;
    int _time;
    int _length;
    int _pitch;
    QString _text;




public:
    static int  ** rangeTime(QList<Word*> * wlist);
    static int minIndexOfWords(QList<Word*>,QList<Word*>);
    static int maxIndexOfWords(QList<Word*>,QList<Word*>);
    static int indexOfWord(const QList<Word*> & list, Word * word);


};




#endif // WORD_H
