

#define URL_FEEDBACK "http://ultratools.org/feedback.php?soft=editor&type="

#include "uDialogFeedback.h"
#include "ui_uDialogFeedback.h"
#include <QMessageBox>
#include "uSetting.h"
#include "uCheckUpdate.h"

UDialogFeedback::UDialogFeedback(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDialogFeedback)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(downloadFile()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(accept()));

}

UDialogFeedback::~UDialogFeedback()
{
    delete ui;
}

void UDialogFeedback::changeEvent(QEvent *e)
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




void UDialogFeedback::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void UDialogFeedback::downloadFile()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    QString type;
    if(ui->radioButton->isChecked())
    {
        type="suggestion";
    }
    else
        if(ui->radioButton_3->isChecked())
        {
            type="pointPositif";
        }
        else
            if(ui->radioButton_2->isChecked())
            {
                type="pointNegatif";
            }


        _url = QUrl::fromUserInput(URL_FEEDBACK+type+"&version="+QString(VERSION)+"&id="+USetting::Instance.getSoftId()+"&message="+ui->textEdit->toPlainText());

    QFileInfo fileInfo(_url.path());
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    if (QFile::exists(fileName)) {
        if (0)
            return;
        QFile::remove(fileName);
    }

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        //QMessageBox::information(NULL, tr("HTTP"),
         //                        tr("Unable to save the file %1: %2.")
         //                        .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        QMessageBox::information(NULL,tr("Erreur"),tr("Un problème est survenu lors de l'écriture du fichier temporaire"));
        return;
    }


    // schedule the request
    httpRequestAborted = false;




        startRequest(_url);
}

void UDialogFeedback::cancelDownload()
{
    httpRequestAborted = true;
    reply->abort();
}

void UDialogFeedback::httpFinished()
{


    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
        return;
    }

    file->flush();
    file->close();



    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        file->remove();
        QMessageBox::information(NULL,tr("Erreur"),tr("Un problème est survenu lors de de la connection"));

      //  QMessageBox::information(NULL, tr("HTTP"),
                       //          tr("Download failed: %1.")
                         //        .arg(reply->errorString()));
    } else if (!redirectionTarget.isNull()) {
     /*   QUrl newUrl = _url.resolved(redirectionTarget.toUrl());
        if (QMessageBox::question(NULL, tr("HTTP"),
                                  tr("Redirect to %1 ?").arg(newUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            _url = newUrl;
            reply->deleteLater();
            file->open(QIODevice::WriteOnly);
            file->resize(0);
            startRequest(_url);
            return;

}*/QMessageBox::information(NULL,tr("Erreur"),tr("Un problème est survenu lors de de la connection"));


    } else {
        QString fileName = QFileInfo(_url.path()).fileName();
    }

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;





    QFileInfo fileInfo(_url.path());
    QString fileName = fileInfo.fileName();

    QFile file(fileName);
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
QString ret;
         if(!file.atEnd()) {
                    ret = file.readLine();

         }

         QMessageBox::information(NULL,"",ret);
         this->accept();
}

void UDialogFeedback::httpReadyRead()
{
    // this slot gets called everytime the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());


}

void UDialogFeedback::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    if (httpRequestAborted)
        return;

}
