#include "wordselection.h"
#include "uLyrics.h"

#include <QDebug>

WordSelection::WordSelection() : _lyrics(0)
{
}

WordSelection::WordSelection(Lyrics *lyrics) : _lyrics(lyrics)
{
    _lyrics->_selections.append(this);
}

WordSelection::~WordSelection()
{
    _lyrics->_selections.removeAll(this);
}

void WordSelection::add(const Word & word)
{
    Q_ASSERT_X(_lyrics->contains(word), "When adding a word to the selection",
               QString("word \""+word.getText()+
                        "\" "+QString::number(word.getTime())+" must be part of the lyrics").toLatin1().data());
    _selectedWords.insert(word, word.getTime());
}

void WordSelection::remove(const Word & word)
{
    _selectedWords.remove(word);
}


void WordSelection::insertAndSelect(const Word &w)
{

}

// not optimized function but so much clearer for the next functions
QMap<Word, int> WordSelection::takeSelectedWords()
{
    QMap<Word, int> oldWords = _selectedWords;
    _selectedWords.clear();
    return oldWords;
}


void WordSelection::setType(Word::Type type)
{
    foreach(const Word &w, takeSelectedWords().keys())
    {
        if(!w.isSeparator())
        {
            _lyrics->_history.push(new Lyrics::SetWordType(_lyrics, w, type));
            Word nw = w;
            nw.setType(type);
            _selectedWords.insert(nw, nw.getTime());
        }
    }
}

void WordSelection::deleteSelectedWords()
{
    foreach(const Word &w, takeSelectedWords().keys())
    {
        _lyrics->removeWord(w);
    }
}


void WordSelection::merge()
{
    if(_selectedWords.count()<2)
    {
        return;
    }
    Word newW(NULL,0,0,0);


int fTime = this->first().getTime()
        , lTime = this->first().getTime() + this->first().getLength()
        ,fPitch = this->first().getPitch();

    foreach(const Word &w, _selectedWords.keys())
    {
        newW.setText(newW.getText()+w.getText());
        if(w.getTime() < fTime)
        {
            fTime = w.getTime();
            fPitch = w.getPitch();
        }
        if(w.getTime() + w.getLength() > lTime)
        {
            lTime = w.getTime() + w.getLength();
        }
        _lyrics->removeWord(w);

    }
    newW.setTime(fTime);
    newW.setLength(lTime - fTime);
    newW.setPitch(fPitch);
    _lyrics->addWord(newW);

    _selectedWords.clear();

}
QPoint WordSelection::translate(int addTime, int addPitch)
{
    if(_selectedWords.size() == 0)
    {
        return QPoint(0,0);
    }
    addTime = std::max(addTime, -_selectedWords.firstKey().getTime());
    foreach(const Word & w, takeSelectedWords().keys())
    {
        _lyrics->removeWord(w);
        Word newWord = w;
        newWord.setPitch(w.getPitch() + addPitch);
        newWord.setTime(w.getTime() + addTime);
        _lyrics->addWord(newWord, QObject::tr("le déplacement de la selection"));
        _selectedWords.insert(newWord, newWord.getTime());
    }
    return QPoint(addTime, addPitch);
}
int WordSelection::expandRight(int add)
{
    if(_selectedWords.size() != 1)
    {
        return 0;
    }
    Word w = _selectedWords.firstKey();
    int minLength = (w.isSeparator() ? 0 : 1);
    add = std::max(add, minLength - w.getLength());
    if(add == 0)
    {
        return 0;
    }
    _lyrics->removeWord(w);
    w.setLength(w.getLength() + add);
    _selectedWords.clear();
    _lyrics->addWord(w);
    _selectedWords.insert(w, w.getTime());
    return add;
}
int WordSelection::expandLeft(int add)
{
    if(_selectedWords.size() != 1)
    {
        return 0;
    }
    Word w = _selectedWords.firstKey();
    int minLength = (w.isSeparator() ? 0 : 1);
    add = std::max(add, minLength - w.getLength());
    add = std::min(add, w.getTime());
    if(add == 0)
    {
        return 0;
    }
    _lyrics->removeWord(w);
    w.setTime(w.getTime() - add);
    w.setLength(w.getLength() + add);
    _selectedWords.clear();
    _lyrics->addWord(w);
    _selectedWords.insert(w, w.getTime());
    return add;
}
