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
    UDialogFeedback(QWidget *parent = 0);
    ~UDialogFeedback();

protected:
    void changeEvent(QEvent *e);
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
