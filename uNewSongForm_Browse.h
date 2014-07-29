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





#ifndef UNEWSONGFORM_BROWSE_H
#define UNEWSONGFORM_BROWSE_H

#include <QDialog>
class UFile;

namespace Ui {
    class UNewSongForm_Browse;
}

class UNewSongForm_Browse : public QDialog {
    Q_OBJECT
public:
    UNewSongForm_Browse(QWidget *parent = 0, UFile * file=0);
    ~UNewSongForm_Browse();

public slots:

    void updateFolder(QString s="");
    void edited(QString s=""){ _edited = true; }
    void browse(void);
    void browseMp3(void);
    void goNext(void);

protected:
    void changeEvent(QEvent *e);

    QString _baseLocation;
    bool _edited;
    UFile * _file;

private:
    Ui::UNewSongForm_Browse *ui;
};

#endif // UNEWSONGFORM_BROWSE_H
