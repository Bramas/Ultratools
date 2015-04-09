/********************************************************************************
** Form generated from reading UI file 'uNewSongForm_Lyrics.ui'
**
** Created: Mon 28. Jun 23:10:02 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNEWSONGFORM_LYRICS_H
#define UI_UNEWSONGFORM_LYRICS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_UNewSongForm_Lyrics
{
public:
    QPlainTextEdit *plainTextEdit;
    QLabel *label;
    QCommandLinkButton *commandLinkButton;

    void setupUi(QDialog *UNewSongForm_Lyrics)
    {
        if (UNewSongForm_Lyrics->objectName().isEmpty())
            UNewSongForm_Lyrics->setObjectName(QString::fromUtf8("UNewSongForm_Lyrics"));
        UNewSongForm_Lyrics->resize(342, 608);
        plainTextEdit = new QPlainTextEdit(UNewSongForm_Lyrics);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 80, 321, 471));
        label = new QLabel(UNewSongForm_Lyrics);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 281, 61));
        label->setWordWrap(true);
        commandLinkButton = new QCommandLinkButton(UNewSongForm_Lyrics);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(80, 560, 185, 41));

        retranslateUi(UNewSongForm_Lyrics);

        QMetaObject::connectSlotsByName(UNewSongForm_Lyrics);
    } // setupUi

    void retranslateUi(QDialog *UNewSongForm_Lyrics)
    {
        UNewSongForm_Lyrics->setWindowTitle(QApplication::translate("UNewSongForm_Lyrics", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UNewSongForm_Lyrics", "Veuillez copier les paroles de la musique en mettant bien : une phrase karaok\303\251 = une ligne", 0, QApplication::UnicodeUTF8));
        commandLinkButton->setText(QApplication::translate("UNewSongForm_Lyrics", "Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UNewSongForm_Lyrics: public Ui_UNewSongForm_Lyrics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNEWSONGFORM_LYRICS_H
