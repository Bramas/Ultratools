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
