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


#ifndef RICHHSCROLLBAR_H
#define RICHHSCROLLBAR_H

#include <QAbstractSlider>
#include <QMouseEvent>
#include <QPoint>

class QPaintEvent;
class QMouseEvent;
class Lyrics;
class QEvent;
class RichHScrollBar : public QAbstractSlider
{
    Q_OBJECT
public:
    explicit RichHScrollBar(QWidget *parent = 0);
    void setTotalMaximum(int m);
    void setViewport(int v, int p);
    void changePageStep(int p);
    void setLyrics(Lyrics * l) { _lyrics = l; }
    int total() const { return maximum() - minimum() + pageStep(); }
    int useableWidth() const { return width() - 2 * HBorder; }
signals:
    void pageStepChanged(int);

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void leaveEvent(QEvent * e) { _overType = OverNothing; update(); QAbstractSlider::leaveEvent(e); }
    void enterEvent(QEvent * e) { _overType = OverNothing; update(); QAbstractSlider::enterEvent(e); }
    void sliderChange(SliderChange change);

private:
    bool _mousePressed;
    QPoint _mousePressPoint;
    int _mousePressSliderValue;
    int _mousePressPageStep;

    void updateLeftRight();
    qreal _left, _right;
    Lyrics * _lyrics;
    int _overType;
    enum {OverNothing, OverLeft, OverRight, OverCenter, OverScaleCenter};

    static const int HBorder;
    static const int VBorder;
    static const int MinVisible;
};

#endif // RICHHSCROLLBAR_H
