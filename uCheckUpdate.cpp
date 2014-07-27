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



#include "uCheckUpdate.h"



UCheckUpdate::UCheckUpdate(QUrl url)
{
    _url = url;
    downloadFile();
}

void UCheckUpdate::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
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
    startRequest(_url);
}

void UCheckUpdate::cancelDownload()
{
    httpRequestAborted = true;
    reply->abort();
}

void UCheckUpdate::httpFinished()
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
        }*/
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

         if(!file.atEnd()) {
            _version = file.readLine();

         }

checkVersion();
}

void UCheckUpdate::httpReadyRead()
{
    // this slot gets called everytime the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());


}

void UCheckUpdate::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    if (httpRequestAborted)
        return;

}
/**/

void UCheckUpdate::checkVersion()
{
    if(_version.compare(VERSION))
    {
        QMessageBox::information(NULL,tr("Nouvelle Version"),"<html>"+tr("Une nouvelle version est disponnible. Elle est disponible sur le site officiel")+" : <a href=\"http://ultratools.org/getnewversion.php\">http://ultratools.org</a>");
    }
    emit connected();
}
