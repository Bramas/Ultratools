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




#include "uSettingDialog.h"
#include "ui_uSettingDialog.h"

#include "uSetting.h"

USettingDialog::USettingDialog(USetting *parent) :
    QDialog(NULL),
    ui(new Ui::USettingDialog)
{
    ui->setupUi(this);


    connect(ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->pushButton_annuler,SIGNAL(clicked()),this,SLOT(reject()));


    ui->lineEdit_ultrastarLocation->setText(parent->getUltrastarLocation());
    ui->spinBox_autosave->setValue(parent->getAutoSaveInterval());

}

USettingDialog::~USettingDialog()
{
    delete ui;
}

void USettingDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString USettingDialog::getUltrastarLocation()
{
    return ui->lineEdit_ultrastarLocation->text();
}
int USettingDialog::getAutoSaveInterval()
{
     return ui->spinBox_autosave->value();
}
