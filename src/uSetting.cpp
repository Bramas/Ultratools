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


#include "uSetting.h"
#include <QUuid>
#include <QFileDialog>

USetting USetting::Instance;

USetting::USetting()
{

}
void USetting::init()
{

_windowEditorTitleSet = false;
     _settings = new QSettings();

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

QString USetting::getSongsLocation()
{
    QDir d(getUltrastarLocation());
    d.cd("Songs"); //if it doesnt exist, stay at the same directory
    return d.absolutePath();
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
    return _settings->value("softId","").toString();
}
QStringList USetting::lastOpenFiles() const
{
    return _settings->value("lastOpenFiles").toStringList();
}
void USetting::addOpenFile(QString filename)
{
    QStringList l = _settings->value("lastOpenFiles").toStringList();
    l.removeAll(filename);
    l.push_front(filename);
    _settings->setValue("lastOpenFiles", l);
}






