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


#ifndef UMIDIMANAGER_H
#define UMIDIMANAGER_H

#include "uAudioManager.h"
class Lyrics;

class UNoteManager : public QObject
{
    Q_OBJECT

public slots:

    void tick(quint64 time);
    void play(void);
    void pause(void);
    void setVolume(int v);

public:
    void setMaxPitch(int in) { _maxPitch = in; }

    void play(Word * w);

    bool isPlaying() { return _isPlaying; }

    /*Phonon::AudioOutput * getOutput(void) {
        return _violonOutput;
    };
*/
    void setLyrics(Lyrics * l) { _lyrics = l; }
    //QList<Word*> * getWords(void) { return &_played; };

    void setupAudio(QObject * parent);

protected:

    QString violonFile(int i);
    bool checkPitch(int p);
    bool _isPlaying;
    int _maxPitch;
    int pitchToNote(int note);
    Lyrics * _lyrics;

    FMOD_RESULT _result;
    FMOD_SYSTEM *_system;
    QString _source;


    QMap<int,FMOD_SOUND *> _sounds;

    QMap<int,FMOD_CHANNEL *> _channels;

    QList<Word*> _played;


public:
    static UNoteManager Instance;
private:
   UNoteManager();
};

#endif // UMIDIMANAGER_H
