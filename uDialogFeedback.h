#ifndef UDIALOGFEEDBACK_H
#define UDIALOGFEEDBACK_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
namespace Ui {
class UDialogFeedback;
}
class UDialogFeedback : public QDialog
{
    Q_OBJECT

public:
    explicit UDialogFeedback(QWidget *parent = 0);
    ~UDialogFeedback();

public slots:
    void accept();
    void onFinished();
    void onError(QNetworkReply::NetworkError);
private:
    Ui::UDialogFeedback *ui;
    QNetworkAccessManager _manager;
    QNetworkReply * _reply;
};

#endif // UDIALOGFEEDBACK_H
