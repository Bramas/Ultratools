/* Copyright (c) 2015 Quentin Bramas
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef UINPUTMANAGER_H
#define UINPUTMANAGER_H


#include "uLyrics.h"

class UInputManager : public QObject
{

    Q_OBJECT

signals:

    void  keyPressEvent(QKeyEvent *, ulong);
    void  keyReleaseEvent(QKeyEvent *, ulong);


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
