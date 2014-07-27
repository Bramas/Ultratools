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

 QList<Sentence*> * Lyrics::getSentences(void)
{
    return &sentences;
}
int * Lyrics::parseCode(QString code)
{

    int * maxH = new int;

    QChar c='\n';


    while(code[0]=='#')
    {

        code.remove(0,code.indexOf('\n')+1);

    }


int le=0;
int before=0, after=0;


int sepTime1=0, sepTime2=0;
USeparateur * lastSep = NULL;
bool ok;
Sentence * tempS;
   while((le=code.indexOf("\n-"))!=-1)
{
//qDebug() << "before "<< before;

tempS = Sentence::parseSentence(this,code.left(le+1));

     //  ui->textFichierSource->append(code.left(le+1)+"--------------------- itération "+QString::number(i++)+"\n");


       code.remove(0,le+1);
      tempS->setExtremity(before,after=code.section(' ',1,1).section('\n',0,0).toInt(&ok));

      if(code.section('\n',0,0).section(' ',0,0).compare("-"))
      {
          sepTime1 = -(code.section('\n',0,0).section(' ',0,0).toInt(&ok));
          sepTime2 = (code.section('\n',0,0).section(' ',-1,-1).toInt(&ok));
          if(sepTime2<0) sepTime2=-sepTime2;

      }
      else
      {
          sepTime1 = (code.section('\n',0,0).section(' ',1,1).toInt(&ok));
          sepTime2 = (code.section('\n',0,0).section(' ',-1,-1).toInt(&ok));
      }


      tempS->setSepBefore(lastSep);
      lastSep = new USeparateur(sepTime1,sepTime2-sepTime1);
      tempS->setSepAfter(lastSep);



      before=after;
      if(!ok) //probleme pour parse le int
       {

          QMessageBox::warning(parent,QObject::tr("Erreur"),QObject::tr("Problème pour parser le fichier .txt\n Lors de la lecture des ligne commençant par - : \n")+code.section('-',0,1));
            delete tempS;
        }

       sentences.push_back(tempS);
       words.append(*tempS->getWords());

       if(tempS->getPitchMax()>pitchMax) pitchMax=tempS->getPitchMax();
       if(tempS->getPitchMin()<pitchMin) pitchMin=tempS->getPitchMin();


       // qDebug()<< "after "<< before << "  " << ok <<"\n";

   }

    tempS = Sentence::parseSentence(this,code.left(code.length()-2));


    tempS->setSepBefore(lastSep);
    tempS->setSepAfter(NULL);



    tempS->setExtremity(before,code.section(":",-1).section(" ",1,1).toInt());
    if(!ok) //probleme pour parse le int
    {
            QMessageBox::warning(parent,QObject::tr("Erreur"),QObject::tr("Problème pour parser le fichier .txt\n Lors de la lecture de la derniere phrase - : \n")+code.section('-',0,1));
            delete tempS;
    }

       sentences.push_back(tempS);
       words.append(*tempS->getWords());

       *maxH=tempS->getEnd();

       return maxH;

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

    foreach(w,words)
    {
        if(trouve)
        {
            wBefore->setWord(w->getWord());
            w->setWord("");

        }

        if(!trouve && wBefore && wBefore->equal(*from))
        {
            wBefore->setWord(wBefore->getWord()+w->getWord());

            trouve=true;

        }

        wBefore=w;
    }


}


