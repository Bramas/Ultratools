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

#ifndef UWIDGETSONGDATA_H
#define UWIDGETSONGDATA_H

#include <QWidget>
#include <QPointF>
#include <QPolygonF>
class QWheelEvent;
class ShowSentenceWidget;

class WidgetSongData : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSongData(QWidget *parent = 0);

    void setWidgetSentence(ShowSentenceWidget* showSentenceWidget);
    void setHScroll(int s);
    void setHScale(int s);
    void addData(qreal leftData, qreal rightData);
    void clearData() { _leftData.clear(); _rightData.clear(); }
signals:

public slots:
    void setSeekPosition(quint64 seek);
    void onFloatSelection(double, double);

protected:
    void paintEvent(QPaintEvent*);
private:
    QVector<qreal> _leftData;
    QVector<qreal> _rightData;
    QPolygonF _dataPoly, _dataPoly2;
    ShowSentenceWidget* _showSentenceWidget;
    double _floatSelection[2];
    double _max;
    int _hScroll;
    int _hScale;
    quint64 _seek;
};

#endif // UWIDGETSONGDATA_H
