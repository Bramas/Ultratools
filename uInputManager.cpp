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
    qDebug()<<"keyPress "<<event;
    if(event->isAutoRepeat()) return;

       _keyPressed.push_front(event->key());
       emit keyPressEvent(event);

       if(event->key()==Qt::Key_Space) emit spacePressEvent();
};
