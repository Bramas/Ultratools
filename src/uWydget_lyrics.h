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

#ifndef UWYDGET_LYRICS_H
#define UWYDGET_LYRICS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPlainTextEdit>

class ShowSentenceWidget;

#include "uWydget_timeline.h"

class UWydget_Lyrics : public QPlainTextEdit
{
    Q_OBJECT

public slots:

    void onKeyPress(QKeyEvent * e);
    void updateChange();
    void queueUpdate();
    void onScroll();
    void ondoubleClick(int s);
    void separeOnSelect(void);
    void cursorPositionChanged(int,int);
    void onSelectionChange(int,int);
    void onTextChanged();

public:
    UWydget_Lyrics();

    void setWidgetWords(ShowSentenceWidget* wydgetWords);
protected:

    void insertFromMimeData(const QMimeData * source);
    void keyPressEvent(QKeyEvent * e);
    virtual void timerEvent(QTimerEvent * event);

    int _cursorPosition;
    void saveChange();

    int _maxHeight;
    ShowSentenceWidget * _wydgetWords;
    QString _brutText;
    int _fontSize;
    int _fontSizeEdit;
    bool _isEditing;
    int _selectedTextFirstIndex, _selectedTextLastIndex;
    int _updateTimer;

};

#endif // UWYDGET_LYRICS_H
