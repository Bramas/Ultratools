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

void UCheckUpdate::checkVersion()
{
    QStringList versions = _version.split('.');
    if(versions.size() != 2)
    {
        return;
    }
    int major, minor;
    bool ok;
    major = versions.at(0).toInt(&ok);
    if(!ok) return;
    minor = versions.at(1).toInt(&ok);
    if(!ok) return;

    if(VERSION_HEX < (major << 8) + minor)
    {
        qDebug()<<"there is a new version available: "<<_version;
        QMessageBox::information(NULL,tr("Nouvelle Version"),"<html>"+tr("Une nouvelle version est disponnible. Elle est disponible sur le site officiel")+" : <a href=\"http://ultratools.org/getnewversion.php\">http://ultratools.org</a>");
    }else
    {
        qDebug()<<"Ultratools is up to date ("<<_version.toLatin1().data()<<"<="<<VERSION<<")";
    }
    QTimer::singleShot(1000, this, SLOT(emitConnected()));
}
void UCheckUpdate::emitConnected()
{
    emit connected();
}
