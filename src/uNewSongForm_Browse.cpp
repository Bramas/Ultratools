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
