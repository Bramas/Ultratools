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




#include "uCheckUpdate.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QTimer>



UCheckUpdate::UCheckUpdate(QUrl url)
{
    _url = url;
    httpRequestAborted = false;
    startRequest(_url);
}

void UCheckUpdate::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void UCheckUpdate::downloadFile()
{


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
        QMessageBox::information(NULL, tr("HTTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        return;
    }


    // schedule the request
    httpRequestAborted = false;
}

void UCheckUpdate::cancelDownload()
{
    httpRequestAborted = true;
    reply->abort();
}

void UCheckUpdate::httpFinished()
{


    if (httpRequestAborted) {
        qDebug()<<"httpRequestAborted";
        return;
    }


    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        qDebug()<<"Network Error: "<<reply->errorString();
        return;
    }

    _version = reply->readLine();
    checkVersion();
}

void UCheckUpdate::updateDataReadProgress(qint64 /*bytesRead*/, qint64 /*totalBytes*/)
{
    if (httpRequestAborted)
        return;

}
/**/

void UCheckUpdate::checkVersion()
{
    if(_version.compare(VERSION))
    {
        qDebug()<<"there is a new version available: "<<_version;
        QMessageBox::information(NULL,tr("Nouvelle Version"),"<html>"+tr("Une nouvelle version est disponnible. Elle est disponible sur le site officiel")+" : <a href=\"http://ultratools.org/getnewversion.php\">http://ultratools.org</a>");
    }else
    {
        qDebug()<<"Ultratools is up to date";
    }
    QTimer::singleShot(1000, this, SLOT(emitConnected()));
}
void UCheckUpdate::emitConnected()
{
    emit connected();
}
