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



#include "timebase.h"
#include "uInputManager.h"
#include <QKeyEvent>
#include <QDebug>


UInputManager UInputManager::Instance;
static unsigned long guiDelta = 0;

static void updateGuiDelta(QInputEvent *event)
{
    unsigned long time = now();
    unsigned long delta = time - event->timestamp();

    if (!guiDelta || guiDelta > delta || delta - guiDelta > 10000)
        guiDelta = delta;
}


void UInputManager::keyReleased(QKeyEvent *event)
{
    updateGuiDelta(event);

    if(event->isAutoRepeat()) return;

    //QMessageBox::warning(NULL,"","lache");
    _keyPressed.removeOne(event->key());
    emit keyReleaseEvent(event, guiDelta + event->timestamp());

    if(event->key()==Qt::Key_Space) emit spaceReleaseEvent();
};

void UInputManager::keyPressed(QKeyEvent *event)
{
    updateGuiDelta(event);

    if(event->isAutoRepeat()) return;

       _keyPressed.push_front(event->key());
       emit keyPressEvent(event, guiDelta + event->timestamp());

       if(event->key()==Qt::Key_Space) emit spacePressEvent();
};
