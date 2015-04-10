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



#define URL_FEEDBACK "http://ultratools.org/feedback.php?soft=editor&type="

#include "uDialogFeedback.h"
#include "ui_uDialogFeedback.h"
#include <QMessageBox>
#include "uSetting.h"
#include "uCheckUpdate.h"
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
    request.setRawHeader("User-Agent", QString("Ultratools Editor " VERSION " " OS_STRING).toLatin1());
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
