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



#include "uFile.h"
#include "uDialog_fileheader.h"
#include "ui_udialog_fileheader.h"

UDialog_fileHeader::UDialog_fileHeader(QWidget *parent,UFile * file) :
    QDialog(parent),
    ui(new Ui::UDialog_fileHeader)
{
    ui->setupUi(this);
    _file = file;

    ui->lineEdit_artist->setText(_file->_headArtist);
    ui->lineEdit_author->setText(_file->_headAuthor);
    ui->lineEdit_background->setText(_file->_headBackground);
    ui->lineEdit_bmp->setText(QString::number(_file->getBpm()));
    ui->lineEdit_cover->setText(_file->_headCover);
    ui->lineEdit_gap->setText(QString::number(_file->_headGap));
    ui->lineEdit_mp3->setText(_file->_headMp3);
    ui->lineEdit_title->setText(_file->_headTitle);
    ui->lineEdit_video->setText(_file->_headVideo);
    ui->lineEdit_year->setText(_file->_headYear);
    ui->lineEdit_edition->setText(_file->_headEdition);
    ui->lineEdit_language->setText(_file->_headLanguage);
    ui->lineEdit_genre->setText(_file->_headGenre);
    ui->lineEdit_videogap->setText(QString::number(_file->_headVideogap));

}

UDialog_fileHeader::~UDialog_fileHeader()
{
    delete ui;
}

void UDialog_fileHeader::changeEvent(QEvent *e)
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

void UDialog_fileHeader::accept()
{

    _file->_headArtist = ui->lineEdit_artist->text();
    _file->_headAuthor = ui->lineEdit_author->text();
    _file->_headBackground = ui->lineEdit_background->text();
    _file->setBpm(ui->lineEdit_bmp->text().replace(',','.').toDouble());
    _file->setGap(ui->lineEdit_gap->text().replace(',','.').toDouble());


    _file->_headCover = ui->lineEdit_cover->text();
    _file->_headMp3 = ui->lineEdit_mp3->text();
    _file->_headTitle = ui->lineEdit_title->text();
    _file->_headVideo = ui->lineEdit_video->text();
    _file->_headVideogap = ui->lineEdit_videogap->text().replace(',','.').toDouble();
    _file->_headYear = ui->lineEdit_year->text();
    _file->_headEdition =  ui->lineEdit_edition->text();
    _file->_headLanguage = ui->lineEdit_language->text();
    _file->_headGenre = ui->lineEdit_genre->text();

    this->close();
}
