/********************************************************************************
** Form generated from reading UI file 'uSettingDialog.ui'
**
** Created: Mon 28. Jun 23:10:02 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USETTINGDIALOG_H
#define UI_USETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_USettingDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_ultrastarLocation;
    QLabel *label_2;
    QSpinBox *spinBox_autosave;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_annuler;

    void setupUi(QDialog *USettingDialog)
    {
        if (USettingDialog->objectName().isEmpty())
            USettingDialog->setObjectName(QString::fromUtf8("USettingDialog"));
        USettingDialog->resize(478, 178);
        verticalLayoutWidget = new QWidget(USettingDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 441, 141));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_ultrastarLocation = new QLineEdit(verticalLayoutWidget);
        lineEdit_ultrastarLocation->setObjectName(QString::fromUtf8("lineEdit_ultrastarLocation"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit_ultrastarLocation);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        spinBox_autosave = new QSpinBox(verticalLayoutWidget);
        spinBox_autosave->setObjectName(QString::fromUtf8("spinBox_autosave"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, spinBox_autosave);


        verticalLayout->addLayout(formLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_ok = new QPushButton(verticalLayoutWidget);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));

        horizontalLayout_2->addWidget(pushButton_ok);

        pushButton_annuler = new QPushButton(verticalLayoutWidget);
        pushButton_annuler->setObjectName(QString::fromUtf8("pushButton_annuler"));

        horizontalLayout_2->addWidget(pushButton_annuler);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(USettingDialog);

        QMetaObject::connectSlotsByName(USettingDialog);
    } // setupUi

    void retranslateUi(QDialog *USettingDialog)
    {
        USettingDialog->setWindowTitle(QApplication::translate("USettingDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("USettingDialog", "Dossier Ultrastar", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("USettingDialog", "Interval entre 2 autoSave  (minutes)", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("USettingDialog", "Ok", 0, QApplication::UnicodeUTF8));
        pushButton_annuler->setText(QApplication::translate("USettingDialog", "Annuler", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class USettingDialog: public Ui_USettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USETTINGDIALOG_H
