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

#ifndef SHOWLINES_H
#define SHOWLINES_H

#include <QWidget>

#include "uInputManager.h"

class QPainter;
class ShowLines : public QWidget
{
    Q_OBJECT

public:
    ShowLines();
    void setMin(double);
    void setMax(double);

public slots:
    void setOctaveOffset(int o) { if(o != _octaveOffset) { _octaveOffset = o; update(); }}

protected:
    double min, max;
     void paintEvent(QPaintEvent * event);
     void drawPianoNote(QPainter * painter, qreal y, int n);
     int _octaveOffset;
};

#endif // SHOWLINES_H
