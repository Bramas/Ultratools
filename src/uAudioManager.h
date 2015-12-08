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

#ifndef UAUDIOMANAGER_H
#define UAUDIOMANAGER_H

#include "uWydget_lyrics.h"


//hack to fix a known bug with FMOD and C++11
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#   define _stdcall __stdcall
#endif
#include <fmod.h>
#include <fmod_errors.h>


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
    void changeSpeed(double);
    void emitEndOfSong() { emit endOfSong(); }

public:
    void init();
    void clear();
    bool setSource(QString);
    quint64 currentTime();
    bool timestampToPosition(ulong &);
    void setWidgetSongData(WidgetSongData * widgetSongData) { _widgetSongData = widgetSongData; }
    void lol();
    FMOD_SYSTEM * getSystem() { return _system; }

    /*!
     * \brief length
     * \return return the length of the current sound in millisecond
     */
    quint32 length();

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
    unsigned int _lastPosition;
    unsigned int _granularity;
    qint64 _delta;
    double _speedFactor;
    float _frequency;
};

#endif // UAUDIOMANAGER_H
