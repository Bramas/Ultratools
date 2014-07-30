/****************************************************************************
**
** Author & Contact: Quentin BRAMAS ( contact@bramas.fr )
**
** This file is part of Ultratools.
**
** GNU General Public License Usage
** ExUlt is free software: you can redistribute it and/or modify it under the
** terms of General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** ExUlt is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** If you have questions regarding the use of this file, please contact
** Quentin BRAMAS (contact@bramas.fr).
**
****************************************************************************/


#ifndef UWYDGET_LYRICS_H
#define UWYDGET_LYRICS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPlainTextEdit>

class ShowSentenceWidget;
class Word;

#include "uWydget_timeline.h"

class UWydget_Lyrics : public QPlainTextEdit
{
    Q_OBJECT

public slots:

    void onKeyPress(QKeyEvent * e);
    void updateChange();
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

    int _cursorPosition;
    void saveChange();

    int _maxHeight;
    ShowSentenceWidget * _wydgetWords;
    QString _brutText;
    int _fontSize;
    int _fontSizeEdit;
    bool _isEditing;
    int _selectedTextFirstIndex, _selectedTextLastIndex;

};

#endif // UWYDGET_LYRICS_H
