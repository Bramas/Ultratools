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

#ifndef UWYDGET_TIMELINE_H
#define UWYDGET_TIMELINE_H

#include "uDialog_fileheader.h"

class ShowSentenceWidget;
class UEditorWindow;
class UWydget_Timeline : public QWidget
{
    Q_OBJECT

signals:

    void gapModified(double);
    void click(quint64);

public:
    UWydget_Timeline(UEditorWindow * parent);
    void setMin(int in) { min = in; update(); }
    void setMax(int in) { max = in; update(); }
    void setBpm(int n) { _bpm = n; }
    void setGap(int n) { _lastGap = _gap = n; }
    void setWidgetSentence(ShowSentenceWidget* showSentenceWidget);

public slots:
    void setSeekPosition(quint64 seek);

    void setSeek(quint64 time);
    bool isGapLocked() { return _gapLocked; };
protected:
    int min, max;
    double _bpm;
    double _gap;
    quint64 _seek;
     void paintEvent(QPaintEvent * event);
     void mousePressEvent(QMouseEvent * event);
     void mouseReleaseEvent(QMouseEvent * event);
     void mouseMoveEvent(QMouseEvent * event);
     bool _gapSelected, _gapOver, _seekSelected, _seekOver, _gapLocked;
     ShowSentenceWidget* _showSentenceWidget;
     double _lastGap;
     UEditorWindow * _parent;

};

#endif // UEDITOR_TIMELINE_H
