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

void Word::setGold()
{
    Q_ASSERT_X(_type != Word::Separator, "setting a separator gold", "a separator has immutable type");
    _type = Word::Gold;
}
void Word::setFree()
{
    Q_ASSERT_X(_type != Word::Separator, "setting a separator free", "a separator has immutable type");
    _type = Word::Free;
}
void Word::setNormal()
{
    Q_ASSERT_X(_type != Word::Separator, "setting a separator normal", "a separator has immutable type");
    _type = Word::Normal;
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
