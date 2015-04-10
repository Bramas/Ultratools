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
    float _bpm;
    float _gap;
    quint64 _seek;
     void paintEvent(QPaintEvent * event);
     void mousePressEvent(QMouseEvent * event);
     void mouseReleaseEvent(QMouseEvent * event);
     void mouseMoveEvent(QMouseEvent * event);
     bool _gapSelected, _gapOver, _seekSelected, _seekOver, _gapLocked;
     ShowSentenceWidget* _showSentenceWidget;
     float _lastGap;
     UEditorWindow * _parent;

};

#endif // UEDITOR_TIMELINE_H
