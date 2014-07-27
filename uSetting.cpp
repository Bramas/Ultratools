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




#include "uSetting.h"
#include "uCheckUpdate.h"
#include <QUuid>

USetting USetting::Instance;

USetting::USetting()
{

}
void USetting::init()
{

_windowEditorTitleSet = false;
     _settings = new QSettings("Ultratools", "Editor");

    _settings->beginGroup("USetting");


    if(!_settings->contains("UltrastarLocation"))
    {
        QString rep = QFileDialog::getExistingDirectory(NULL,QObject::tr("Choisir le dossier d'installation d'Ultrastar"),"c:/");
        _settings->setValue("UltrastarLocation",rep);
    }
    if(!_settings->contains("softId"))
    {
           QString id("Ed-");
           id.append(VERSION);
           id.append("-");
           QUuid r(QUuid::createUuid());

           QString rs=r.toString();
           int i = (int)rs[1].toLatin1();
           i+=(int)rs[6].toLatin1();
           i+=(int)rs[11].toLatin1();
           i+=(int)rs[12].toLatin1();
           i+=(int)rs[21].toLatin1();

           id.append(QString::number(i)+"-");
           id.append(rs);
        _settings->setValue("softId",id);
    }

}
QString USetting::getUltrastarLocation()
{
    return _settings->value("UltrastarLocation","/").toString();
}

void USetting::showDialog()
{
    USettingDialog d(this);

    if(d.exec() == QDialog::Rejected) return;


    _settings->setValue("UltrastarLocation",d.getUltrastarLocation());
    _settings->setValue("AutoSaveInterval",d.getAutoSaveInterval());

}

int USetting::getAutoSaveInterval(void)
{
    return _settings->value("AutoSaveInterval",2).toInt();
}
QString USetting::getSoftId(void)
{
    return _settings->value("softId").toString();
}





