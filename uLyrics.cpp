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

    //sentences.push_back();

     /*     Phonon::MediaObject *music;// =  Phonon::createPlayer(Phonon::MusicCategory,Phonon::MediaSource("songs/arkol - vingt ans/01-anthem park two.mp3"));
    //music->play();

*/
  //   Phonon::MediaObject *mediaObject = new Phonon::MediaObject(parent);
   /*  mediaObject->setCurrentSource(Phonon::MediaSource("songs/arkol - vingt ans/01-anthem park two.mp3"));
     Phonon::AudioOutput *audioOutput =
         new Phonon::AudioOutput(Phonon::MusicCategory, this);
     Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);*/

}

void Lyrics::parseLine(QString &line)
{
    QTextStream in(&line);
    QChar typeChar = in.read(1).at(0);
    if(typeChar == '#' || typeChar == 'E')
    {
        return;
    }

    Word * word = 0;
    if(typeChar == '-') // it's a separator
    {
        int time1, time2 = 0;
        in >> time1;
        if(!in.atEnd())
        {
            in >> time2;
            time2 -= time1;
        }
        //qDebug()<<line<<" sep : "<<time1<<" "<<time2;
        word = new Word(this,time1, time2, 0, Word::Separator);

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
        word = new Word(this,time, length, pitch, type);
        //qDebug()<<line<<" word : "<<time<<length<<pitch<<type;
        QString text = in.readLine();
        word->setText(text);
    }
    _words.push_back(word);
    if(_words.back()->getPitch() < pitchMin) pitchMin=_words.back()->getPitch();
    if(_words.back()->getPitch() > pitchMax) pitchMax=_words.back()->getPitch();
    this->setModified(false);
}

void Lyrics::parseCode(QString &code)
{
    QTextStream in(&code);
    QString line;
    while(!(line = in.readLine()).isNull())
    {
        line = line.trimmed();
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

void Lyrics::moveLeft(Word *from)
{

    bool trouve = false;
    Word * w;
    Word * wBefore=NULL;

    foreach(w,_words)
    {
        if(w->isSeparator()) continue;
        if(trouve)
        {
            wBefore->setText(w->getText());
            w->setText("");
        }

        if(!trouve && wBefore && wBefore->equal(*from))
        {
            wBefore->setText(wBefore->getText()+w->getText());
            trouve=true;
        }

        wBefore=w;
    }
    modified("moveLeft");


}


Word * Lyrics::moveRight(Word *from, int indexIWant)
{


    Word * ret = from;
    bool trouve = false;
    Word * w;
    Word * wBefore=NULL;

    QString temp="", temp2="";

    int i=0;

    qDebug()<<"Move Left : "<<_words.count();
    foreach(w,_words)
    {
        if(w->isSeparator()) continue;
        if(trouve)
        {
            temp2=w->getText();
            w->setText(temp);

            temp = temp2;

            if(++i == indexIWant)
            {
                ret = w;
            }
            //qDebug()<<"- "<<wBefore->getText();
        }

        if(!trouve && wBefore && wBefore->equal(*from))
        {
            temp = w->getText();
            w->setText(wBefore->getText());

            trouve=true;
            //qDebug()<<"FIRST : "<<wBefore->getText();

            if(indexIWant == 1)
            {
                ret = w;
            }
            ++i;
        }

        wBefore=w;
    }

    if(temp.compare("")) // !=""
    {
        w->setText(w->getText()+temp);
    }

    modified("moveRight");
    return ret;


}

QList<Word*> * Lyrics::separatorsOfWords(QList<Word *> * list) const
{
    QList<Word*> * sep= new QList<Word*>();
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
QList<Word*> * Lyrics::sentencesOfWords(QList<Word *> * list) const
{
    QList<Word*> * sen= new QList<Word*>();

    return sen;
    /** FIXME */
    /*
    Word* w;
    foreach(w,*list)
    {
        if(!sen->contains(w->getParent()))
        {
            sen->push_back(w->getParent());
        }

    }


    return sen;
*/

}
void Lyrics::resortWord(Word *wdr)
{
    if(_words.count()<2) { return; }

    _words.removeOne(wdr);
    addWord(wdr);
}


Word *  Lyrics::addSeparator(int time)
{
    Word * sep = new Word(this, time, 0, 0, Word::Separator);
    addWord(sep);
    return sep;
}

void Lyrics::removeWord(Word *w)
{
    _words.removeOne(w);
    modified("removeWord");
}
void Lyrics::addWord(Word *ws)
{
    QList<Word*>::iterator it = _words.begin();

    while(it != _words.end())
    {
        if((*it)->getTime() > ws->getTime())
        {
            if((*it)->isSeparator() && ws->isSeparator())
            {
                return;
            }
            if(it != _words.begin() && (*(it - 1))->isSeparator() && ws->isSeparator())
            {
                return;
            }
            break;
        }
        ++it;
    }
    _words.insert(it, ws);
    modified("addWord");
}

void Lyrics::sortAll()
{
    if(_words.empty()) return;

    qSort(_words.begin(),_words.end(),Word::wordLessThanPtr);
    modified("sortAll");
}

void Lyrics::doublePresicion()
{
    if(_bpm>800) {
        QMessageBox::warning(NULL,tr("impossible"),tr("le BPM est déjà bien assez grand"));
        return;
    }

    foreach(Word *w,_words)
    {
        w->setTime(w->getTime()*2);
        w->setLength(w->getLength()*2);
    }

    modified("doublePresicion");
}


bool Lyrics::setDelay(int delay, quint64 from)
{
    double temp = 0;
    if(from > 0)
        temp = (((from-qFloor(this->getGap()))/1000.0) * this->getBpm()/15.0f);


    Word * last=NULL;
    // check only if the delay is negative
    bool firstWordChecked=(delay>=0);
    foreach(Word * w, words())
    {
        if( temp  <= w->getTime() && !firstWordChecked)
        {
            if(w->getTime() + delay < 0 ||
               (last && w->getTime() + delay < last->getTime() + last->getLength()))
            {
                return false;
            }
            else
            {
                firstWordChecked=true;
            }
            w->setTime(w->getTime()+delay);
        }
        else if( temp  <= w->getTime() )
        {
            w->setTime(w->getTime()+delay);
        }
        else
        {
            last=w;
        }
    }
    return true;
}
