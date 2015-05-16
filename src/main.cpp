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



#include <QApplication>
#include <QTranslator>
#include <QMessageBox>

#include "editorwindow.h"
#include "timebase.h"
#include <QInputDialog>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

void setLang(QApplication& app, const QString& idl){
        qDebug("Lang is %s", idl.toLatin1().data());

        QTranslator* translator = new QTranslator();
        translator->load("UltraTools_Editor_" + idl,":/lang");
        app.installTranslator(translator);
}


void manageLang(QApplication& app){
        QSettings settings;
        int lang = settings.value("lang", -1).toInt();
        if( lang == -1){
                QStringList languages;
                languages << "English" << "Francais" << "Spanish(not finished)";
                lang = languages.indexOf(QInputDialog::getItem(0, "Preference", "Choose your language ?", languages, 0, false));
                if(lang == -1){
                        lang = 0;
                }
                settings.setValue("lang", lang);
        }

        switch(lang){
                case 0:
                        setLang(app,"en");
                        break;
                case 1:
                        setLang(app,"fr");
                        break;
                case 2:
                                setLang(app,"en");
                                break;
        }
}


int main(int argc, char *argv[])
{

#ifdef __APPLE__
     QDir dir(QFileInfo(argv[0]).path());  // e.g. appdir/Contents/MacOS
     dir.cdUp();
     if(dir.cd("PlugIns"))// e.g. appdir/Contents/PlugIns
     {
        QApplication::setLibraryPaths( QStringList(dir.absolutePath()));
     }
     else
     {
         qDebug()<<"not deployed";
     }
#endif
#ifdef _WIN32
     QDir dir(QFileInfo(argv[0]).path());  // e.g. appdir/Contents/MacOS
     if(dir.cd("plugins"))// e.g. appdir/plugins
     {
        QApplication::setLibraryPaths( QStringList(dir.absolutePath()));
     }
     else
     {
         qDebug()<<"not deployed";
     }
#endif

    QApplication a(argc, argv);
    a.setOrganizationName("Ultratools");
    a.setOrganizationDomain("ultratools.org");
    a.setApplicationName("Editor");
    qDebug()<<"Ultratools Editor " VERSION;

    initializeTimebase();
    manageLang(a);

    UEditorWindow w;
    w.show();


    return a.exec();
}