Word * Lyrics::moveRight(Word *from, int indexIWant)
{


    Word * ret = from;


    bool trouve = false;
    Word * w;
    Word * wBefore=NULL;

    QString temp="", temp2="";

    int i=0;

    qDebug()<<"Move Left : "<<words.count();
    foreach(w,words)
    {
        if(trouve)
        {
            temp2=w->getWord();
            w->setWord(temp);

            temp = temp2;

            if(++i == indexIWant)
            {
                ret = w;
            }
            //qDebug()<<"- "<<wBefore->getWord();
        }

        if(!trouve && wBefore && wBefore->equal(*from))
        {
            temp = w->getWord();
            w->setWord(wBefore->getWord());

            trouve=true;
            //qDebug()<<"FIRST : "<<wBefore->getWord();

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
        w->setWord(w->getWord()+temp);
    }

    return ret;


}

QList<USeparateur*> * Lyrics::separatorsOfWords(QList<Word *> * list)
{
    QList<USeparateur*> * sep= new QList<USeparateur*>();

    Word* w;
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
    }



    return sep;

}
QList<Sentence*> * Lyrics::sentencesOfWords(QList<Word *> * list)
{
    QList<Sentence*> * sen= new QList<Sentence*>();

    Word* w;
    foreach(w,*list)
    {
        if(!sen->contains(w->getParent()))
        {
            sen->push_back(w->getParent());
        }

    }



    return sen;

}
void Lyrics::sortThisWord(Word *wdr)
{
    if(words.count()<2) { return; }

    words.removeOne(wdr);
    Word * w;

    Word * last = NULL;

    int k=0;

    foreach(w,words)
    {
        if(w->getTime()>wdr->getTime())
        {
            words.insert(k,wdr);
            break;
        }
        last = w;
        ++k;
    }
    if(k==words.count())
    {
        words.push_back(wdr);
    }


    Sentence * s = wdr->getParent();

    if(w->getParent()->getSepAfter() && w->getParent()->getSepAfter()->getTime()<wdr->getTime())
    {
        //do nothing
    }
    else
    if(!last || !w->getParent()->getSepBefore() ||  w->getParent()->getSepBefore()->getTime1()<wdr->getTime())
    {
        wdr->getParent()->getWords()->removeOne(wdr);
        w->getParent()->addWord(wdr);
    }
    else
    {
        wdr->getParent()->getWords()->removeOne(wdr);
        last->getParent()->addWord(wdr);
    }

    if(s->getWords()->empty())
    {
        removeSentence(s);
    }
}


void Lyrics::sortThisSeparator(USeparateur *s)
{
    if(words.empty()) { return; }


    Word * w;

    Word * last = NULL;


    foreach(w,words)
    {
        if(w->getTime()>s->getTime1())
        {
            if(w->getParent()->getSepBefore() == s && last && last->getParent()->getSepAfter() == s)// it's already ok
            {
                return;
            }

            if(!last) // we put the sep before the first word = we just delete it
            {
                deleteSeparator(s);
                return;
            }
            // else we delete it and we will create a new

            qDebug()<<"AVANT SEP : "<<separatorsOfWords(&words)->count();

            deleteSeparator(s);
            qDebug()<<"MILIEU SEP : "<<separatorsOfWords(&words)->count();
            addSeparator(s->getTime1(), s->getLength());


            qDebug()<<"APRE SEP : "<<separatorsOfWords(&words)->count();



            break;
        }
        last = w;
    }
}

USeparateur *  Lyrics::addSeparator(int time, int length)
{

    Word * w ;
    Sentence * s;
    Sentence * into = NULL;

    foreach(s,sentences)
    {
        if(s->getWords()->first()->getTime() < time
           && s->getWords()->last()->getTime() > time )
        {
            into = s;
            break;
        }
    }

    if(!into) return NULL;

    Sentence * newSent = new Sentence(this);
    USeparateur * newSep = new USeparateur(time,length);


    QList<Word*> wordChange;
    foreach(w,*into->getWords())
    {
        if(w->getTime()>time)
        {
            wordChange.push_back(w);
        }
    }

    foreach(w,wordChange)
    {
        into->getWords()->removeOne(w);
        newSent->addWord(w);
    }

    newSent->setSepAfter(into->getSepAfter());
    newSent->setSepBefore(newSep);

    into->setSepAfter(newSep);

    addSentence(newSent);

    return newSep;



}
void Lyrics::deleteSeparator(USeparateur *s)
{
    if(s==NULL) return;

    Sentence * before=NULL;
    Sentence * sent;
    Sentence * Supp=NULL;

    foreach(sent,sentences)
    {
        if(sent->getSepAfter() == s)
        {
            before = sent;
        }
        else
        if(before && sent->getSepBefore() == s) // move those words to the sentence before
        {
            Supp = sent;
            before->addWords(*sent->getWords());
            break;
        }
    }

    if(Supp)
    {
        before->setSepAfter(Supp->getSepAfter());

        sentences.removeOne(Supp);
    }

}

void Lyrics::addSentence(Sentence *sent)
{
    Sentence * s;

    int k=0;
    if(sent->getSepAfter())
    {
        foreach(s,sentences)
        {
            if(s->getSepAfter() && sent->getSepAfter()->getTime1() < s->getSepAfter()->getTime1())
            {
                sentences.insert(k,sent);
                return;
            }
            ++k;
        }
    }

    sentences.push_back(sent);
}

