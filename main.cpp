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


#include <QtGui/QApplication>

#include "editorwindow.h"
#include <QCleanlooksStyle>
#include <QInputDialog>

void setLang(QApplication& app, const QString& idl){
        qWarning(QString("Lang is %1 (lang_%1)").arg(idl).toLatin1());

        QTranslator* translator = new QTranslator();
        translator->load("UltraTools_Editor_" + idl,":/lang");
        app.installTranslator(translator);
}


void manageLang(QApplication& app){
        QSettings settings("Ultratools", "Editor");
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


void donate(){
        QSettings settings("Ultratools", "Editor");
        bool showDonate = settings.value("donate", true).toBool();
        if( showDonate ){
                QMessageBox msgDonate;
                msgDonate.setText(QApplication::tr("<html>Ce logiciel est gratuit, mais il a fallut du temps pour le développer. "
                                                  "Pour laisser ce logiciel gratuit et mis à jour, merci de faire un don paypal : <a href=\"http://ultratools.org\">http://ultratools.org</a></html>"));
                msgDonate.setInformativeText(QApplication::tr("Will you donate?"));
                QPushButton* already = msgDonate.addButton(QApplication::tr("I already have"),QMessageBox::YesRole);
                QPushButton* will = msgDonate.addButton(QApplication::tr("I will, ask me later"),QMessageBox::YesRole);
                QPushButton* donot = msgDonate.addButton(QApplication::tr("I don't want"),QMessageBox::NoRole);

                msgDonate.setDefaultButton(will);
                msgDonate.exec();

                if(msgDonate.clickedButton() == (QAbstractButton*) already){
                        settings.setValue("donate", false);
                }
                else if(msgDonate.clickedButton() == (QAbstractButton*) donot){
                      //  QMessageBox::information(0, QApplication::tr("It is your choice"), QApplication::tr("Free Softwares exist thanks to donation.\n"
                       //                                                                         "In the futur, if you are using Picmiz a lot, please change your opinion and donate."));
                        settings.setValue("donate", false);
                }
        }
}




int main(int argc, char *argv[])
{


    QApplication a(argc, argv);


    a.setStyle(new QCleanlooksStyle );

    manageLang(a);
    donate();

    UEditorWindow w;
    w.show();


    return a.exec();
}
