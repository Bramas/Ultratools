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


#include "uWord.h"
#include "uLyrics.h"

Word::Word(Lyrics * parent, int time, int length, int pitch, Word::Type type)
{
    _parent = parent;
    _oTime = _time=time;
    _length=_oLength=length;
    _oPitch = _pitch=pitch;
    _selected = false;
    _over = 0;
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

int Word::getLength(void) const
{
    return _length;
}
int Word::getPitch(void) const
{
    return _pitch;
}

void Word::setParent(Lyrics *par)
{
    _parent = par;

    if(_parent)
    {
        _parent->modified("in the setParent");
    }
}

int ** Word::rangeTime(QList<Word *> *wlist)
{
    if(wlist->empty()) return NULL;

    int * range[2];

        range[0] = new int;
        range[1] = new int;

        *range[0] = wlist->first()->getTime();
        *range[1] = wlist->first()->getTime()+wlist->first()->getLength();

    foreach(Word *w , *wlist)
    {
        if(w->getTime()<*range[0])
        {
            *range[0] = w->getTime();
        }
        if(w->getTime() + w->getLength()>*range[1])
        {
            *range[1] = w->getTime() + w->getLength();
        }
    }
    return range;
}

bool Word::wordLessThanPtr(const Word *a, const Word *b)
{
    return a->getTime()<b->getTime();
}

int Word::minIndexOfWords(QList<Word *> theWords,QList<Word *> inThisWords)
{
    if(inThisWords.empty() || theWords.empty()) return -1;
    int min = inThisWords.indexOf(theWords.first());
    foreach(Word * w,theWords)
    {        
        if(min > inThisWords.indexOf(w))
        {
            min = inThisWords.indexOf(w);
        }
    }
    return min;
}
int Word::maxIndexOfWords(QList<Word *> theWords,QList<Word *> inThisWords)
{
    if(inThisWords.empty() || theWords.empty()) return -1;
    int max = inThisWords.indexOf(theWords.first());
    foreach(Word * w,theWords)
    {
        if(max < inThisWords.indexOf(w))
        {
            max = inThisWords.indexOf(w);
        }
    }
    return max;
}
