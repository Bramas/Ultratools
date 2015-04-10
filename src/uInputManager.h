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
