#ifndef UDIALOG_TIMING_H
#define UDIALOG_TIMING_H

#include <QDialog>

class UFile;

namespace Ui {
    class uDialog_timing;
}

class UDialog_timing : public QDialog {
    Q_OBJECT

    public slots:
       void accept(void);
       void valueChanged(void);

public:
    UDialog_timing(QWidget *parent, UFile * file);
    ~UDialog_timing();
protected:
    UFile * _file;
    void changeEvent(QEvent *e);

private:
    Ui::uDialog_timing *ui;
};


#endif // UDIALOG_TIMING_H


#include "uFile.h"
