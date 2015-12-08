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

#include "undocommands.h"
#include "uLyrics.h"
#include "uWord.h"

#include <QDebug>


/** undo command are private part of Lyrics class */

//typedef QPair<bool, Word> QPair<bool, Word>

Lyrics::AddDeleteWord::AddDeleteWord(Lyrics * lyrics, const Word & word, bool add, QString text) :
    QUndoCommand(!text.isEmpty() ? text : (add ? tr("ajouter une note") : tr("supprimer une note"))),
    _lyrics(lyrics),
    _editGroup(lyrics->_editGroup)
{
    _words << QPair<bool, Word>(add, word);
}

void Lyrics::AddDeleteWord::redo()
{
    foreach(const auto & p, _words)
    {
        if(p.first){ // if we want to add
            _lyrics->reallyAddWord(p.second);
        }
        else {
            _lyrics->reallyRemoveWord(p.second);
        }
    }
    _lyrics->emitModified();
}

void Lyrics::AddDeleteWord::undo()
{
    for(int i = _words.size() - 1; i >= 0; --i) // we have to undo in a backward manner
    {
        auto p = _words.at(i);
        if(p.first){ // if we want to undo add
            _lyrics->reallyRemoveWord(p.second);
        }
        else {
            _lyrics->reallyAddWord(p.second);
        }
    }
    _lyrics->emitModified();
}

bool Lyrics::AddDeleteWord::mergeWith(const QUndoCommand * other)
{
    if(other->id() != this->id())
        return false;

    const AddDeleteWord* otherC = static_cast<const AddDeleteWord*>(other);
    if(otherC->editGroup() != this->editGroup())
        return false;

    this->setText(other->text());
    _words << otherC->_words.last();
    return true;
}



Lyrics::SetWordType::SetWordType(Lyrics * lyrics, const Word & word, Word::Type type) :
    QUndoCommand(tr("le changement de type")),
    _lyrics(lyrics),
    _editGroup(lyrics->_editGroup)
{
    WordType wt;
    wt.word = word;
    wt.newType = type;
    wt.oldType = word.getType();
    _words << wt;
}
void Lyrics::SetWordType::redo()
{
    for(SetWordType::WordType& wt: _words)
    {
        _lyrics->wordRef(wt.word).setType(wt.newType);
        wt.word.setType(wt.newType);
    }
    _lyrics->emitModified();
}

void Lyrics::SetWordType::undo()
{
    for(int i = _words.size() - 1; i >= 0; --i) // we have to undo in a backward manner
    {
        _lyrics->wordRef(_words.at(i).word).setType(_words.at(i).oldType);
        _words[i].word.setType(_words.at(i).oldType);
    }
    _lyrics->emitModified();
}

bool Lyrics::SetWordType::mergeWith(const QUndoCommand * other)
{
    if(other->id() != this->id())
        return false;

    const SetWordType* otherC = static_cast<const SetWordType*>(other);
    if(otherC->editGroup() != this->editGroup())
        return false;

    this->setText(other->text());
    _words << otherC->_words.last();
    return true;
}


Lyrics::SetDelay::SetDelay(Lyrics *lyrics, int delay, int from) :
    _delay(delay),
    _from(from),
    _editGroup(lyrics->_editGroup),
    _lyrics(lyrics)
{

}

void Lyrics::SetDelay::redo()
{
    auto wordIt = _lyrics->_words.begin();
    QList<Word> toBeInserted;
    while(wordIt != _lyrics->_words.end())
    {
        if(_from <= (*wordIt).getTime())
        {
            Word w = (*wordIt);
            wordIt = _lyrics->_words.erase(wordIt);
            w.setTime(w.getTime()+_delay);
            toBeInserted << w;
        }
        else
        {
            ++wordIt;
        }
    }
    foreach(const Word & w, toBeInserted)
    {
        wordIt = _lyrics->_words.insert(wordIt, w.getTime(), w);
    }
    _lyrics->emitModified();
}
void Lyrics::SetDelay::undo()
{
    auto wordIt = _lyrics->_words.begin();
    QList<Word> toBeInserted;
    while(wordIt != _lyrics->_words.end())
    {
        if(_from+_delay <= (*wordIt).getTime())
        {
            Word w = (*wordIt);
            wordIt = _lyrics->_words.erase(wordIt);
            w.setTime(w.getTime()-_delay);
            toBeInserted << w;
        }
        else
        {
            ++wordIt;
        }
    }
    foreach(const Word & w, toBeInserted)
    {
        wordIt = _lyrics->_words.insert(wordIt, w.getTime(), w);
    }
    _lyrics->emitModified();
}

bool Lyrics::SetDelay::mergeWith(const QUndoCommand *other)
{
    if(other->id() != this->id())
        return false;

    const SetDelay* otherC = static_cast<const SetDelay*>(other);
    if(otherC->editGroup() != this->editGroup())
        return false;

    if(otherC->_from != _from + _delay)
    {
        return false;
    }

    _delay += otherC->_delay;
    return true;
}







Lyrics::ChangeText::ChangeText(Lyrics * lyrics, const Word & word, const QString &text) :
    QUndoCommand(tr("la modificatin du texte")),
    _lyrics(lyrics),
    _editGroup(lyrics->_editGroup)
{
    WordText wt;
    wt.word = word;
    wt.newText = text;
    wt.oldText = word.getText();
    _words << wt;
}
void Lyrics::ChangeText::redo()
{
    for(ChangeText::WordText & wt: _words)
    {
        _lyrics->wordRef(wt.word).setText(wt.newText);
        wt.word.setText(wt.newText);
    }
    _lyrics->emitModified();
}

void Lyrics::ChangeText::undo()
{
    for(int i = _words.size() - 1; i >= 0; --i) // we have to undo in a backward manner
    {
        _lyrics->wordRef(_words.at(i).word).setText(_words.at(i).oldText);
        _words[i].word.setText(_words.at(i).oldText);
    }
    _lyrics->emitModified();
}

bool Lyrics::ChangeText::mergeWith(const QUndoCommand * other)
{
    if(other->id() != this->id())
        return false;

    const ChangeText* otherC = static_cast<const ChangeText*>(other);
    if(otherC->editGroup() != this->editGroup())
        return false;

    this->setText(other->text());
    _words << otherC->_words.last();
    return true;
}
