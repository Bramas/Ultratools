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



#include "uDialog_timing.h"
#include "ui_uDialog_timing.h"

UDialog_timing::UDialog_timing(QWidget *parent, UFile * file) :
    QDialog(parent),
    ui(new Ui::uDialog_timing)
{
    ui->setupUi(this);
    _file=file;

    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(valueChanged()));
}

UDialog_timing::~UDialog_timing()
{
    delete ui;
}

void UDialog_timing::changeEvent(QEvent *e)
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

void UDialog_timing::accept()
{
    _file->lyrics->setDelay(ui->spinBox->value());
    this->close();
}

void UDialog_timing::valueChanged()
{
    quint64 time = _file->lyrics->beatToMsc(abs(ui->spinBox->value())) - _file->lyrics->getGap() ;
    ui->lineEdit->setText(QString(ui->spinBox->value() < 0 ? "-" : "")+QString::number(time));
}

