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






