/****************************************************************************
**
** Author & Contact: Quentin BRAMAS ( contact@bramas.fr )
**
** This file is part of Ultratools.
**
** GNU General Public License Usage
** ExUlt is free software: you can redistribute it and/or modify it under the
** terms of General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** ExUlt is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** If you have questions regarding the use of this file, please contact
** Quentin BRAMAS (contact@bramas.fr).
**
****************************************************************************/


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
    _file->setBpm(ui->lineEdit_bmp->text().replace(',','.').toFloat());
    _file->setGap(ui->lineEdit_gap->text().replace(',','.').toFloat());


    _file->_headCover = ui->lineEdit_cover->text();
    _file->_headMp3 = ui->lineEdit_mp3->text();
    _file->_headTitle = ui->lineEdit_title->text();
    _file->_headVideo = ui->lineEdit_video->text();
    _file->_headVideogap = ui->lineEdit_videogap->text().replace(',','.').toFloat();
    _file->_headYear = ui->lineEdit_year->text();
    _file->_headEdition =  ui->lineEdit_edition->text();
    _file->_headLanguage = ui->lineEdit_language->text();
    _file->_headGenre = ui->lineEdit_genre->text();

    this->close();
}
