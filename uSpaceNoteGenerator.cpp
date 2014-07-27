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




#include "uSpaceNoteGenerator.h"

USpaceNoteGenerator::USpaceNoteGenerator(UFile * file)
{
    _file = file;
    _beat=0;
    _currentWord = NULL;

    connect(&UInputManager::Instance,SIGNAL(spacePressEvent()),this,SLOT(spacePressEvent()));
    connect(&UInputManager::Instance,SIGNAL(spaceReleaseEvent()),this,SLOT(spaceReleaseEvent()));
}


void USpaceNoteGenerator::tick(qint64 time)
{
    _currentTime = time;
    _beat = _file->timeToBeat(time-_file->lyrics->getGap());
}

void USpaceNoteGenerator::spacePressEvent()
{

    if(!_words.empty() && _words.last()->getTime()+_words.last()->getLength()>=_beat && _words.last()->getLength()<5)
    {
        return;
    }

    _currentWord = new Word(NULL,_beat,1,0,false);
    _currentWord->setWord("~");



}
void USpaceNoteGenerator::spaceReleaseEvent()
{
    if(!_currentWord) return;

   // if(UInputManager::Instance.isKeyPressed(Qt::Key_Space))// QMessageBox::warning(NULL,"","lol");


    if(_beat - _currentWord->getTime()>1)
        _currentWord->setLength(_beat - _currentWord->getTime());

    _words.push_back(_currentWord);

    _currentWord = NULL;


}

QList<Word*> USpaceNoteGenerator::result()
{
    return _words;
}

int USpaceNoteGenerator::adaptGap()
{
    if(_words.empty()) return 0;
    
    
    int gap = _words.first()->getTime();

    foreach(Word * w, _words)
    {
        w->setTime(w->getTime()-gap);
    }

    return gap;
    
}

void USpaceNoteGenerator::generateLyrics(QString text, Lyrics * lyrics)
{

    int gap = adaptGap();

    lyrics->setGap(gap);

    QStringList lines = text.split('\n');

    int wordPerSentence = ceil(_words.count()/lines.count());

    int k =0;
    int j=0;
    foreach(Word * w,_words)
    {
        lyrics->addWord(w);
        if(k>=wordPerSentence && j<lines.count())
        {
            w->getParent()->getParent()->addSeparator(w->getTime()-1,0);
            k=0;
            ++j;
        }
        ++k;
    }

    QStringList temp;
    k=0;
    j=0;
    foreach(Sentence * s,*lyrics->getSentences())
    {
        if(!s->getWords()->empty())
        {
            j=0;
            if(lines.empty()) break;

            foreach(Word * w,*s->getWords())
            {
                w->setWord((lines.first().section(' ',j,j).compare("")?lines.first().section(' ',j,j,QString::SectionIncludeLeadingSep):"~"));
                ++j;
            }
            if(j<(temp = lines.first().split(' ')).count())
            {
                for(int i=0;i<j;++i)
                {
                    temp.pop_front();
                }
                s->getWords()->last()->setWord(temp.join(" "));
            }
            ++k;
            lines.pop_front();
        }

    }

}
