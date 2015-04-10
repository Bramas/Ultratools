#include "uDialogAbout.h"
#include "ui_uDialogAbout.h"
#include "inc/fmod.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    this->setWindowTitle(trUtf8("About"));
    this->ui->textBrowser->setOpenExternalLinks(true);
    this->ui->textBrowser->setText(
                "<center><strong>Ultratools Editor " VERSION "</strong><br/>"
                "<a target='_blank' href='http://www.ultratools.org'>www.ultratools.org</a><br/>"
                "<strong>Author: Quentin BRAMAS<strong></center><br/>"
                "licence: GPLv3<br/>"
                "build with:<br/>"
                " - Qt " QT_VERSION_STR "<br/>"
                " - FMOD "+QString::number(FMOD_VERSION>>16)+"."+QString::number(0xFF & (FMOD_VERSION>>8))+"."+QString::number(0xFF & (FMOD_VERSION)));
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
