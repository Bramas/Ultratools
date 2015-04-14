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
