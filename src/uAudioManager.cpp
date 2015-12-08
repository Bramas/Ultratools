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





#include "timebase.h"
#include "uAudioManager.h"
#include "uWidgetSongData.h"
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <limits>
#include <algorithm>


UAudioManager UAudioManager::Instance;

UAudioManager::UAudioManager() : _sound(NULL), _channel(NULL), _widgetSongData(0), _lastPosition(0), _granularity(0), _delta(0), _speedFactor(1)
{
    _initialised=false;

    _tickTimer = new QTimer(this);
    _tickTimer->setInterval(0);
      connect(_tickTimer, SIGNAL(timeout()), this, SLOT(timerOut()));
}

FMOD_RESULT F_CALLBACK endCallback(FMOD_CHANNEL */*channel*/, FMOD_CHANNEL_CALLBACKTYPE type, void * /*commanddata1*/, void * /*commanddata2*/)
{
    qDebug()<<(int)type;
    if(type != FMOD_CHANNEL_CALLBACKTYPE_END)
    {
        return FMOD_OK;
    }
    QTimer::singleShot(0,&UAudioManager::Instance, SLOT(emitEndOfSong()));
    return FMOD_OK;
}

typedef signed short pcm16;

void UAudioManager::clear()
{
    this->pause();
    if (_channel)
    {
        FMOD_Channel_Stop(_channel);
        _channel = NULL;
    }
    if(_sound)
    {
        FMOD_Sound_Release(_sound);
        _sound = NULL;
    }
    _widgetSongData->clearData();
    _source = "";
}

bool UAudioManager::setSource(QString source)
{
    clear();

    _source=source;
    _result = FMOD_System_CreateSound(_system,_source.toStdString().c_str(), FMOD_LOOP_NORMAL | FMOD_2D | FMOD_SOFTWARE | FMOD_CREATESAMPLE, 0, &_sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
    if (_result != FMOD_OK) return false;

    _result = FMOD_Sound_GetDefaults(_sound, &_frequency, NULL, NULL, NULL);
    if (_result != FMOD_OK) return false;

    _result = FMOD_System_PlaySound(_system,FMOD_CHANNEL_FREE, _sound, true, &_channel);
    if (_result != FMOD_OK) return false;

    _result = FMOD_Channel_SetFrequency(_channel,_frequency * _speedFactor);
    if (_result != FMOD_OK) return false;

    _result = FMOD_Channel_SetCallback(_channel, endCallback);
    if (_result != FMOD_OK) return false;


    pcm16  *pointer[2] = {0, 0};
    unsigned int length[2];
    unsigned int totalLength;
    unsigned int totalMscLength;


    FMOD_SOUND_FORMAT format = FMOD_SOUND_FORMAT_NONE;
    FMOD_Sound_GetFormat(_sound, 0, &format, 0, 0);
    qDebug()<<"format:"<<format;
    qDebug()<<"PCM16? "<<(format == FMOD_SOUND_FORMAT_PCM16);

    _result = FMOD_Sound_GetLength(_sound, &totalLength, FMOD_TIMEUNIT_PCMBYTES);
    if (_result != FMOD_OK) return false;

    FMOD_Sound_GetLength(_sound, &totalMscLength, FMOD_TIMEUNIT_MS);
    qDebug()<<"totalLength? "<<totalLength<<" bytes "<<totalMscLength<<" Ms";

    // lock the buffer
    _result = FMOD_Sound_Lock(_sound, 0, totalLength, (void**)&pointer[0], (void**)&pointer[1], &length[0], &length[1]);
    if (_result != FMOD_OK) return false;

    int sizeOfBin = 100, nSamples = 0;
    pcm16 channelMax[2];
    _widgetSongData->clearData();

    for(int part = 0; part < 2; part++)
    {
        pcm16 *end = pointer[part] + length[part] / sizeof(pcm16);
        for(pcm16 *p = pointer[part]; p < end; p++)
        {
            if(nSamples >> 1)
                channelMax[nSamples & 1] = std::max(channelMax[nSamples & 1], *p);
            else
                channelMax[nSamples & 1] = *p;
            if(++nSamples == sizeOfBin << 1)
            {
                nSamples = 0;
                _widgetSongData->addData((qreal)channelMax[0]/(qreal)SHRT_MAX, (qreal)channelMax[1]/(qreal)SHRT_MAX);
            }
        }
    }
    if(nSamples)
        _widgetSongData->addData((qreal)channelMax[0]/(qreal)SHRT_MAX, (qreal)channelMax[1]/(qreal)SHRT_MAX);
    FMOD_Sound_Unlock(_sound, pointer[0], pointer[1], length[0], length[1]);
    _widgetSongData->show();

    return true;

}
void UAudioManager::timerOut()
{
    FMOD_System_Update(_system);

    emit tick(currentTime());

}

void UAudioManager::seek(quint64 startTime)
{
    unsigned int time = startTime;
    FMOD_Channel_SetPosition(
      _channel,
        time,
      FMOD_TIMEUNIT_MS
    );
}

void UAudioManager::changeVolume(int i)
{
    float f=i;
    f/=100;
    FMOD_Channel_SetVolume(_channel,f);

}

quint32 UAudioManager::length()
{
    if(_source.isEmpty())
        return 0;
    quint32 l=0;
    FMOD_RESULT ok = FMOD_Sound_GetLength(_sound, &l, FMOD_TIMEUNIT_MS);
    if(ok != FMOD_OK)
    {
        return 0;
    }
    return l;
}

void UAudioManager::changeSpeed(double factor)
{
    _granularity = 0;
    _speedFactor = factor;
    FMOD_Channel_SetFrequency(_channel,_frequency * factor);
}

void UAudioManager::play()
{
    FMOD_Channel_SetPaused(_channel,false);
    _tickTimer->start();
}
void UAudioManager::pause()
{
    FMOD_Channel_SetPaused(_channel,true);
    _tickTimer->stop();
}

bool UAudioManager::timestampToPosition(ulong &time)
{
    if(!_tickTimer->isActive() || (qint64)time < _delta)
        return false;
    time = (ulong)(time * _speedFactor) - _delta;
    return true;
}

quint64 UAudioManager::currentTime()
{
    unsigned int time;
    qint64 pre, delta;

    pre = now();
    if (FMOD_Channel_GetPosition(_channel, &time, FMOD_TIMEUNIT_MS) != FMOD_OK)
    {
        time = _lastPosition;
    }
    if (time > _lastPosition)
    {
        unsigned int fmoddelta = time - _lastPosition;
        if (_granularity > fmoddelta || !_granularity)
            _granularity = fmoddelta;
    }
    _lastPosition = time;
    pre *= _speedFactor;
    delta = pre - time;
    if (_delta > delta || _delta + _granularity + 2 < delta)
        _delta = delta;

    return (quint64)(pre - _delta);
}

void UAudioManager::init()
{

    _initialised=true;
_result = FMOD_System_Create(&_system);
 // Create the main system object.


if (_result != FMOD_OK)
{

    QMessageBox::information(NULL,"","error : "+QString::number(_result)+" , "+FMOD_ErrorString(_result));

    return ;
}
FMOD_System_SetSoftwareChannels(
  _system,
  50
);

_result = FMOD_System_Init(_system,50, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
if (_result != FMOD_OK)
{
    QMessageBox::information(NULL,"","error : "+QString::number(_result)+" , "+FMOD_ErrorString(_result));

    return ;
}





}
