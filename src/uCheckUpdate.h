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


#ifndef UCHECKUPDATE_H
#define UCHECKUPDATE_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>


class UCheckUpdate : public QObject
{
    Q_OBJECT

signals:
    void connected(void);

public:
    UCheckUpdate(QUrl url);
    void startRequest(QUrl url);

private slots:
    void downloadFile();
    void cancelDownload();
    void httpFinished();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
    void checkVersion();
    void emitConnected();


private:

    QUrl _url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    int httpGetId;
    bool httpRequestAborted;
    QString _version;
};
/**/
#endif // UCHECKUPDATE_H

