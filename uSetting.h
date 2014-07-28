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




#ifndef USETTING_H
#define USETTING_H

#include <QSettings>
#include "USettingDialog.h"

class USetting : public QObject
{

    Q_OBJECT

public slots:

    void showDialog(void);
public:
    static USetting Instance;

    QString getSoftId(void);
    QString getUltrastarLocation(void);
    QString getSongsLocation(void){ return getUltrastarLocation() + "/Songs"; }
    int getAutoSaveInterval(void);
    bool isRestartAfterStop(void) { return true;  }

    QString getWindowTitle(QString win,QString add) {
        if(!_windowEditorTitleSet)
        {
            _windowEditorTitle = win;
            _windowEditorTitleSet=true;
        }
        return _windowEditorTitle+add; }
    void setWindowTitle(QString w) { _windowEditorTitle = w; }

    void init(void);


private:

bool _windowEditorTitleSet;
QString _windowEditorTitle;
QSettings *_settings;

USetting();
};

#endif // USETTING_H
