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

