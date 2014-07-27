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


#include "uSentence.h"
#include "uLyrics.h"

Sentence::Sentence(Lyrics * parent, int timeBefore, int timeAfter)
{
    this->timeAfter=timeAfter;
    this->timeBefore=timeBefore;
    pitchMax=0;
    pitchMin=255;
    _parent = parent;

    _sepBefore=NULL;
    _sepAfter=NULL;



}
QList<Word*> * Sentence::getWords(void)
{
    return &words;
}



int  Sentence::getStart(void)
{
    return this->timeBefore;
}
int  Sentence::getEnd(void)
{
    return this->timeAfter;
}

Sentence * Sentence::parseSentence(Lyrics * parent,QString code)
{
    Sentence * s = new Sentence(parent);

QStringList sCode=code.split("\n",QString::SkipEmptyParts);
QString str;
for(int i=0;i<sCode.length();i++)
{

    if((str=sCode.at(i)).at(0)==':' || str.at(0)=='*' || str.at(0)=='F')
    {
         s->words.push_back(new Word(s,str.section(" ",1,1).toInt(),
                                     str.section(" ",2,2).toInt(),
                                     str.section(" ",3,3).toInt(),
                                     (str.at(0)=='*'?true:false)));
         if(str.at(0)=='F')
         {
              s->words.back()->setFree(true);
         }
         //str=str.section(" ",-2,-1);
        // str=str.remove(0,str.indexOf(" ")+1);//
         str.remove(0,str.section(" ",0,3).length()+1);

         s->words.back()->setWord(str);
         if(s->words.back()->getPitch()<s->pitchMin) s->pitchMin=s->words.back()->getPitch();
         if(s->words.back()->getPitch()>s->pitchMax) s->pitchMax=s->words.back()->getPitch();
    }

}


// qDebug() << "'" <<code<<"'";

    return s;
}


void Sentence::setExtremity(int before, int after)
{
    this->timeAfter=after;
    this->timeBefore=before;
   // qDebug()<<"    before : " << before << "   after:  "<< after<<"\n";
}

int Sentence::getPitchMax()
{
    return pitchMax;
}
int Sentence::getPitchMin()
{
    return pitchMin;
}

void Sentence::addWord(Word *wdr)
{
    Word * w;
    int k = 0;
    foreach(w,words)
    {
        if(w->getTime()>wdr->getTime())
        {
            words.insert(k,wdr);
            wdr->setParent(this);
            return;
        }
        ++k;
    }

    wdr->setParent(this);
    words.push_back(wdr);

}

void Sentence::addWords(QList<Word *> ws)
{
     Word * w;
     foreach(w,ws)
     {
         addWord(w);
     }
}
void Sentence::modified(QString sender)
{
    _parent->modified(sender);
}
