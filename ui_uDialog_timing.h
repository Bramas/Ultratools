/********************************************************************************
** Form generated from reading UI file 'uDialog_timing.ui'
**
** Created: Thu 10. Mar 19:23:57 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDIALOG_TIMING_H
#define UI_UDIALOG_TIMING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_uDialog_timing
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;

    void setupUi(QDialog *uDialog_timing)
    {
        if (uDialog_timing->objectName().isEmpty())
            uDialog_timing->setObjectName(QString::fromUtf8("uDialog_timing"));
        uDialog_timing->resize(400, 300);
        buttonBox = new QDialogButtonBox(uDialog_timing);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        spinBox = new QSpinBox(uDialog_timing);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(150, 50, 71, 21));
        spinBox->setMinimum(-20);
        label = new QLabel(uDialog_timing);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 50, 131, 21));
        label_2 = new QLabel(uDialog_timing);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(230, 50, 131, 21));
        label_3 = new QLabel(uDialog_timing);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 90, 101, 16));
        lineEdit = new QLineEdit(uDialog_timing);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(150, 90, 51, 21));
        label_4 = new QLabel(uDialog_timing);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(220, 90, 71, 16));

        retranslateUi(uDialog_timing);
        QObject::connect(buttonBox, SIGNAL(accepted()), uDialog_timing, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), uDialog_timing, SLOT(reject()));

        QMetaObject::connectSlotsByName(uDialog_timing);
    } // setupUi

    void retranslateUi(QDialog *uDialog_timing)
    {
        uDialog_timing->setWindowTitle(QApplication::translate("uDialog_timing", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("uDialog_timing", "Appliquer un d\303\251callage de", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("uDialog_timing", "\303\240 toute les notes", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("uDialog_timing", "ce qui correspond \303\240", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("uDialog_timing", "milisecondes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class uDialog_timing: public Ui_uDialog_timing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDIALOG_TIMING_H
