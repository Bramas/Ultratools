#ifndef RICHHSCROLLBAR_H
#define RICHHSCROLLBAR_H

#include <QAbstractSlider>
#include <QMouseEvent>
#include <QPoint>

class QPaintEvent;
class QMouseEvent;

class RichHScrollBar : public QAbstractSlider
{
    Q_OBJECT
public:
    explicit RichHScrollBar(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    bool _mousePressed;
    QPoint _mousePressPoint;
    int _mousePressSliderValue;
};

#endif // RICHHSCROLLBAR_H
