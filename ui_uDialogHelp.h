/********************************************************************************
** Form generated from reading UI file 'uDialogHelp.ui'
**
** Created: Fri 2. Jul 01:18:47 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDIALOGHELP_H
#define UI_UDIALOGHELP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_UDialogHelp
{
public:

    void setupUi(QDialog *UDialogHelp)
    {
        if (UDialogHelp->objectName().isEmpty())
            UDialogHelp->setObjectName(QString::fromUtf8("UDialogHelp"));
        UDialogHelp->resize(400, 300);

        retranslateUi(UDialogHelp);

        QMetaObject::connectSlotsByName(UDialogHelp);
    } // setupUi

    void retranslateUi(QDialog *UDialogHelp)
    {
        UDialogHelp->setWindowTitle(QApplication::translate("UDialogHelp", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UDialogHelp: public Ui_UDialogHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDIALOGHELP_H
