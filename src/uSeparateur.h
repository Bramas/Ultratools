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

#ifndef USEPARATEUR_H
#define USEPARATEUR_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QTranslator>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
 #include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QtGlobal>
#include <QSlider>
#include <cmath>
#include <QScrollBar>
 #include <QFileDialog>
#include <QDialog>
 #include <QLineEdit>
#include <QHBoxLayout>
 #include <QSpacerItem>
#include <QSettings>
#include <QScrollArea>
#include <QObject>
#include <QDesktopServices>


class USeparator
{
public:
    USeparateur(int time, int length) : UAbstractLine(TYPE_SEPARATOR) { _oTime = _time = time; _oLength = _length = length; }

    int getTime(void) const  { return getTime1(); }
    int getTime1(void) const { return _time; }
    int getTime2(void) { return _time + _length; }
    int getLength(void) { return _length; }


    void setTime(int in , bool definitly = true) { _time = in; if(definitly) { _oTime = _time; } }
    void setLength(int in , bool definitly = true) { _length = in; if(definitly) { _oLength = _length; } }

    void hold(void) { _oTime = _time; _oLength = _length; }

    quint8 getOver(void) { return _over; }
    void setOver(quint8 i) { _over = i; }

    int getOTime(void) { return _oTime; };
    int getOLength(void) { return _oLength; };


    Sentence * getRightSentence(void) { return _rightSentence; }
    Sentence * getLeftSentence(void) { return _leftSentence; }
    void setRightSentence(Sentence * in) { _rightSentence = in; }
    void  setLeftSentence(Sentence * in) { _leftSentence = in; }

private:

    Sentence * _rightSentence;
    Sentence * _leftSentence;

    quint8 _over;
    int _time;
    int _length;
    int _oTime;
    int _oLength;
};

#endif // USEPARATEUR_H
