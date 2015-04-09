/********************************************************************************
** Form generated from reading UI file 'uNewSongForm_Browse.ui'
**
** Created: Mon 28. Jun 23:10:02 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNEWSONGFORM_BROWSE_H
#define UI_UNEWSONGFORM_BROWSE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UNewSongForm_Browse
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit_artist;
    QLabel *label_5;
    QLineEdit *lineEdit_title;
    QLabel *label_3;
    QCheckBox *checkBox_withVideo;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout_3;
    QLineEdit *lineEdit_folder;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_browse;
    QSpacerItem *verticalSpacer;
    QCommandLinkButton *commandNext;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *lineEdit_mp3;
    QPushButton *pushButton_browseMp3;

    void setupUi(QWidget *UNewSongForm_Browse)
    {
        if (UNewSongForm_Browse->objectName().isEmpty())
            UNewSongForm_Browse->setObjectName(QString::fromUtf8("UNewSongForm_Browse"));
        UNewSongForm_Browse->resize(534, 370);
        formLayoutWidget = new QWidget(UNewSongForm_Browse);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(60, 20, 221, 91));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_4);

        lineEdit_artist = new QLineEdit(formLayoutWidget);
        lineEdit_artist->setObjectName(QString::fromUtf8("lineEdit_artist"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit_artist);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_5);

        lineEdit_title = new QLineEdit(formLayoutWidget);
        lineEdit_title->setObjectName(QString::fromUtf8("lineEdit_title"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEdit_title);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        checkBox_withVideo = new QCheckBox(formLayoutWidget);
        checkBox_withVideo->setObjectName(QString::fromUtf8("checkBox_withVideo"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, checkBox_withVideo);

        horizontalLayoutWidget = new QWidget(UNewSongForm_Browse);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 140, 501, 69));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        lineEdit_folder = new QLineEdit(horizontalLayoutWidget);
        lineEdit_folder->setObjectName(QString::fromUtf8("lineEdit_folder"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lineEdit_folder);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_3 = new QLineEdit(horizontalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setEnabled(false);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, lineEdit_3);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label);


        horizontalLayout->addLayout(formLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        pushButton_browse = new QPushButton(horizontalLayoutWidget);
        pushButton_browse->setObjectName(QString::fromUtf8("pushButton_browse"));

        verticalLayout_4->addWidget(pushButton_browse);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_4);

        commandNext = new QCommandLinkButton(UNewSongForm_Browse);
        commandNext->setObjectName(QString::fromUtf8("commandNext"));
        commandNext->setGeometry(QRect(330, 310, 185, 41));
        horizontalLayoutWidget_2 = new QWidget(UNewSongForm_Browse);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(60, 250, 461, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        lineEdit_mp3 = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_mp3->setObjectName(QString::fromUtf8("lineEdit_mp3"));

        horizontalLayout_2->addWidget(lineEdit_mp3);

        pushButton_browseMp3 = new QPushButton(horizontalLayoutWidget_2);
        pushButton_browseMp3->setObjectName(QString::fromUtf8("pushButton_browseMp3"));

        horizontalLayout_2->addWidget(pushButton_browseMp3);


        retranslateUi(UNewSongForm_Browse);

        QMetaObject::connectSlotsByName(UNewSongForm_Browse);
    } // setupUi

    void retranslateUi(QWidget *UNewSongForm_Browse)
    {
        UNewSongForm_Browse->setWindowTitle(QApplication::translate("UNewSongForm_Browse", "Nouveau Son", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("UNewSongForm_Browse", "Artist :", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("UNewSongForm_Browse", "Title :", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("UNewSongForm_Browse", "Avec Video :", 0, QApplication::UnicodeUTF8));
        checkBox_withVideo->setText(QString());
        label_2->setText(QApplication::translate("UNewSongForm_Browse", "nom du fichier :", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UNewSongForm_Browse", "Dossier de cr\303\251ation :", 0, QApplication::UnicodeUTF8));
        pushButton_browse->setText(QApplication::translate("UNewSongForm_Browse", "Parcourir", 0, QApplication::UnicodeUTF8));
        commandNext->setText(QApplication::translate("UNewSongForm_Browse", "Suivant", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("UNewSongForm_Browse", "Fichier mp3 :", 0, QApplication::UnicodeUTF8));
        pushButton_browseMp3->setText(QApplication::translate("UNewSongForm_Browse", "Parcourir", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UNewSongForm_Browse: public Ui_UNewSongForm_Browse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNEWSONGFORM_BROWSE_H
