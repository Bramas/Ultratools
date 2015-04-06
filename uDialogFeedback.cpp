#include "uDialogFeedback.h"
#include "ui_uDialogFeedback.h"
#include "uSetting.h"
#include <QPushButton>
#include <QUrlQuery>
#include <QUrl>
#include <QMessageBox>

UDialogFeedback::UDialogFeedback(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDialogFeedback)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(trUtf8("Envoyer"));
}

UDialogFeedback::~UDialogFeedback()
{
    delete ui;
}

void UDialogFeedback::accept()
{
    this->ui->buttonBox->setDisabled(true);
    this->ui->plainTextEdit->setDisabled(true);
    this->ui->groupBox->setDisabled(true);
    QString type("unknown");

    QUrl url("http://ultratools.org/feedback.php?soft=editor&method=post");
    QUrlQuery urlquery;
    urlquery.addQueryItem("soft", "editor");
    urlquery.addQueryItem("message", this->ui->plainTextEdit->toPlainText());
    urlquery.addQueryItem("id", USetting::Instance.getSoftId());
    urlquery.addQueryItem("type", type);
    urlquery.addQueryItem("version", VERSION);
    url.setQuery(urlquery);
    QByteArray data = url.query().toUtf8();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("User-Agent", QString("Ultratools Editor "VERSION" "OS_STRING).toLatin1());
    request.setRawHeader("soft-id", USetting::Instance.getSoftId().toLatin1());

    _reply = _manager.post(request, data);
    connect(_reply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(onError(QNetworkReply::NetworkError)));
}

void UDialogFeedback::onFinished()
{
    QMessageBox::information(this, trUtf8("Réponse"), _reply->readAll());
    QDialog::accept();
}

void UDialogFeedback::onError(QNetworkReply::NetworkError /*error*/)
{
    QMessageBox::warning(this, trUtf8("Erreur"), _reply->errorString());
    QDialog::reject();
}
