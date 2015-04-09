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
