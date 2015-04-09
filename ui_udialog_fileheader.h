/********************************************************************************
** Form generated from reading UI file 'udialog_fileheader.ui'
**
** Created: Mon 28. Jun 23:10:02 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDIALOG_FILEHEADER_H
#define UI_UDIALOG_FILEHEADER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UDialog_fileHeader
{
public:
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *label_8;
    QLineEdit *lineEdit_author;
    QLabel *label;
    QLineEdit *lineEdit_title;
    QLabel *label_2;
    QLineEdit *lineEdit_artist;
    QLabel *label_3;
    QLineEdit *lineEdit_mp3;
    QLabel *label_4;
    QLineEdit *lineEdit_cover;
    QLabel *label_5;
    QLineEdit *lineEdit_background;
    QLabel *label_6;
    QLineEdit *lineEdit_video;
    QLabel *label_7;
    QLineEdit *lineEdit_videogap;
    QLabel *label_9;
    QLineEdit *lineEdit_gap;
    QLabel *label_10;
    QLineEdit *lineEdit_bmp;
    QLabel *label_11;
    QLineEdit *lineEdit_edition;
    QLabel *label_12;
    QLineEdit *lineEdit_language;
    QLabel *label_13;
    QLineEdit *lineEdit_genre;
    QLabel *label_14;
    QLineEdit *lineEdit_year;
    QFrame *frame;
    QPushButton *pushButton_mp3;
    QPushButton *pushButton_cover;
    QPushButton *pushButton_background;
    QPushButton *pushButton_video;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UDialog_fileHeader)
    {
        if (UDialog_fileHeader->objectName().isEmpty())
            UDialog_fileHeader->setObjectName(QString::fromUtf8("UDialog_fileHeader"));
        UDialog_fileHeader->resize(390, 437);
        verticalLayoutWidget_2 = new QWidget(UDialog_fileHeader);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 371, 421));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(verticalLayoutWidget_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayoutWidget = new QWidget(groupBox);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 20, 341, 362));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_8 = new QLabel(horizontalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_8);

        lineEdit_author = new QLineEdit(horizontalLayoutWidget);
        lineEdit_author->setObjectName(QString::fromUtf8("lineEdit_author"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_author);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        lineEdit_title = new QLineEdit(horizontalLayoutWidget);
        lineEdit_title->setObjectName(QString::fromUtf8("lineEdit_title"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_title);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        lineEdit_artist = new QLineEdit(horizontalLayoutWidget);
        lineEdit_artist->setObjectName(QString::fromUtf8("lineEdit_artist"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_artist);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        lineEdit_mp3 = new QLineEdit(horizontalLayoutWidget);
        lineEdit_mp3->setObjectName(QString::fromUtf8("lineEdit_mp3"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_mp3);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        lineEdit_cover = new QLineEdit(horizontalLayoutWidget);
        lineEdit_cover->setObjectName(QString::fromUtf8("lineEdit_cover"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_cover);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_5);

        lineEdit_background = new QLineEdit(horizontalLayoutWidget);
        lineEdit_background->setObjectName(QString::fromUtf8("lineEdit_background"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEdit_background);

        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        lineEdit_video = new QLineEdit(horizontalLayoutWidget);
        lineEdit_video->setObjectName(QString::fromUtf8("lineEdit_video"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lineEdit_video);

        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_7);

        lineEdit_videogap = new QLineEdit(horizontalLayoutWidget);
        lineEdit_videogap->setObjectName(QString::fromUtf8("lineEdit_videogap"));

        formLayout->setWidget(7, QFormLayout::FieldRole, lineEdit_videogap);

        label_9 = new QLabel(horizontalLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_9);

        lineEdit_gap = new QLineEdit(horizontalLayoutWidget);
        lineEdit_gap->setObjectName(QString::fromUtf8("lineEdit_gap"));

        formLayout->setWidget(12, QFormLayout::FieldRole, lineEdit_gap);

        label_10 = new QLabel(horizontalLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_10);

        lineEdit_bmp = new QLineEdit(horizontalLayoutWidget);
        lineEdit_bmp->setObjectName(QString::fromUtf8("lineEdit_bmp"));

        formLayout->setWidget(13, QFormLayout::FieldRole, lineEdit_bmp);

        label_11 = new QLabel(horizontalLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_11);

        lineEdit_edition = new QLineEdit(horizontalLayoutWidget);
        lineEdit_edition->setObjectName(QString::fromUtf8("lineEdit_edition"));

        formLayout->setWidget(8, QFormLayout::FieldRole, lineEdit_edition);

        label_12 = new QLabel(horizontalLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_12);

        lineEdit_language = new QLineEdit(horizontalLayoutWidget);
        lineEdit_language->setObjectName(QString::fromUtf8("lineEdit_language"));

        formLayout->setWidget(9, QFormLayout::FieldRole, lineEdit_language);

        label_13 = new QLabel(horizontalLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_13);

        lineEdit_genre = new QLineEdit(horizontalLayoutWidget);
        lineEdit_genre->setObjectName(QString::fromUtf8("lineEdit_genre"));

        formLayout->setWidget(10, QFormLayout::FieldRole, lineEdit_genre);

        label_14 = new QLabel(horizontalLayoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_14);

        lineEdit_year = new QLineEdit(horizontalLayoutWidget);
        lineEdit_year->setObjectName(QString::fromUtf8("lineEdit_year"));

        formLayout->setWidget(11, QFormLayout::FieldRole, lineEdit_year);


        horizontalLayout->addLayout(formLayout);

        frame = new QFrame(horizontalLayoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(30, 0));
        frame->setMaximumSize(QSize(30, 16777215));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(3);
        frame->setMidLineWidth(5);
        pushButton_mp3 = new QPushButton(frame);
        pushButton_mp3->setObjectName(QString::fromUtf8("pushButton_mp3"));
        pushButton_mp3->setEnabled(false);
        pushButton_mp3->setGeometry(QRect(0, 77, 30, 23));
        pushButton_mp3->setMaximumSize(QSize(30, 16777215));
        pushButton_cover = new QPushButton(frame);
        pushButton_cover->setObjectName(QString::fromUtf8("pushButton_cover"));
        pushButton_cover->setEnabled(false);
        pushButton_cover->setGeometry(QRect(0, 104, 30, 23));
        pushButton_cover->setMaximumSize(QSize(30, 16777215));
        pushButton_cover->setAutoDefault(false);
        pushButton_background = new QPushButton(frame);
        pushButton_background->setObjectName(QString::fromUtf8("pushButton_background"));
        pushButton_background->setEnabled(false);
        pushButton_background->setGeometry(QRect(0, 130, 30, 23));
        pushButton_background->setMaximumSize(QSize(30, 16777215));
        pushButton_video = new QPushButton(frame);
        pushButton_video->setObjectName(QString::fromUtf8("pushButton_video"));
        pushButton_video->setEnabled(false);
        pushButton_video->setGeometry(QRect(0, 156, 30, 23));
        pushButton_video->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(frame);


        verticalLayout_2->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget_2);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(UDialog_fileHeader);
        QObject::connect(buttonBox, SIGNAL(accepted()), UDialog_fileHeader, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UDialog_fileHeader, SLOT(reject()));

        QMetaObject::connectSlotsByName(UDialog_fileHeader);
    } // setupUi

    void retranslateUi(QDialog *UDialog_fileHeader)
    {
        UDialog_fileHeader->setWindowTitle(QApplication::translate("UDialog_fileHeader", "Edition du fichier", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("UDialog_fileHeader", "Option du fichier", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("UDialog_fileHeader", "Author", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UDialog_fileHeader", "Title", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UDialog_fileHeader", "Artist", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("UDialog_fileHeader", "Mp3", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("UDialog_fileHeader", "Cover", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("UDialog_fileHeader", "Background", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("UDialog_fileHeader", "Vid\303\251o", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("UDialog_fileHeader", "Vid\303\251o gap", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("UDialog_fileHeader", "Gap", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("UDialog_fileHeader", "BMP", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("UDialog_fileHeader", "Edition", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("UDialog_fileHeader", "Language", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("UDialog_fileHeader", "Genre", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("UDialog_fileHeader", "Year", 0, QApplication::UnicodeUTF8));
        pushButton_mp3->setText(QApplication::translate("UDialog_fileHeader", "...", 0, QApplication::UnicodeUTF8));
        pushButton_cover->setText(QApplication::translate("UDialog_fileHeader", "...", 0, QApplication::UnicodeUTF8));
        pushButton_background->setText(QApplication::translate("UDialog_fileHeader", "...", 0, QApplication::UnicodeUTF8));
        pushButton_video->setText(QApplication::translate("UDialog_fileHeader", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UDialog_fileHeader: public Ui_UDialog_fileHeader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDIALOG_FILEHEADER_H
