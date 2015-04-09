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

#ifndef UAUDIOMANAGER_H
#define UAUDIOMANAGER_H

#include "uWydget_lyrics.h"

#include "inc/fmod.h"
#include "inc/fmod_errors.h"
class WidgetSongData;

class UAudioManager : public QObject
{
    Q_OBJECT

signals:

    void tick(quint64);
    void endOfSong();

public slots:

    void play();
    void pause();
    void seek(quint64 startTime);
    void timerOut();
    void changeVolume(int);
    void emitEndOfSong() { emit endOfSong(); }

public:
    void init();
    bool setSource(QString);
    quint64 currentTime();
    void setWidgetSongData(WidgetSongData * widgetSongData) { _widgetSongData = widgetSongData; }
    void lol();
    FMOD_SYSTEM * getSystem() { return _system; }

protected:
    QTimer * _tickTimer;
    bool _initialised;
    FMOD_RESULT _result;
    FMOD_SYSTEM *_system;
    QString _source;
    FMOD_SOUND *_sound;
    FMOD_CHANNEL *_channel;

public:
    static UAudioManager Instance;
private:

    UAudioManager();
    WidgetSongData * _widgetSongData;
};

#endif // UAUDIOMANAGER_H
