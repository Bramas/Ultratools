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



#include <QFileDialog>
#include <QDir>
#include "uFile.h"
#include "uSetting.h"
#include "uNewSongForm_Browse.h"
#include "ui_uNewSongForm_Browse.h"

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
    _baseLocation = QFileDialog::getExistingDirectory(this,tr("Dossier de création"),USetting::Instance.getSongsLocation());
    ui->lineEdit_folder->setText(_baseLocation);
    _edited = false;

    updateFolder();
}
void UNewSongForm_Browse::browseMp3(void)
{
    QString mp3Location = QFileDialog::getOpenFileName(this,tr("Le fichier mp3"),USetting::Instance.getSongsLocation(),
                                                       tr("MP3") + " ( *.mp3 );;" + tr("Toutes fiches") + " ( *.* )");
    ui->lineEdit_mp3->setText(mp3Location);

}

void UNewSongForm_Browse::updateFolder(QString /*no*/)
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

    QString ext = ui->lineEdit_mp3->text().section('.',-1,-1);
    _file->_headMp3 = ui->lineEdit_folder->text().section('/',-1,-1) + "." + (ext.isEmpty() ? "mp3" : ext);
    _file->setFileName(ui->lineEdit_folder->text()+"/"+ui->lineEdit_folder->text().section('/',-1,-1) + ".txt");

    QDir dir;
    dir.mkpath(ui->lineEdit_folder->text()+"/");

    QFile::copy(ui->lineEdit_mp3->text(),(ui->lineEdit_folder->text()+"/"+_file->_headMp3));


    _file->saveInFile();

    this->close();
}
