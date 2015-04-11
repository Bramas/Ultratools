/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Quentin Bramas <quentin@bramas.fr> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Quentin Bramas
 *
 * "LICENCE BEERWARE" (Révision 42):
 * Quentin Bramas <quentin@bramas.fr> a créé ce fichier. Tant que vous conservez cet avertissement,
 * vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
 * que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
 * retour. Quentin Bramas
 * ----------------------------------------------------------------------------
 */


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

void Word::setOctaveOffset(int newOctave, bool definitly)
{
    if(definitly)
    {
        //_oPitch = newOctave;
    }
    _octaveOffset = newOctave;
}

void Word::setGold(bool newGold)
{
    if(_parent) _parent->modified("setGold()");
    _type = (Word::Type)(newGold ? _type | Word::Gold : _type & ~Word::Gold);
}
void Word::setFree(bool in)
{
    if(_parent) _parent->modified("setFree()");
    _type = (Word::Type)(in ? _type | Word::Free : _type & ~Word::Free);
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

QPair<int, int> Word::rangeTime(QList<Word *> *wlist)
{
    QPair<int, int> range(0,0);
    if(wlist->empty()) return range;


        range.first = wlist->first()->getTime();
        range.second = wlist->first()->getTime()+wlist->first()->getLength();

    foreach(Word *w , *wlist)
    {
        if(w->getTime()<range.first)
        {
            range.first = w->getTime();
        }
        if(w->getTime() + w->getLength()>range.second)
        {
            range.second = w->getTime() + w->getLength();
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

int Word::indexOfWord(const QList<Word*> & list, Word * word)
{
    int idx = 0;
    foreach(const Word * w, list)
    {
        if(w == word)
        {
            return idx;
        }
        if(w->isSeparator())
        {
            continue;
        }
        ++idx;
    }
    return -1;
}


int Word::minIndexOfWords(QList<Word *> theWords,QList<Word *> inThisWords)
{
    if(inThisWords.empty() || theWords.empty()) return -1;
    int min = indexOfWord(inThisWords,theWords.first());
    foreach(Word * w,theWords)
    {        
        int m = indexOfWord(inThisWords, w);
        if(min > m)
        {
            min = m;
        }
    }
    return min;
}
int Word::maxIndexOfWords(QList<Word *> theWords,QList<Word *> inThisWords)
{
    if(inThisWords.empty() || theWords.empty()) return -1;
    int max = indexOfWord(inThisWords,theWords.first());
    foreach(Word * w,theWords)
    {
        int m = indexOfWord(inThisWords, w);
        if(max < m)
        {
            max = m;
        }
    }
    return max;
}
