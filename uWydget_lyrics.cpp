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

connect(&UInputManager::Instance, SIGNAL(keyPressEvent(QKeyEvent*)),this, SLOT(onKeyPress(QKeyEvent*)));
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
        while(it != _wydgetWords->getLyrics()->words().end())
        {
            if(!(*it)->isSeparator())
            {
                (*it)->setText("");
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
