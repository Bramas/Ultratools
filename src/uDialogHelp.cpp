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

#include "uDialogHelp.h"
#include "ui_uDialogHelp.h"
#include <QPainter>
#include <QPixmap>
UDialogHelp::UDialogHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDialogHelp)
{
    ui->setupUi(this);

this->setGeometry(10,50,900,485);

   /* QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(tr("images/Help.fr.jpg"))));

    this->setPalette(palette);
*/
    update();
}

UDialogHelp::~UDialogHelp()
{
    delete ui;
}

void UDialogHelp::changeEvent(QEvent *e)
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
void UDialogHelp::paintEvent(QPaintEvent * /*event*/)
{
    QPainter * painter = new QPainter(this);
    //painter->drawImage(QRect(0,0,800,600),QImage::QImage(tr("images/Help.fr.jpg")));
   // painter->drawImage(QPoint(0,0),QImage::QImage(tr("images/Help.fr.jpg")));
    painter->drawImage(QPoint(0,0),QImage(tr(":/Images/images/Help.fr.jpg")));
}
