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

#ifndef WORD_H
#define WORD_H

#include "uSetting.h"


class Lyrics;

class Word
{
public:
    typedef enum Type { Default = 7, Normal = 1, Free = 2, Gold = 4, Separator = 8 } Type;

    Word() : _parent(0) { }
    bool isNull() const { return !_parent; }

    Word(Lyrics * parent, int time, int length, int pitch, Word::Type type = Word::Normal);


    int setTime(int newTime, bool definitly = true);
    int getTime(void) const  { return getTime1(); }
    int getTime1(void) const { return _time; }
    int getTime2(void) const { return _time + _length; }

    int setLength(int newlength, bool definitly = true);
    int getLength(void) const;
    int setPitch(int newPitch, bool definitly = true);
    int getPitch(void) const;

    void setOctaveOffset(int newOctave, bool definitly = true);
    int getOctaveOffset(void) const;

    void setType(Word::Type type);
    bool isGold(void) const { return _type & Word::Gold; }
    bool isFree(void) const { return _type & Word::Free; }
    bool isNormal(void) const { return _type == Word::Normal; }

    Word::Type getType(void) const { return _type; }
    bool isSeparator() const { return _type & Word::Separator; }
    Lyrics * getParent() { return _parent; }
    void setParent(Lyrics * par);

    void setText(QString text);
    QString getText(void) const { return _text; }
    void setSelected(bool selected = true) { _selected = selected; }
    bool isSelected(void) const { return _selected; }

    bool hasBeenModified(void) const { return _oTime!=_time || _oPitch!=_pitch || _oLength!=_length; }



    int getOTime() const { return _oTime; }
    int getOPitch() const { return _oPitch; }
    int getOLength() const { return _oLength; }

    void hold(void);


    bool equal(const Word& t2) const
    {
        return (this->getLength()  ==t2.getLength()
                && this->getPitch()==t2.getPitch()
                && this->getTime() ==t2.getTime()
                && this->getText() ==t2.getText()
                && this->getType() ==t2.getType());
    }
    bool operator==(const Word& t2) const
    {
        return this->equal(t2);
    }
    bool operator!=(const Word& t2) const
    {
        return !this->equal(t2);
    }
    bool operator<(const Word& t2) const
    {

        if (this->getTime() != t2.getTime())
            return this->getTime() < t2.getTime();

        if (this->getLength() != t2.getLength())
            return this->getLength() < t2.getLength();

        if (this->isSeparator() != t2.isSeparator())
            return (this->isSeparator() && !t2.isSeparator()); //separator come before

        if (this->isSeparator())// at this point, if they  are both separators, they are equals
        {
            return false;
        }

        if (this->getPitch() != t2.getPitch())
            return this->getPitch() < t2.getPitch();

        if (this->getText() != t2.getText())
            return this->getText() < t2.getText();

        // else, they are equal
        return false;

    }
    bool operator<=(const Word& t2) const
    {
        return *this < t2 || this->equal(t2);
    }
    bool operator>(const Word& t2) const
    {
        return t2 < *this;
    }
    bool operator>=(const Word& t2) const
    {
        return *this > t2 || this->equal(t2);
    }


    static bool wordLessThanPtr(const Word * a,const Word * b);

private:

    bool _selected;
    Lyrics * _parent;

    int _oTime;
    int _oPitch;
    int _oLength;

    Word::Type _type;
    int _time;
    int _length;
    int _pitch;
    int _octaveOffset;
    QString _text;






public:
    static QPair<int,int> rangeTime(const QSet<Word> &wlist);
    static int minIndexOfWords(const QSet<Word> &, const QMap<int, Word> &);
    static int maxIndexOfWords(const QSet<Word> &, const QMap<int, Word> &);
    static int indexOfWord(const QMap<int, Word> &list, const Word &word);


};


inline uint qHash(const Word &key, uint seed)
{
    Q_ASSERT(!key.isNull());
    return (qHash(key.getTime(), seed) ^ 13) + (qHash(key.getLength(), seed) ^ 27) + qHash(key.getText(), seed);
}


#endif // WORD_H
