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

#include <QApplication>
#include <QFileInfo>
#include <cmath>
#include <QDebug>
#include <QMessageBox>
#include <QStandardPaths>
#include "uWord.h"
#include "uLyrics.h"
#include "uNoteManager.h"

UNoteManager UNoteManager::Instance;

UNoteManager::UNoteManager()
{
    _lyrics = NULL;
_maxPitch = 18;
_pitchOffset = 0;
_isPlaying= false;

}

QString UNoteManager::violonFile(int i)
{
#ifdef __APPLE__

    QFileInfo f(QApplication::applicationDirPath()+"/../Resources/violon/"+QString::number(i)+".mp3");
    if(!f.exists())
    {
        f = QFileInfo(QApplication::applicationDirPath()+"/../../../violon/"+QString::number(i)+".mp3");
    }
#else
#ifdef _WIN32
    QFileInfo f(QApplication::applicationDirPath()+"/violon/"+QString::number(i)+".mp3");
#else
#if QT_VERSION < QT_VERSION_CHECK(5,4,0)
    QStringList dirs(QStandardPaths::standardLocations(QStandardPaths::DataLocation));
#else
    QStringList dirs(QStandardPaths::standardLocations(QStandardPaths::AppDataLocation));
#endif
    QFileInfo f;
    foreach(const QString &d, dirs) {
        f.setFile(d+"/violon/"+QString::number(i)+".mp3");
        if (f.exists())
            break;
    }
#endif
#endif
    if(!f.exists())
    {
        QMessageBox::warning(0, trUtf8("Fichier introuvable"), trUtf8("Les fichiers des notes de musiques sont introuvalbes:")+" "+f.absoluteFilePath());
        return "";
    }
    return f.absoluteFilePath();
}

void UNoteManager::setupAudio(QObject * /*parent*/)
{
    _system = UAudioManager::Instance.getSystem();

    FMOD_SOUND * sound;
    FMOD_CHANNEL * channel;
    FMOD_System_CreateChannelGroup(_system, NULL, &_notesGroup);


    QString root = "violon/";
    QString tmp;
   for(int i = -36 ; i<5 ; ++i)//5
    {
       QString violonFilePath = violonFile(i);
       if(violonFilePath.isEmpty())
       {
            return;
       }
        _result = FMOD_System_CreateSound(_system,violonFilePath.toLatin1().data(),
                                          FMOD_LOOP_NORMAL | FMOD_2D | FMOD_SOFTWARE, 0, &sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.

        //ERRCHECK(result);

        _result = FMOD_System_PlaySound(_system,FMOD_CHANNEL_FREE, sound, true, &channel);
        //ERRCHECK(result);

       _sounds.insert(i,sound);
        _channels.insert(i,channel);
        FMOD_Channel_SetChannelGroup(channel, _notesGroup);


    }
/*   FMOD_BOOL rep;
   FMOD_Channel_GetPaused(_channels[-15], &rep);
   qDebug()<<(bool)rep;
   FMOD_Channel_SetPaused(_channels[-15],false);
   FMOD_Channel_GetPaused(_channels[-15], &rep);
   qDebug()<<(bool)rep;
 */

}

void UNoteManager::play(const Word & w)
{
    _isPlaying = true;
    //QMessageBox::information(NULL,"","LOL");
    if(_played.contains(w)) return;

    _played.push_back(w);

    //QMessageBox::information(NULL,"",QString::number(pitchToNote(w.getPitch())));
  // _violonList.value(pitchToNote(w.getPitch()))->play();

    FMOD_BOOL rep;
    FMOD_Channel_GetPaused(_channels[pitchToNote(w.getPitch())], &rep);
    if(rep)
    {
        FMOD_Channel_SetPaused(_channels[pitchToNote(w.getPitch())],false);
        //qDebug()<<"play "<<pitchToNote(w.getPitch());
    }


}

int UNoteManager::pitchToNote(int note)
{
    int noteOffset = _maxPitch + _pitchOffset;
    while(noteOffset > 0) { noteOffset -= 12; }
    while(noteOffset < -10) { noteOffset += 12; }
    noteOffset = noteOffset - _maxPitch;

    note += noteOffset;
    note += 1;
    //qDebug()<<_maxPitch << "  "<<noteOffset + _maxPitch<< "  " << noteOffset<<"  :  "<<note;

    return note;
}

bool UNoteManager::checkPitch(int p)
{
    foreach(const Word & w,_played)
    {
        if(w.getPitch()==p)
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
    FMOD_ChannelGroup_SetVolume(_notesGroup, f);
}

void UNoteManager::changePitch(int offset)
{
    if (_pitchOffset == offset)
        return;

    QSet<int> playing;

    foreach(const Word & w, _played)
    {
        playing |= pitchToNote(w.getPitch());
    }

    _pitchOffset = offset;

    foreach(const Word & w, _played)
    {
        int note = pitchToNote(w.getPitch());
        if (playing.contains(note))
        {
            playing -= note;
        }
        else
        {
            FMOD_Channel_SetPaused(_channels[note],false);
        }
    }

    foreach(int note, playing)
    {
        FMOD_Channel_SetPaused(_channels[note],true);
        FMOD_Channel_SetPosition(_channels[note],0,FMOD_TIMEUNIT_MS);
    }
}

void UNoteManager::tick(quint64 time)
{
    if(!_lyrics || _played.empty() || !_isPlaying) return;

    //qDebug()<<(((time-floor(_lyrics->getGap()))/1000.0) * _lyrics->getBpm()/15.0f)<< "  "<<_played.first()->getTime() + _played.first()->getLength();

    double temp = (((time-floor(_lyrics->getGap()))/1000.0) * _lyrics->getBpm()/15.0f);

    foreach(const Word & w, _played)
    {
        if( temp  > w.getTime() + w.getLength() + 0.5 || temp < w.getTime() - 0.2)
        {
            _played.removeOne(w);
            if(!checkPitch(w.getPitch()))
            {
                FMOD_BOOL rep;
                FMOD_Channel_GetPaused(_channels[pitchToNote(w.getPitch())], &rep);
                if(!rep)
                {
                    FMOD_Channel_SetPaused(_channels[pitchToNote(w.getPitch())],true);
                    //qDebug()<<"stop "<<pitchToNote(w.getPitch());
                }
                FMOD_Channel_SetPosition(_channels[pitchToNote(w.getPitch())],0,FMOD_TIMEUNIT_MS);
            }

        }
    }


}

void UNoteManager::pause()
{
    _isPlaying=false;

    for(int i = -36 ; i<5 ; ++i)//5
    {
        FMOD_Channel_SetPaused(_channels[i],true);
        FMOD_Channel_SetPosition(_channels[i],0,FMOD_TIMEUNIT_MS);
    }

    _played.clear();

}
void UNoteManager::play()
{
    _isPlaying=true;
    
    if(!_played.empty())
    {
        foreach(const Word & w, _played)
        {
                FMOD_Channel_SetPaused(_channels[pitchToNote(w.getPitch())],false);

        }
    }
}
