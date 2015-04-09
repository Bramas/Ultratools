/********************************************************************************
** Form generated from reading UI file 'uDialogFeedback.ui'
**
** Created: Fri 2. Jul 11:22:26 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDIALOGFEEDBACK_H
#define UI_UDIALOGFEEDBACK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UDialogFeedback
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *label;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *UDialogFeedback)
    {
        if (UDialogFeedback->objectName().isEmpty())
            UDialogFeedback->setObjectName(QString::fromUtf8("UDialogFeedback"));
        UDialogFeedback->resize(279, 271);
        verticalLayoutWidget = new QWidget(UDialogFeedback);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 261, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(verticalLayoutWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(verticalLayoutWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(verticalLayoutWidget);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout->addWidget(radioButton_3);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        textEdit = new QTextEdit(verticalLayoutWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(UDialogFeedback);

        QMetaObject::connectSlotsByName(UDialogFeedback);
    } // setupUi

    void retranslateUi(QDialog *UDialogFeedback)
    {
        UDialogFeedback->setWindowTitle(QApplication::translate("UDialogFeedback", "Dialog", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("UDialogFeedback", "Suggestion", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("UDialogFeedback", "Point N\303\251gatif", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("UDialogFeedback", "Point Positif", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UDialogFeedback", "Message :", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("UDialogFeedback", "Envoyer", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("UDialogFeedback", "Annuler", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UDialogFeedback: public Ui_UDialogFeedback {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDIALOGFEEDBACK_H
