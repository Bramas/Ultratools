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


#include "uWydget_lyrics.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>
#include <QTextBlock>
#include "uInputManager.h"
#include <uShowSentenceWydget.h>
#include <QScrollBar>
#include <QMimeData>

#define MAX_HEIGHT 40
#define UTF8_WORDS_SEPARATOR 0x02D2
#define UTF8_SENTENCE_SEPARATOR 0x02FD //02C4

UWydget_Lyrics::UWydget_Lyrics() : QPlainTextEdit(0)
{
_selectedTextFirstIndex=-1; _selectedTextLastIndex=-1;
_wydgetWords = NULL;
 this->setMaximumWidth(200);
 this->setMinimumWidth(200);

_maxHeight      = MAX_HEIGHT;
_cursorPosition = 0;

_fontSize = 6;
_isEditing = false;

connect(&UInputManager::Instance, SIGNAL(keyPressEvent(QKeyEvent*)),this, SLOT(onKeyPress(QKeyEvent*)));
}

void UWydget_Lyrics::setWidgetWords(ShowSentenceWidget* wydgetWords)
{
    _wydgetWords = wydgetWords;
    connect(_wydgetWords->getLyrics(), SIGNAL(hasBeenModified()), this, SLOT(updateChange()));
    updateChange();
}

void UWydget_Lyrics::onKeyPress(QKeyEvent *e)
{

    if(e->key() == Qt::Key_Enter || e->key()+1 == Qt::Key_Enter)
        saveChange();
}

void UWydget_Lyrics::insertFromMimeData(const QMimeData *source)
{
    QString t = source->text();
    t.replace(' ',"\n");
    this->insertPlainText(t);
}

void UWydget_Lyrics::onTextChanged()
{
    if(!_wydgetWords)
    {
        return;
    }
    QTextBlock block = this->document()->firstBlock();
    QList<Word*>::iterator it = _wydgetWords->getLyrics()->words().begin();
    while(block.isValid())
    {
        if(it == _wydgetWords->getLyrics()->words().end())
        {
            break;
        }
        if(!(*it)->isSeparator())
        {
            (*it)->setText(block.text());
            block = block.next();
        }
        ++it;
    }
    if(block.isValid())
    {
        while(block.isValid())
        {
            if(block.blockNumber() == this->document()->blockCount() - 1)
            {
                break;
            }
            Word * w = new Word(_wydgetWords->getLyrics(), _wydgetWords->getLyrics()->words().last()->getTime2()+1, 2,_wydgetWords->getLyrics()->words().last()->getPitch());
            w->setText(block.text());
            _wydgetWords->getLyrics()->words().append(w);
            block = block.next();
        }
    }
    else
    {
        Word * last = (*it);
        while(it != _wydgetWords->getLyrics()->words().end())
        {
            if(!(*it)->isSeparator())
            {
                (*it)->setText("");
            }
            ++it;
        }
    }
    _wydgetWords->update();
}

void UWydget_Lyrics::saveChange()
{

    qDebug()<<"saveChange";

}

void UWydget_Lyrics::updateChange()
{
    if(!_wydgetWords)
    {
        return;
    }
    QString t;
    foreach(const Word * w, _wydgetWords->getLyrics()->words())
    {
        if(!w->isSeparator())
        {
            t += w->getText()+"\n";
        }
    }

    disconnect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    this->setPlainText(t);
    connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}


void UWydget_Lyrics::onScroll()
{
    if(!_wydgetWords || !_wydgetWords->getWordsDisplayedPtr()->count())
    {
        return;
    }
    int firstBlock = Word::indexOfWord( _wydgetWords->getLyrics()->words(), _wydgetWords->getWordsDisplayedPtr()->first());
    this->verticalScrollBar()->setValue(firstBlock);

}

void UWydget_Lyrics::ondoubleClick(int s)
{

}

void UWydget_Lyrics::separeOnSelect()
{

}

void UWydget_Lyrics::cursorPositionChanged(int old,int pos){

}
void UWydget_Lyrics::onSelectionChange(int s, int f)
{
    if(s==-1 || f < s)
    {
        this->setExtraSelections(QList<QTextEdit::ExtraSelection>());
        return;
    }
    QList<QTextEdit::ExtraSelection> l;
    for(int i = s; i <= f; ++i)
    {
        QTextEdit::ExtraSelection extra;
        extra.cursor = this->textCursor();
        extra.cursor.setPosition(this->document()->findBlockByNumber(i).position());
        extra.format.setBackground(QBrush(QColor(180,255,255)));
        extra.format.setProperty(QTextFormat::FullWidthSelection, true);
        l << extra;
    }
    this->setExtraSelections(l);
}
