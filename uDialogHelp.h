#ifndef UDIALOGHELP_H
#define UDIALOGHELP_H

#include <QDialog>

namespace Ui {
    class UDialogHelp;
}

class UDialogHelp : public QDialog {
    Q_OBJECT
public:
    UDialogHelp(QWidget *parent = 0);
    ~UDialogHelp();

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);

private:
    Ui::UDialogHelp *ui;
};

#endif // UDIALOGHELP_H
