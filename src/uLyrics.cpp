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



#include "uLyrics.h"
#include <QTranslator>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <cmath>

Lyrics::Lyrics(QWidget * parent)
{
    this->parent=parent;
    pitchMax=0;
    pitchMin=255;
    _recalcMinMax=false;
    _gap=0;
    _editGroup = 1;

}

void Lyrics::parseLine(QString &line)
{
    QTextStream in(&line);
    QChar typeChar = in.read(1).at(0);
    if(typeChar == '#' || typeChar == 'E')
    {
        return;
    }

    Word word;
    if(typeChar == '-') // it's a separator
    {
        int time1, time2 = 0;
        in >> time1;
        in >> time2;
        if (in.status() == QTextStream::Ok)
        {
            time2 -= time1;
        }
        word = Word(this,time1, time2, 0, Word::Separator);

    }else
    {
        int time, length, pitch;
        in >> time;
        in >> length;
        in >> pitch;
        in.read(1); // ignore the first space
        Word::Type type = (typeChar == '*' ?
                               Word::Gold :
                               (typeChar == 'F' ?
                                    Word::Free :
                                    Word::Normal));
        word = Word(this,time, length, pitch, type);
        QString text = in.readLine();
        word.setText(text);
    }
    reallyAddWord(word);
    this->setModified(false);
}

void Lyrics::parseCode(QString &code)
{
    QTextStream in(&code);
    QString line;
    while(!(line = in.readLine()).isNull())
    {
        parseLine(line);
    }
}

int Lyrics::getPitchMax()
{
    return pitchMax;
}
int Lyrics::getPitchMin()
{
    return pitchMin;
}



QList<Word> Lyrics::sentencesOfWord(const Word &w) const
{
    QList<Word> sentence;

    auto wordIt = this->words().find(w.getTime(), w);

    while(wordIt != this->words().constBegin() && !(*wordIt).isSeparator())
        --wordIt;

    if(!(*wordIt).isSeparator())
    {
        wordIt = this->words().constBegin();
    }
    if((*wordIt).isSeparator())
    {
        ++wordIt;
    }

    while(wordIt != this->words().constEnd() && !(*wordIt).isSeparator())
    {
        sentence << (*wordIt);
        ++wordIt;
    }

    return sentence;

}

Word Lyrics::addSeparator(int time)
{
    Word sep(this, time, 0, 0, Word::Separator);
    addWord(sep);
    return sep;
}

QMap<int, Word>::const_iterator Lyrics::find(const Word &w)
{
    return _words.find(w.getTime(), w);
}

void Lyrics::removeWord(const Word &w)
{
    _history.push(new Lyrics::AddDeleteWord(this, w, false));
    emit hasBeenModified();
}
void Lyrics::addWord(const Word &w, QString actionText)
{
    _history.push(new Lyrics::AddDeleteWord(this, w, true, actionText));
    emit hasBeenModified();
}

void Lyrics::emitModified()
{
    if (_recalcMinMax)
    {
        _recalcMinMax = false;
        if (!_words.isEmpty())
        {
            pitchMin = pitchMax = _words.first().getPitch();
            foreach (const Word &w, _words)
            {
                if (pitchMin > w.getPitch())
                    pitchMin = w.getPitch();
                if (pitchMin > w.getPitch())
                    pitchMin = w.getPitch();
            }
        }
    } 
    emit hasBeenModified();
}

void Lyrics::reallyRemoveWord(const Word &w)
{
    if (w.getPitch() == pitchMin || w.getPitch() == pitchMax)
        _recalcMinMax = true;
    _words.remove(w.getTime(), w);
}

void Lyrics::reallyAddWord(const Word &w)
{
    if(_words.isEmpty() || w.getPitch() < pitchMin)
        pitchMin = w.getPitch();
    if(_words.isEmpty() || w.getPitch() > pitchMax)
        pitchMax = w.getPitch();
    auto it = _words.insert(w.getTime(), w);
    it.value().setParent(this);
}

void Lyrics::doublePresicion()
{
    if(_bpm>800) {
        QMessageBox::warning(NULL,tr("impossible"),tr("le BPM est déjà bien assez grand"));
        return;
    }

    QMultiMap<int, Word> newWords;

    for(Word & w: _words)
    {
        w.setTime(w.getTime()*2);
        w.setLength(w.getLength()*2);
        newWords.insert(w.getTime(), w);
    }

    _words.swap(newWords);

    emit hasBeenModified(); //FIXME (use undocommand)
}


Word & Lyrics::wordRef(const Word &w)
{
    return _words.find(w.getTime(), w).value();
}

Lyrics::WordIterator Lyrics::wordBegin()
{
    return Lyrics::WordIterator(this, _words.begin());
}

Lyrics::WordIterator Lyrics::wordEnd()
{
    return Lyrics::WordIterator(this, _words.end());
}
int Lyrics::setDelay(int delay, int from)
{
    if(from > _gap)
        from = ceil((((from-floor(this->getGap()))/1000.0) * this->getBpm()/15.0));
    else
        from = 0;


    // check only if the delay is negative
    if(delay < 0)
    {
        auto wordIt = _words.constBegin();
        while(wordIt != _words.constEnd())
        {
            if( from <= (*wordIt).getTime())
            {
                //check if we go before the gap
                if( (*wordIt).getTime() + delay < 0)
                {
                    delay = -(*wordIt).getTime();
                }

                //check if we go before the previous word
                if(wordIt != _words.constBegin() && (*wordIt).getTime() + delay < (*(wordIt - 1)).getTime() + (*(wordIt - 1)).getLength())
                {
                    delay = -(*wordIt).getTime() + (*(wordIt - 1)).getTime() + (*(wordIt - 1)).getLength();
                }

                //check if the cursor go before the previous word
                if(wordIt != _words.constBegin() && from + delay <= (*(wordIt - 1)).getTime())
                {
                    delay = 1 - from + (*(wordIt - 1)).getTime();
                }
                break;
            }
            ++wordIt;
        }
    }
    if(delay != 0)
    {
        _history.push(new Lyrics::SetDelay(this, delay, (int)from));
        emit hasBeenModified();
    }

    return delay;
}

void Lyrics::WordIterator::setText(QString text)
{
    if(_it.value().getText() == text)
    {
        return;
    }
    _lyrics->_history.push(new Lyrics::ChangeText(_lyrics, _it.value(), text));
    //_it.value().setText(text);
}
