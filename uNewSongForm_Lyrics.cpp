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



#include "uNewSongForm_Lyrics.h"
#include "ui_uNewSongForm_Lyrics.h"

UNewSongForm_Lyrics::UNewSongForm_Lyrics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UNewSongForm_Lyrics)
{
    ui->setupUi(this);
    connect(ui->commandLinkButton,SIGNAL(clicked()),this,SLOT(close()));
}

UNewSongForm_Lyrics::~UNewSongForm_Lyrics()
{
    delete ui;
}

QString UNewSongForm_Lyrics::getText()
{

     return ui->plainTextEdit->toPlainText();
}

void UNewSongForm_Lyrics::changeEvent(QEvent *e)
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
