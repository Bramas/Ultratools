#ifndef UDIALOGFEEDBACK_H
#define UDIALOGFEEDBACK_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
namespace Ui {
    class UDialogFeedback;
}

class UDialogFeedback : public QDialog {
    Q_OBJECT
public:
    UDialogFeedback(QWidget *parent = 0);
    ~UDialogFeedback();

private slots:
    void downloadFile();
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);

protected:
    void changeEvent(QEvent *e);
        void startRequest(QUrl url);
private:
    Ui::UDialogFeedback *ui;

    QUrl _url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    int httpGetId;
    bool httpRequestAborted;
};

#endif // UDIALOGFEEDBACK_H
