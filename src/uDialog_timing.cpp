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

