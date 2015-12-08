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
