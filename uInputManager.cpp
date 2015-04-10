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



#include "uInputManager.h"
#include <QKeyEvent>
#include <QDebug>


UInputManager UInputManager::Instance;


void UInputManager::keyReleased(QKeyEvent *event)
{

    if(event->isAutoRepeat()) return;

    //QMessageBox::warning(NULL,"","lache");
    _keyPressed.removeOne(event->key());
    emit keyReleaseEvent(event);

    if(event->key()==Qt::Key_Space) emit spaceReleaseEvent();
};

void UInputManager::keyPressed(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;

       _keyPressed.push_front(event->key());
       emit keyPressEvent(event);

       if(event->key()==Qt::Key_Space) emit spacePressEvent();
};
