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

#ifndef UMIDIMANAGER_H
#define UMIDIMANAGER_H

#include "uAudioManager.h"
#include "uWord.h"
class Lyrics;

class UNoteManager : public QObject
{
    Q_OBJECT

public slots:

    void tick(quint64 time);
    void play(void);
    void pause(void);
    void setVolume(int v);
    void changePitch(int);

public:
    void setMaxPitch(int in) { _maxPitch = in; }

    void play(const Word & w);

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
    int _pitchOffset;
    int pitchToNote(int note);
    Lyrics * _lyrics;

    FMOD_RESULT _result;
    FMOD_SYSTEM *_system;
    FMOD_CHANNELGROUP * _notesGroup;
    QString _source;



    QMap<int,FMOD_SOUND *> _sounds;

    QMap<int,FMOD_CHANNEL *> _channels;

    QList<Word> _played;


public:
    static UNoteManager Instance;
private:
   UNoteManager();
};

#endif // UMIDIMANAGER_H
