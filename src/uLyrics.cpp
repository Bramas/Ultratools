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
        in >> time2;
        if (in.status() == QTextStream::Ok)
        {
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
        parseLine(line);
    }
    sortAll();
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
    Word * w = 0;
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

    if(w && temp.compare("")) // !=""
    {
        w->setText(w->getText()+temp);
    }

    modified("moveRight");
    return ret;


}

QList<Word*> * Lyrics::separatorsOfWords(QList<Word *> * list) const
{
    Q_UNUSED(list);
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
QList<Word*> Lyrics::sentencesOfWord(Word *w) const
{
    Q_UNUSED(w);
    QList<Word*> sentence;

    QList<Word*>::const_iterator wordIt = this->words().constBegin() + this->words().indexOf(w);

    while(wordIt != this->words().constBegin() && !(*wordIt)->isSeparator())
        --wordIt;

    if(!(*wordIt)->isSeparator())
    {
        wordIt = this->words().constBegin();
    }
    if((*wordIt)->isSeparator())
    {
        ++wordIt;
    }

    while(wordIt != this->words().constEnd() && !(*wordIt)->isSeparator())
    {
        sentence << (*wordIt);
        ++wordIt;
    }

    return sentence;

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
        if((*it)->getTime() > ws->getTime() ||
	   ((*it)->getTime() == ws->getTime() && ws->isSeparator()))
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
