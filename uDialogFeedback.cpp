#include "uDialogFeedback.h"
#include "ui_uDialogFeedback.h"
#include <QPushButton>

UDialogFeedback::UDialogFeedback(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDialogFeedback)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(trUtf8("Envoyer"));
}

UDialogFeedback::~UDialogFeedback()
{
    delete ui;
}
