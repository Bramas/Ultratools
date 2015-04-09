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
    void onFloatSelection(float, float);

protected:
    void paintEvent(QPaintEvent*);
    void wheelEvent(QWheelEvent *);
private:
    QVector<qreal> _leftData;
    QVector<qreal> _rightData;
    QPolygonF _dataPoly, _dataPoly2;
    ShowSentenceWidget* _showSentenceWidget;
    float _floatSelection[2];
    float _max;
    float _scaleX;
    int _translateX;
    int _hScroll;
    int _hScale;
    quint64 _seek;
};

#endif // UWIDGETSONGDATA_H
