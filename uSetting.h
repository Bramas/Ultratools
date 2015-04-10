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
