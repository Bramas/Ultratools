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


#ifndef UINPUTMANAGER_H
#define UINPUTMANAGER_H


#include "uLyrics.h"

class UInputManager : public QObject
{

    Q_OBJECT

signals:

    void  keyPressEvent(QKeyEvent *);
    void  keyReleaseEvent(QKeyEvent *);


    void  spacePressEvent(void);
    void spaceReleaseEvent(void);

public:

    bool isKeyPressed(int key) { return _keyPressed.contains(key); };



    void keyPressed(QKeyEvent *event);
    void keyReleased(QKeyEvent *event);

    static UInputManager Instance;

protected:



   private:
   UInputManager() { };

   QList<int> _keyPressed;

};

/*
class UInputManager
{

   public:

    void keyPressed(QKeyEvent *event) { _keyPressed.push_front(event->key()); };
    void keyReleased(QKeyEvent *event) { _keyPressed.removeOne(event->key()); };

    bool isKeyPressed(int key) { return _keyPressed.contains(key); };


        UInputManager();
   private:

        QList<int> _keyPressed;

};

*/
#endif // UINPUTMANAGER_H
