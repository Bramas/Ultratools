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



#include <QApplication>
#include <QTranslator>
#include <QMessageBox>

#include "editorwindow.h"
#include "timebase.h"
#include "uMidiManager.h"
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
#ifdef USE_MIDI
    UMidiManager::getInstance();
#endif
    manageLang(a);

    UEditorWindow w;
    w.show();


    return a.exec();
}
