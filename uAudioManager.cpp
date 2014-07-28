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
#include <QTimer>
#include <QMessageBox>


UAudioManager UAudioManager::Instance;

UAudioManager::UAudioManager() : _sound(NULL), _channel(NULL)
{
    _initialised=false;

    _tickTimer = new QTimer(this);
    _tickTimer->setInterval(0);
      connect(_tickTimer, SIGNAL(timeout()), this, SLOT(timerOut()));
}

bool UAudioManager::setSource(QString source)
{
    _source=source;

    if(_sound)
    {
        FMOD_Sound_Release(_sound);
    }

    _result = FMOD_System_CreateStream(_system,_source.toStdString().c_str(), FMOD_DEFAULT, 0, &_sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
    //ERRCHECK(result);

    _result = FMOD_System_PlaySound(_system,FMOD_CHANNEL_FREE, _sound, true, &_channel);
    //ERRCHECK(result);

    return true;

}
void UAudioManager::timerOut()
{

    emit tick(currentTime());

}

void UAudioManager::seek(qint64 startTime)
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

qint64 UAudioManager::currentTime()
{
    unsigned int time;
    FMOD_Channel_GetPosition(
      _channel,
     &time,
      FMOD_TIMEUNIT_MS
    );

    return (qint64)time;
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
