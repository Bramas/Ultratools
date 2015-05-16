/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Quentin Bramas <quentin@bramas.fr> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Quentin Bramas
 *
 * "LICENCE BEERWARE" (Révision 42):
 * Quentin Bramas <quentin@bramas.fr> a créé ce fichier. Tant que vous conservez cet avertissement,
 * vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
 * que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
 * retour. Quentin Bramas
 * ----------------------------------------------------------------------------
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
    unsigned long _granularity;
    unsigned long _delta;
};

#endif // UAUDIOMANAGER_H
