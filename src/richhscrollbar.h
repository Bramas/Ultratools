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
    void setMaximum(int m);
    void setPageStep(int p);
    void setLyrics(Lyrics * l) { _lyrics = l; }
signals:
    void pageStepChanged(int);

public slots:
    void setValue(int v);

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void leaveEvent(QEvent * e) { _overType = OverNothing; update(); QAbstractSlider::leaveEvent(e); }
    void enterEvent(QEvent * e) { _overType = OverNothing; update(); QAbstractSlider::enterEvent(e); }

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
};

#endif // RICHHSCROLLBAR_H
