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




#include "UNewSongForm_Browse.h"
#include "ui_UNewSongForm_Browse.h"

UNewSongForm_Browse::UNewSongForm_Browse(QWidget *parent,UFile * file) :
    QDialog(parent),
    ui(new Ui::UNewSongForm_Browse)
{
    ui->setupUi(this);

    _file = file;

    _baseLocation = USetting::Instance.getSongsLocation();
    ui->lineEdit_folder->setText(USetting::Instance.getSongsLocation());

    _edited=false;

    connect(ui->pushButton_browse,SIGNAL(clicked()),this,SLOT(browse()));
    connect(ui->pushButton_browseMp3,SIGNAL(clicked()),this,SLOT(browseMp3()));


    connect(ui->checkBox_withVideo,SIGNAL(clicked()),this,SLOT(updateFolder()));
    connect(ui->lineEdit_title,SIGNAL(textChanged(QString)),this,SLOT(updateFolder(QString)));
    connect(ui->lineEdit_artist,SIGNAL(textChanged(QString)),this,SLOT(updateFolder(QString)));
    connect(ui->lineEdit_folder,SIGNAL(textEdited(QString)),this,SLOT(edited(QString)));

    connect(ui->commandNext,SIGNAL(clicked()),this,SLOT(goNext()));

}

UNewSongForm_Browse::~UNewSongForm_Browse()
{
    delete ui;
}

void UNewSongForm_Browse::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UNewSongForm_Browse::browse(void)
{
    _baseLocation = QFileDialog::getExistingDirectory(this,"Dossier de création",USetting::Instance.getSongsLocation());
    ui->lineEdit_folder->setText(_baseLocation);
    _edited = false;

    updateFolder();
}
void UNewSongForm_Browse::browseMp3(void)
{
    QString mp3Location = QFileDialog::getOpenFileName(this,tr("Le fichier mp3"),USetting::Instance.getSongsLocation(),"Musique ( *.mp3 )");
    ui->lineEdit_mp3->setText(mp3Location);

}

void UNewSongForm_Browse::updateFolder(QString no)
{
    if(_edited) return;


    QString s = ui->lineEdit_artist->text();

    if(s.compare(""))
    {
        if(ui->lineEdit_title->text().compare(""))
        {
            s.append(" - "+ui->lineEdit_title->text());
        }
    }else
    {
        s = ui->lineEdit_title->text();
    }

    if(ui->checkBox_withVideo->isChecked())
    {
        s.append(" [VIDEO]");
    }

    ui->lineEdit_folder->setText( _baseLocation + "/" + s );
}

void UNewSongForm_Browse::goNext()
{
    _file->_headArtist = ui->lineEdit_artist->text();
    _file->_headTitle = ui->lineEdit_title->text();

    _file->_headMp3 = ui->lineEdit_folder->text().section('/',-1,-1) + ".mp3";
    _file->setFileName(ui->lineEdit_folder->text()+"/"+ui->lineEdit_folder->text().section('/',-1,-1) + ".txt");

    QDir dir;
    dir.mkpath(ui->lineEdit_folder->text()+"/");

    QFile::copy(ui->lineEdit_mp3->text(),(ui->lineEdit_folder->text()+"/"+ui->lineEdit_folder->text().section('/',-1,-1) + ".mp3"));


    _file->saveInFile();

    this->close();
}
