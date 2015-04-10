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

#include <math.h>
#include <QKeyEvent>

#include "uRecorder.h"
#include "uShowSentenceWydget.h"
#include "editorwindow.h"

Recorder::Recorder(ShowSentenceWidget * showSentenceWidget)
{
    _beat=0;
    _currentWord = NULL;
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
    _beat = _showSentenceWidget->currentBeat();
    _currentWord = new Word(NULL,_beat,1,0);
    _currentWord->setText("");

}
void Recorder::onKeyReleaseEvent(QKeyEvent * /*event*/)
{
    if(!_currentWord) return;

   // if(UInputManager::Instance.isKeyPressed(Qt::Key_Space))// QMessageBox::warning(NULL,"","lol");

    _beat = _showSentenceWidget->currentBeat();

    if(_beat - _currentWord->getTime()>1)
        _currentWord->setLength(_beat - _currentWord->getTime());

    _showSentenceWidget->getLyrics()->addWord(_currentWord);
    _currentWord = NULL;


}

void Recorder::start()
{
    _isRecording = true;
}
void Recorder::stop()
{
    _isRecording = false;
}

