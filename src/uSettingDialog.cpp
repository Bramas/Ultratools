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
