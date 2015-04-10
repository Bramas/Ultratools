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
                "Built with:<br/>"
                " - Qt " QT_VERSION_STR " (License LGPLv3)<br/>"
                " - FMOD "+QString::number(FMOD_VERSION>>16)+"."+QString::number(0xFF & (FMOD_VERSION>>8))+"."+QString::number(0xFF & (FMOD_VERSION)) + " (License : Non-Commercial)");
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
