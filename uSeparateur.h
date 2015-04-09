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

enum { TYPE_NOTE, TYPE_SEPARATOR };

class UAbstractLine
{
public:
    UAbstractLine(quint8 type){ _TYPE=type; };

    virtual int getTime() const = 0;
    quint8 getType(void) { return _TYPE; };


    static bool lessThan(const UAbstractLine * a,const UAbstractLine * b);

    quint8 _TYPE;

};



class Sentence;

class USeparateur : public UAbstractLine
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
