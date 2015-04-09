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




#include "uAudioManager.h"
#include "uWidgetSongData.h"
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <limits>


UAudioManager UAudioManager::Instance;

UAudioManager::UAudioManager() : _sound(NULL), _channel(NULL), _widgetSongData(0)
{
    _initialised=false;

    _tickTimer = new QTimer(this);
    _tickTimer->setInterval(0);
      connect(_tickTimer, SIGNAL(timeout()), this, SLOT(timerOut()));
}

FMOD_RESULT F_CALLBACK endCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void * /*commanddata1*/, void * /*commanddata2*/)
{
    qDebug()<<(int)type;
    if(type != FMOD_CHANNEL_CALLBACKTYPE_END)
    {
        return FMOD_OK;
    }
    QTimer::singleShot(0,&UAudioManager::Instance, SLOT(emitEndOfSong()));
}

typedef signed short pcm16;
float pcm16ToFloat(const pcm16 in) {
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;

    float out;

    t1 = in & 0x7fff;                       // Non-sign bits
    t2 = in & 0x8000;                       // Sign bit
    t3 = in & 0x7c00;                       // Exponent

    t1 <<= 13;                              // Align mantissa on MSB
    t2 <<= 16;                              // Shift sign bit into position

    t1 += 0x38000000;                       // Adjust bias

    t1 = (t3 == 0 ? 0 : t1);                // Denormals-as-zero

    t1 |= t2;                               // Re-insert sign bit

    *((uint32_t*)(&out)) = t1;
    return out;
}

bool UAudioManager::setSource(QString source)
{
    _source=source;

    if(_sound)
    {
        FMOD_Sound_Release(_sound);
    }

    _result = FMOD_System_CreateSound(_system,_source.toStdString().c_str(), FMOD_LOOP_NORMAL | FMOD_2D | FMOD_SOFTWARE , 0, &_sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
    //ERRCHECK(result);

    _result = FMOD_System_PlaySound(_system,FMOD_CHANNEL_FREE, _sound, true, &_channel);
    FMOD_Channel_SetCallback(_channel, endCallback);


    FMOD_SOUND * sound;
    FMOD_System_CreateSound(_system,_source.toStdString().c_str(), FMOD_LOOP_NORMAL | FMOD_2D | FMOD_SOFTWARE | FMOD_CREATESAMPLE, 0, &sound);



    pcm16  *pointer1 = 0;
    pcm16  *pointer2 = 0;
    unsigned int length1;
    unsigned int length2;
    unsigned int totalLength;
    unsigned int totalMscLength;


    FMOD_SOUND_FORMAT format = FMOD_SOUND_FORMAT_NONE;
    FMOD_Sound_GetFormat(sound, 0, &format, 0, 0);
    qDebug()<<"format:"<<format;
    qDebug()<<"PCM16? "<<(format == FMOD_SOUND_FORMAT_PCM16);

    FMOD_Sound_GetLength(sound, &totalLength, FMOD_TIMEUNIT_PCMBYTES);
    FMOD_Sound_GetLength(sound, &totalMscLength, FMOD_TIMEUNIT_MS);
    quint64 t = (quint64)totalMscLength;
    qDebug()<<"totalLength? "<<totalLength<<" bytes "<<totalMscLength<<" Ms";

    // lock the buffer
    FMOD_Sound_Lock(sound, 0, totalLength, (void**)&pointer1, (void**)&pointer2, &length1, &length2);

    totalLength/=2;
    double sum = 0;
    int sizeOfBin = 100;
    _widgetSongData->clearData();
    for(unsigned int i = 0; i < totalLength; i += 2*sizeOfBin)
    {

        pcm16 leftMax = *pointer1;
        ++pointer1;
        pcm16 rightMax = *pointer1;
        ++pointer1;
        for(int m = 0; m < sizeOfBin-1; ++m)
        {
            if(leftMax < *pointer1)
            {
                leftMax = *pointer1;
            }
            ++pointer1;
            if(rightMax < *pointer1)
            {
                rightMax = *pointer1;
            }
            ++pointer1;
        }
        _widgetSongData->addData((qreal)leftMax/(qreal)SHRT_MAX, (qreal)rightMax/(qreal)SHRT_MAX);
    }
    FMOD_Sound_Unlock(sound, pointer1, pointer2, length1, length2);
    _widgetSongData->show();

    return true;

}
void UAudioManager::timerOut()
{
    FMOD_System_Update(_system);

    int sampleSize = 64;
    float *specLeft, *specRight;

    specLeft = new float[sampleSize];
    specRight = new float[sampleSize];

    // Get spectrum for left and right stereo channels
    FMOD_Channel_GetSpectrum(_channel, specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
    FMOD_Channel_GetSpectrum(_channel, specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT);

    float *spec;
    spec = new float[sampleSize];
    for (int i = 0; i < sampleSize; i++)
        spec[i] = (specLeft[i] + specRight[i]) / 2.0;

    int i = 0;
    //qDebug()<<(int)(spec[i++]*10)<<(int)(spec[i++]*10)<<(int)(spec[i++]*10)<<(int)(spec[i++]*10)<<(int)(spec[i++]*10)<<(int)(spec[i++]*10)<<(int)(spec[i++]*10)<<(int)(spec[i++]*10)<<(int)(spec[i++]*10);


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

quint64 UAudioManager::currentTime()
{
    unsigned int time;
    FMOD_Channel_GetPosition(
      _channel,
     &time,
      FMOD_TIMEUNIT_MS
    );

    return (quint64)time;
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