void Lyrics::removeWord(Word *w)
{
    Sentence  * s;
    foreach(s,sentences)
    {
        if(s->getWords()->contains(w))
        {
            s->getWords()->removeOne(w);
            if(s->getWords()->empty())
            {
                removeSentence(s);
            }
            break;
        }
    }
    words.removeOne(w);

}
void Lyrics::removeSentence(Sentence *sent)
{
    if(!sent->getWords()->empty())
    {
        foreach(Word *w,*sent->getWords())
        {
            removeWord(w);
        }
    }

    if(sent->getSepBefore())
    {
        deleteSeparator(sent->getSepBefore());
        return;
    }

    if(sent->getSepAfter())
    {
        deleteSeparator(sent->getSepAfter());
        return;
    }

    sentences.removeAll(sent);

}
void Lyrics::addWord(Word *ws)
{
    Sentence  * s;

    if(sentences.empty())
    {
        sentences.push_back(new Sentence(this,0,0));
    }

    foreach(s,sentences)
    {
        if(!s->getSepAfter() || s->getSepAfter()->getTime1() > ws->getTime())
        {
            s->addWord(ws);
            break;
        }
    }

    Word  * w;
    int k =0;
    foreach(w,words)
    {
        if(w->getTime() > ws->getTime())
        {
            words.insert(k,ws);
            return;
        }
        ++k;
    }
    words.push_back(ws);


}

void Lyrics::sortAll()
{
    if(words.empty()) return;
/*
    _lines.clear();


    foreach(Sentence*s,sentences)
    {
        foreach(Word*w,*s->getWords())
        {
             _lines.push_back(w);
         }

        if(s->getSepAfter() && !_lines.contains(s->getSepAfter()))
        {
                _lines.push_back(s->getSepAfter());
        }
    }

   // qSort(_lines.begin(),_lines.end(),UAbstractLine::lessThan);

    //fromLines(&_lines);*/




    qSort(words.begin(),words.end(),Word::wordLessThanPtr);

    foreach(Sentence *s,sentences)
    {
        qSort(s->getWords()->begin(),s->getWords()->end(),Word::wordLessThanPtr);
    }

    USeparateur * rightSep;

    foreach(Sentence *s,sentences)
    {
        if(s->getSepAfter() && s->getSepBefore())
        {
            rightSep = s->getSepAfter();

            foreach(Word * w,*rightSep->getRightSentence()->getWords())
            {
                if(w->getTime()>rightSep->getTime1()) break;
/*
                rightSep->getRightSentence()->getWords()->removeAll(w);
                s->addWord(w);*/
                qDebug()<<"HAPPEN1 "<<w->getWord();
           }
           if(rightSep->getRightSentence()->getWords()->empty())
            {
                this->removeSentence(rightSep->getRightSentence());
            }


            if(rightSep->getTime1()<s->getSepBefore()->getTime1())
            {
                qDebug()<<"HAPPEN ";//<<w->getWord();

                USeparateur * temps = s->getSepBefore();
                s->setSepBefore(s->getSepAfter());
                s->setSepAfter(rightSep->getRightSentence()->getSepAfter());

                rightSep->getRightSentence()->setSepBefore(temps);
                rightSep->getRightSentence()->setSepAfter(s->getSepBefore());

                int i = sentences.indexOf(s);
                sentences.removeOne(s);
                sentences.insert(i+1,s);

            }

        }

    }



}

int * Lyrics::fromLines(QList<UAbstractLine *> *lines)
{
    words.clear();
    sentences.clear();

    QList<USeparateur*> sep;

    foreach(UAbstractLine*l,*lines)
    {
        if(lines->first()->getType()==TYPE_NOTE)
        {
            words.push_back((Word*)l);
        }
        else
        {
            sep.push_back((USeparateur*)l);
        }
    }
    if(words.empty()) return NULL;

    Sentence * sent = new Sentence(this,0,0);
    sent->addWords(words);
    sentences.push_back(sent);

    foreach(USeparateur * s,sep)
    {
        addSeparator(s->getTime(),s->getLength());
    }

    return NULL;

}

void Lyrics::doublePresicion()
{
    if(_bpm>800) {
        QMessageBox::warning(NULL,tr("impossible"),tr("le BPM est déjà bien assez grand"));
        return;
    }

    foreach(Word *w,words)
    {
        w->setTime(w->getTime()*2);
        w->setLength(w->getLength()*2);
    }

    foreach(Sentence*s,sentences)
    {
        if(s->getSepAfter())
        {
            s->getSepAfter()->setTime(s->getSepAfter()->getTime()*2);
            s->getSepAfter()->setLength(s->getSepAfter()->getLength());
        }
    }

}
