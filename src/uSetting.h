/* Copyright (c) 2015 Quentin Bramas
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */



#ifndef USETTING_H
#define USETTING_H

#include <QSettings>
#include <QStringList>
#include "uSettingDialog.h"

class USetting : public QObject
{

    Q_OBJECT

public slots:

    void showDialog(void);
public:
    static USetting Instance;

    void addOpenFile(QString fileName);
    QStringList lastOpenFiles() const;
    QString getSoftId(void);
    QString getUltrastarLocation(void);
    QString getSongsLocation(void);
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
