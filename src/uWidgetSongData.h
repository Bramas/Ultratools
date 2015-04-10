/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Quentin Bramas <quentin@bramas.fr> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Quentin Bramas
 *
 * "LICENCE BEERWARE" (Révision 42):
 * Quentin Bramas <quentin@bramas.fr> a créé ce fichier. Tant que vous conservez cet avertissement,
 * vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
 * que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
 * retour. Quentin Bramas
 * ----------------------------------------------------------------------------
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
    void onFloatSelection(float, float);

protected:
    void paintEvent(QPaintEvent*);
private:
    QVector<qreal> _leftData;
    QVector<qreal> _rightData;
    QPolygonF _dataPoly, _dataPoly2;
    ShowSentenceWidget* _showSentenceWidget;
    float _floatSelection[2];
    float _max;
    int _hScroll;
    int _hScale;
    quint64 _seek;
};

#endif // UWIDGETSONGDATA_H
