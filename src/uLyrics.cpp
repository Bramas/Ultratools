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



#include "uLyrics.h"
#include <QTranslator>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QtMath>

Lyrics::Lyrics(QWidget * parent)
{
    this->parent=parent;
    pitchMax=0;
    pitchMin=255;
    _gap=0;

    _modified=false;
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
    this->addWord(word);
    if(word.getPitch() < pitchMin) pitchMin=word.getPitch();
    if(word.getPitch() > pitchMax) pitchMax=word.getPitch();
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



QList<Word> Lyrics::separatorsOfWords(const QList<Word> &list) const
{
    Q_UNUSED(list);
    QList<Word> sep;
    return sep;
    /** FIXME */
    /*Word* w;
    foreach(w,*list)
    {
        if(!sep->contains(w->getParent()->getSepAfter()))
        {
            sep->push_back(w->getParent()->getSepAfter());
        }
        if(!sep->contains(w->getParent()->getSepBefore()))
        {
            sep->push_back(w->getParent()->getSepBefore());
        }
    }*/



    return sep;

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
    _words.remove(w.getTime(), w);
    modified("removeWord");
}
void Lyrics::addWord(const Word &w)
{
    _words.insert(w.getTime(), w);
    modified("addWord");
}


void Lyrics::doublePresicion()
{
    if(_bpm>800) {
        QMessageBox::warning(NULL,tr("impossible"),tr("le BPM est déjà bien assez grand"));
        return;
    }

    for(Word & w: _words)
    {
        w.setTime(w.getTime()*2);
        w.setLength(w.getLength()*2);
    }

    modified("doublePresicion");
}


Word & Lyrics::wordRef(const Word &w)
{
    return _words.find(w.getTime(), w).value();
}

bool Lyrics::setDelay(int delay, quint64 from)
{
    double temp = 0;
    if(from > 0)
        temp = (((from-qFloor(this->getGap()))/1000.0) * this->getBpm()/15.0f);


    Word last;
    // check only if the delay is negative
    bool firstWordChecked=(delay>=0);
    for(Word & w: words())
    {
        if( temp  <= w.getTime() && !firstWordChecked)
        {
            if( w.getTime() + delay < 0 ||
               (!last.isNull() && w.getTime() + delay < last.getTime() + last.getLength()))
            {
                return false;
            }
            else
            {
                firstWordChecked=true;
            }
            w.setTime( w.getTime()+delay);
        }
        else if( temp  <= w.getTime() )
        {
            w.setTime(w.getTime()+delay);
        }
        else
        {
            last=w;
        }
    }
    return true;
}
