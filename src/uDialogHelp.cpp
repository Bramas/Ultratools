/* Copyright (c) 2015 Quentin Bramas
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
