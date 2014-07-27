#include "uDialogFeedback.h"
#include "ui_uDialogFeedback.h"

UDialogFeedback::UDialogFeedback(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDialogFeedback)
{
    ui->setupUi(this);
}

UDialogFeedback::~UDialogFeedback()
{
    delete ui;
}
