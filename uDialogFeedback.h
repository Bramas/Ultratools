#ifndef UDIALOGFEEDBACK_H
#define UDIALOGFEEDBACK_H

#include <QDialog>

namespace Ui {
class UDialogFeedback;
}

class UDialogFeedback : public QDialog
{
    Q_OBJECT

public:
    explicit UDialogFeedback(QWidget *parent = 0);
    ~UDialogFeedback();

private:
    Ui::UDialogFeedback *ui;
};

#endif // UDIALOGFEEDBACK_H
