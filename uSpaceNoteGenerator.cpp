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

#include <math.h>


#include "uSpaceNoteGenerator.h"
#include "uInputManager.h"
#include "uFile.h"

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

void USpaceNoteGenerator::keyPressEvent()
{
    if(!isRecording)
    {
        return;
    }
    _currentWord = new Word(NULL,_beat,1,0);
    _currentWord->setText("");

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
    int j=0;
    int lastTime = 0, lastPitch = 60;

    foreach(const QString &line, lines)
    {
        foreach(const QString &lineW, line.split(' '))
        {
            if(j >= _words.count())
            {
                lyrics->addWord(new Word(lyrics, lastTime, 4, lastPitch));
                lastTime += 5;
            }
            else
            {
                lastPitch = _words.at(j)->getPitch();
                lastTime = _words.at(j)->getTime2() + 1;
                lyrics->addWord(_words.at(j++));
            }
        }
        lyrics->addSeparator(lastTime++);
    }
}
