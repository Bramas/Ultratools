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

#include <QSet>
#include "uWord.h"
#include "uLyrics.h"

Word::Word(Lyrics * parent, int time, int length, int pitch, Word::Type type)
{
    _parent = parent;
    _oTime = _time=time;
    _length=_oLength=length;
    _oPitch = _pitch=pitch;
    _octaveOffset = 0;
    _selected = false;
    if(_parent)
    {
        _parent->modified("in the constructor");
    }
    _type = type;
}

void Word::setText(QString text)
{
    if(_parent)
    {
        _parent->modified("in the setWord");
    }
    _text=text;
}

int Word::setTime(int newTime, bool definitly)
{
    if(_parent)
    {
        _parent->modified("in the setTime");
    }

    if(definitly)
    {
        _oTime = newTime;
    }
    return _time = newTime;
}
int Word::setLength(int newLength, bool definitly)
{
    if(_parent)
    {
        _parent->modified("in the setLength");
    }
    if(definitly)
    {
        _oLength = newLength;
    }
     return _length = newLength;
}
int Word::setPitch(int newPitch, bool definitly)
{
    if(_parent)
    {
        _parent->modified("in the setPitch");
    }
    if(definitly)
    {
        _oPitch = newPitch;
    }
     return _pitch = newPitch;
}

void Word::setOctaveOffset(int newOctave, bool definitly)
{
    if(definitly)
    {
        //_oPitch = newOctave;
    }
    _octaveOffset = newOctave;
}

void Word::setType(Word::Type type)
{
    Q_ASSERT_X(_type != Word::Separator, "setting a separator a new type", "a separator has immutable type");
    _type = type;
}

void Word::hold(void) {
    if(_parent)
    {
        _parent->modified("hold()");
    }
    _oTime=_time; _oPitch=_pitch; _oLength=_length;
}
int Word::getLength(void) const
{
    return _length;
}
int Word::getPitch(void) const
{
    return _pitch;
}
int Word::getOctaveOffset(void) const
{
    return _octaveOffset;
}

void Word::setParent(Lyrics *par)
{
    _parent = par;
}

QPair<int, int> Word::rangeTime(const QSet<Word> & wlist)
{
    QPair<int, int> range(0,0);
    if(wlist.empty()) return range;


        range.first = (*(wlist.constBegin())).getTime();
        range.second = (*(wlist.constBegin())).getTime()+(*(wlist.constBegin())).getLength();

    foreach(const Word &w , wlist)
    {
        if(w.getTime()<range.first)
        {
            range.first = w.getTime();
        }
        if(w.getTime() + w.getLength()>range.second)
        {
            range.second = w.getTime() + w.getLength();
        }
    }
    return range;
}

bool Word::wordLessThanPtr(const Word *a, const Word *b)
{
    if (a->getTime() == b->getTime())
        return (a->isSeparator() && !b->isSeparator());
    return a->getTime()<b->getTime();
}

int Word::indexOfWord(const QMap<int, Word> &list, const Word & word)
{
    int idx = 0;
    foreach(const Word & w, list)
    {
        if(w == word)
        {
            return idx;
        }
        if(w.isSeparator())
        {
            continue;
        }
        ++idx;
    }
    return -1;
}


int Word::minIndexOfWords(const QSet<Word> & theWords, const QMap<int, Word> &inThisWords)
{
    if(inThisWords.empty() || theWords.empty()) return -1;
    int min = indexOfWord(inThisWords, *(theWords.constBegin()));
    foreach(const Word & w, theWords)
    {        
        int m = indexOfWord(inThisWords, w);
        if(min > m)
        {
            min = m;
        }
    }
    return min;
}
int Word::maxIndexOfWords(const QSet<Word> &theWords, const QMap<int, Word> &inThisWords)
{
    if(inThisWords.empty() || theWords.empty()) return -1;
    int max = indexOfWord(inThisWords, *(theWords.constBegin()));
    foreach(const Word & w, theWords)
    {
        int m = indexOfWord(inThisWords, w);
        if(max < m)
        {
            max = m;
        }
    }
    return max;
}
