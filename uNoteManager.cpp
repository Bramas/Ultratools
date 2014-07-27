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

#include <QApplication>
#include <QFileInfo>
#include "uNoteManager.h"

UNoteManager UNoteManager::Instance;

UNoteManager::UNoteManager()
{

    _lyrics = NULL;
_maxPitch = 18;
_isPlaying= false;

}

QString UNoteManager::violonFile(int i)
{
    QFileInfo f(QApplication::applicationDirPath()+"/../../../violon/"+QString::number(i)+".mp3");
    return f.absoluteFilePath();
}

void UNoteManager::setupAudio(QObject *parent)
{
    _system = UAudioManager::Instance.getSystem();

    FMOD_SOUND * sound;
    FMOD_CHANNEL * channel;


    QString tmp;
   for(int i = -36 ; i<5 ; ++i)//5
    {
        _result = FMOD_System_CreateSound(_system,violonFile(i).toLatin1().data(), FMOD_DEFAULT, 0, &sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
        //ERRCHECK(result);

        _result = FMOD_System_PlaySound(_system,FMOD_CHANNEL_FREE, sound, true, &channel);
        //ERRCHECK(result);

       _sounds.insert(i,sound);
        _channels.insert(i,channel);


    }
/* */

}

void UNoteManager::play(Word * w)
{
    _isPlaying = true;
    //QMessageBox::information(NULL,"","LOL");
    if(_played.contains(w)) return;

    _played.push_back(w);

    //QMessageBox::information(NULL,"",QString::number(pitchToNote(w->getPitch())));
  // _violonList.value(pitchToNote(w->getPitch()))->play();



    FMOD_Channel_SetPaused(_channels[pitchToNote(w->getPitch())],false);


}

int UNoteManager::pitchToNote(int note)
{
    while(note>3+_maxPitch+5-(_maxPitch+5)%12 + 12) { note-=12; }
    while(note<-36+_maxPitch+5-(_maxPitch+5)%12 + 12) { note+=12; }

    note -= _maxPitch+5-(_maxPitch+5)%12 + 12;
    note += 1;

    return note;
}

bool UNoteManager::checkPitch(int p)
{
    foreach(Word * w,_played)
    {
        if(w->getPitch()==p)
        {
            return true;
        }
    }
    return false;
}
void UNoteManager::setVolume(int v)
{
    float f=v;
    f/=100;
    for(int i = -36 ; i<5 ; ++i)//5
    {
        FMOD_Channel_SetVolume(_channels[i],f);
    }
}

void UNoteManager::tick(quint64 time)
{
    if(!_lyrics || _played.empty() || !_isPlaying) return;

    //qDebug()<<(((time-floor(_lyrics->getGap()))/1000.0) * _lyrics->getBpm()/15.0f)<< "  "<<_played.first()->getTime() + _played.first()->getLength();

    double temp = (((time-floor(_lyrics->getGap()))/1000.0) * _lyrics->getBpm()/15.0f);

    foreach(Word * w, _played)
    {
        if( temp  > w->getTime() + w->getLength()+2 || temp < w->getTime())
        {


            //_violonList.value(pitchToNote(w->getPitch()))->stop();
           // if(_played.empty()) _violon->stop();
            _played.removeOne(w);

            if(!checkPitch(w->getPitch()))
            {
                FMOD_Channel_SetPaused(_channels[pitchToNote(w->getPitch())],true);
                FMOD_Channel_SetPosition(_channels[pitchToNote(w->getPitch())],0,FMOD_TIMEUNIT_MS);
            }

        }
    }


}

void UNoteManager::pause()
{
    _isPlaying=false;
    foreach(Word * w, _played)
    {
        FMOD_Channel_SetPosition(_channels[pitchToNote(w->getPitch())],0,FMOD_TIMEUNIT_MS);
        FMOD_Channel_SetPaused(_channels[pitchToNote(w->getPitch())],true);

    }

    _played.clear();

}
void UNoteManager::play()
{
    _isPlaying=true;
    
    if(!_played.empty())
    {
        foreach(Word * w, _played)
        {

                FMOD_Channel_SetPaused(_channels[pitchToNote(w->getPitch())],false);

        }
    }
}
