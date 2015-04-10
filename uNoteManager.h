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
    FMOD_CHANNELGROUP * _notesGroup;
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
