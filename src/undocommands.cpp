#include "undocommands.h"
#include "uLyrics.h"
#include "uWord.h"

#include <QDebug>


/** undo command are private part of Lyrics class */

//typedef QPair<bool, Word> QPair<bool, Word>

Lyrics::AddDeleteWord::AddDeleteWord(Lyrics * lyrics, const Word & word, bool add, QString text) :
    QUndoCommand(!text.isEmpty() ? text : (add ? tr("ajouter une note") : tr("supprimer une note"))),
    _lyrics(lyrics),
    _editGroup(_lyrics->_editGroup)
{
    _words << QPair<bool, Word>(add, word);
}

void Lyrics::AddDeleteWord::redo()
{
    foreach(const auto & p, _words)
    {
        if(p.first){ // if we want to add
            _lyrics->_words.insert(p.second.getTime(), p.second);
        }
        else {
            _lyrics->_words.remove(p.second.getTime(), p.second);
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
            _lyrics->_words.remove(p.second.getTime(), p.second);
        }
        else {
            _lyrics->_words.insert(p.second.getTime(), p.second);
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
    _editGroup(_lyrics->_editGroup)
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


