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

