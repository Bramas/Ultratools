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



#ifndef USPACENOTEGENERATOR_H
#define USPACENOTEGENERATOR_H

#include <QtCore>
#include "uWord.h"
class ShowSentenceWidget;
class QKeyEvent;

class Recorder : public QObject
{
    Q_OBJECT

public:
    Recorder(ShowSentenceWidget * showSentenceWidget);
    bool isRecording() { return _isRecording; }
public slots:
    void onKeyPressEvent(QKeyEvent * event, ulong time);
    void onKeyReleaseEvent(QKeyEvent * event, ulong time);
    void startNote(ulong time, int pitch);
    void stopNote(ulong time, int pitch);
    void start();
    void stop();

protected:
    int getBeat(ulong);

private:

    Word _currentWord;
    ShowSentenceWidget * _showSentenceWidget;
    quint64 _currentTime;
    bool _isRecording;
};

#endif // USPACENOTEGENERATOR_H
