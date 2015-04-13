#include "wordselection.h"
#include "uLyrics.h"

#include <QDebug>

WordSelection::WordSelection() : _lyrics(0)
{
}

WordSelection::WordSelection(Lyrics *lyrics) : _lyrics(lyrics)
{
    _lyrics->_selections.append(this);
    qDebug()<<" create selection ";
}

WordSelection::~WordSelection()
{
    _lyrics->_selections.removeAll(this);
    qDebug()<<" remove selection ";
}

void WordSelection::add(const Word & word)
{
    Q_ASSERT_X(_lyrics->contains(word), "When adding a word to the selection", "_overed must be part of the lyrics");
    _selectedWords.insert(word, word.getTime());
}

void WordSelection::remove(const Word & word)
{
    _selectedWords.remove(word);
}
void WordSelection::setGold()
{

}
void WordSelection::setFree()
{

}
void WordSelection::setNormal()
{

}

void WordSelection::deleteSelectedWords()
{

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
void WordSelection::translate(int addTime, int addPitch)
{
    qDebug()<<"translate "<<addTime<<" "<<addPitch;
}
void WordSelection::expandRight(int add)
{
    qDebug()<<"expandRight "<<add;
}
void WordSelection::expandLeft(int add)
{
    qDebug()<<"expandLeft "<<add;
}
