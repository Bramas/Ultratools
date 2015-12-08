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

UWydget_Lyrics::UWydget_Lyrics() : QPlainTextEdit(0), _updateTimer(0)
{
_selectedTextFirstIndex=-1; _selectedTextLastIndex=-1;
_wydgetWords = NULL;
 this->setMaximumWidth(200);
 this->setMinimumWidth(200);

_maxHeight      = MAX_HEIGHT;
_cursorPosition = 0;

_fontSize = 6;
_isEditing = false;

this->document()->setUndoRedoEnabled(false);

connect(&UInputManager::Instance, SIGNAL(keyPressEvent(QKeyEvent*, ulong)),this, SLOT(onKeyPress(QKeyEvent*)));
}

void UWydget_Lyrics::setWidgetWords(ShowSentenceWidget* wydgetWords)
{
    _wydgetWords = wydgetWords;
    connect(_wydgetWords->getLyrics(), SIGNAL(hasBeenModified()), this, SLOT(queueUpdate()));
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

void UWydget_Lyrics::keyPressEvent(QKeyEvent * e)
{
    if(e->matches(QKeySequence::Undo))// || e->matches(QKeySequence::Redo))
    {
        _wydgetWords->getLyrics()->undo();
        return;
    }
    if(e->matches(QKeySequence::Redo))
    {
        _wydgetWords->getLyrics()->redo();
        return;
    }
    QPlainTextEdit::keyPressEvent(e);
}

void UWydget_Lyrics::onTextChanged()
{
    if(!_wydgetWords || _wydgetWords->getLyrics()->words().isEmpty())
    {
        return;
    }
    QTextBlock block = this->document()->firstBlock();
    auto it = _wydgetWords->getLyrics()->wordBegin();
    while(block.isValid())
    {
        if(it == _wydgetWords->getLyrics()->wordEnd())
        {
            break;
        }
        if(!(*it).isSeparator())
        {
            it.setText(block.text());
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
            Word w(_wydgetWords->getLyrics(), _wydgetWords->getLyrics()->words().last().getTime2()+1, 2,_wydgetWords->getLyrics()->words().last().getPitch());
            w.setText(block.text());
            _wydgetWords->getLyrics()->addWord(w);
            block = block.next();
        }
    }
    else
    {
        while(it != _wydgetWords->getLyrics()->wordEnd())
        {
            if(!(*it).isSeparator())
            {
                it.setText("");
            }
            ++it;
        }
    }
    if (_updateTimer)
    {
        killTimer(_updateTimer);
	_updateTimer = 0;
    }
    _wydgetWords->update();
}

void UWydget_Lyrics::saveChange()
{

    qDebug()<<"saveChange";

}

void UWydget_Lyrics::queueUpdate()
{
    if(!_updateTimer)
    {
        _updateTimer = startTimer(0);
    }
}

void UWydget_Lyrics::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == _updateTimer)
    {
        killTimer(_updateTimer);
	_updateTimer = 0;
        updateChange();
    }
    else
    {
        QPlainTextEdit::timerEvent(event);
    }
}

void UWydget_Lyrics::updateChange()
{
    if(!_wydgetWords)
    {
        return;
    }
    QString t;
    foreach(const Word & w, _wydgetWords->getLyrics()->words())
    {
        if(!w.isSeparator())
        {
            t += w.getText()+"\n";
        }
    }

    disconnect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    this->setPlainText(t);
    connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}


void UWydget_Lyrics::onScroll()
{
    if(!_wydgetWords || !_wydgetWords->getWordsDisplayedPtr().count())
    {
        return;
    }
    int firstBlock = Word::indexOfWord( _wydgetWords->getLyrics()->words(), _wydgetWords->getWordsDisplayedPtr().first());
    this->verticalScrollBar()->setValue(firstBlock);

}

void UWydget_Lyrics::ondoubleClick(int /*s*/)
{

}

void UWydget_Lyrics::separeOnSelect()
{

}

void UWydget_Lyrics::cursorPositionChanged(int /*old*/,int /*pos*/){

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
