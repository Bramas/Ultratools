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

#include <cmath>
#include <QKeyEvent>

#include "uRecorder.h"
#include "uShowSentenceWydget.h"
#include "editorwindow.h"

Recorder::Recorder(ShowSentenceWidget * showSentenceWidget)
{
    _isRecording = false;
    _showSentenceWidget = showSentenceWidget;

    connect(&UInputManager::Instance,SIGNAL(keyPressEvent(QKeyEvent *)),this,SLOT(onKeyPressEvent(QKeyEvent *)));
    connect(&UInputManager::Instance,SIGNAL(keyReleaseEvent(QKeyEvent *)),this,SLOT(onKeyReleaseEvent(QKeyEvent *)));
}

void Recorder::onKeyPressEvent(QKeyEvent * event)
{
    if(!_isRecording || event->key() == Qt::Key_Space)
    {
        return;
    }
    int beat = _showSentenceWidget->currentBeat();
    _currentWord = Word(NULL,beat,1,0);
    _currentWord.setText("");

}
void Recorder::onKeyReleaseEvent(QKeyEvent * /*event*/)
{
    if(_currentWord.getText().isNull()) return;

   // if(UInputManager::Instance.isKeyPressed(Qt::Key_Space))// QMessageBox::warning(NULL,"","lol");

    int beat = _showSentenceWidget->currentBeat();

    if(beat - _currentWord.getTime()>1)
        _currentWord.setLength(beat - _currentWord.getTime());

    _showSentenceWidget->getLyrics()->addWord(_currentWord);
    _currentWord = Word();


}

void Recorder::start()
{
    _isRecording = true;
}
void Recorder::stop()
{
    _isRecording = false;
}

