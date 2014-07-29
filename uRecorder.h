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




#ifndef USPACENOTEGENERATOR_H
#define USPACENOTEGENERATOR_H

#include <QtCore>
class ShowSentenceWidget;
class Word;
class QKeyEvent;

class Recorder : public QObject
{
    Q_OBJECT

public:
    Recorder(ShowSentenceWidget * showSentenceWidget);
    bool isRecording() { return _isRecording; }
public slots:
    void onKeyPressEvent(QKeyEvent * event);
    void onKeyReleaseEvent(QKeyEvent * event);
    void start();
    void stop();

private:

    Word * _currentWord;
    int _beat;
    ShowSentenceWidget * _showSentenceWidget;
    quint64 _currentTime;
    bool _isRecording;
};

#endif // USPACENOTEGENERATOR_H
