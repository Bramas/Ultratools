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

#include "uNoteManager.h"

class USpaceNoteGenerator : public QObject
{
    Q_OBJECT

public slots:
    void tick(qint64);
    void spacePressEvent(void);
    void spaceReleaseEvent(void);

public:
    USpaceNoteGenerator(UFile * file);

    QList<Word*> result(void);

    void generateLyrics(QString text,Lyrics * lyrics);

private:

    int adaptGap();
    Word * _currentWord;
    int _beat;
    UFile * _file;
    quint64 _currentTime;
    QList<Word*> _words;

};

#endif // USPACENOTEGENERATOR_H
