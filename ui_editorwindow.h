/********************************************************************************
** Form generated from reading UI file 'editorwindow.ui'
**
** Created: Thu 10. Mar 19:04:24 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORWINDOW_H
#define UI_EDITORWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollBar>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditWindowClass
{
public:
    QAction *actionNouveau;
    QAction *actionOuvrir;
    QAction *actionSauvegarder;
    QAction *actionQuitter;
    QAction *actionAide;
    QAction *actionEditer_les_ent_tes;
    QAction *actionFichiers_r_cents;
    QAction *actionScinder_une_note;
    QAction *actionFusionner_deux_notes;
    QAction *actionNode_normale;
    QAction *actionNote_freestyle;
    QAction *actionNote_Gold;
    QAction *actionAjouter_une_note;
    QAction *actionAjouter_un_s_parateur;
    QAction *actionEnregistrer_sous;
    QAction *actionSupprimer_une_note;
    QAction *actionPr_f_rences;
    QAction *actionMorphe;
    QAction *actionDebug;
    QAction *actionVerrouiller_les_timings;
    QAction *actionDoublePrecision;
    QAction *actionCentrer;
    QAction *actionEnvoyer_une_suggestion_remarque_rapide;
    QAction *actionD_caler_les_notes;
    QWidget *centralwidget;
    QTabWidget *tab;
    QWidget *tabEditeur;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *tabEditVLayContener;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *HLayAudioDevice;
    QLCDNumber *lcd_music;
    QLabel *label;
    QSlider *Slider_MusiqueVolume;
    QLabel *label_2;
    QSlider *Slider_NoteVolume;
    QLabel *label_3;
    QSpinBox *spinBox_previous;
    QSpacerItem *horizontalSpacer;
    QGridLayout *tabEditeurLayMain;
    QSlider *vSlider;
    QScrollBar *vScroll;
    QSlider *hSlider;
    QScrollBar *hScroll;
    QPushButton *pushButton_separe;
    QWidget *tabFichier;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *tabFichierLayMain;
    QVBoxLayout *tabFichierLayV;
    QSpacerItem *verticalSpacer_2;
    QTextEdit *textFichierSource;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuAide;
    QMenu *menuEdition;
    QMenu *menuTiming;
    QToolBar *toolBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EditWindowClass)
    {
        if (EditWindowClass->objectName().isEmpty())
            EditWindowClass->setObjectName(QString::fromUtf8("EditWindowClass"));
        EditWindowClass->resize(816, 687);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/images/logo2.png"), QSize(), QIcon::Normal, QIcon::Off);
        EditWindowClass->setWindowIcon(icon);
        actionNouveau = new QAction(EditWindowClass);
        actionNouveau->setObjectName(QString::fromUtf8("actionNouveau"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNouveau->setIcon(icon1);
        actionOuvrir = new QAction(EditWindowClass);
        actionOuvrir->setObjectName(QString::fromUtf8("actionOuvrir"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Images/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOuvrir->setIcon(icon2);
        actionSauvegarder = new QAction(EditWindowClass);
        actionSauvegarder->setObjectName(QString::fromUtf8("actionSauvegarder"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Images/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSauvegarder->setIcon(icon3);
        actionQuitter = new QAction(EditWindowClass);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Images/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuitter->setIcon(icon4);
        actionAide = new QAction(EditWindowClass);
        actionAide->setObjectName(QString::fromUtf8("actionAide"));
        actionEditer_les_ent_tes = new QAction(EditWindowClass);
        actionEditer_les_ent_tes->setObjectName(QString::fromUtf8("actionEditer_les_ent_tes"));
        actionFichiers_r_cents = new QAction(EditWindowClass);
        actionFichiers_r_cents->setObjectName(QString::fromUtf8("actionFichiers_r_cents"));
        actionScinder_une_note = new QAction(EditWindowClass);
        actionScinder_une_note->setObjectName(QString::fromUtf8("actionScinder_une_note"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Images/images/scinder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScinder_une_note->setIcon(icon5);
        actionFusionner_deux_notes = new QAction(EditWindowClass);
        actionFusionner_deux_notes->setObjectName(QString::fromUtf8("actionFusionner_deux_notes"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Images/images/fusion.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFusionner_deux_notes->setIcon(icon6);
        actionNode_normale = new QAction(EditWindowClass);
        actionNode_normale->setObjectName(QString::fromUtf8("actionNode_normale"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Images/images/nodeNormal.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNode_normale->setIcon(icon7);
        actionNote_freestyle = new QAction(EditWindowClass);
        actionNote_freestyle->setObjectName(QString::fromUtf8("actionNote_freestyle"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Images/images/nodeFree.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNote_freestyle->setIcon(icon8);
        actionNote_Gold = new QAction(EditWindowClass);
        actionNote_Gold->setObjectName(QString::fromUtf8("actionNote_Gold"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Images/images/nodeGold.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNote_Gold->setIcon(icon9);
        actionAjouter_une_note = new QAction(EditWindowClass);
        actionAjouter_une_note->setObjectName(QString::fromUtf8("actionAjouter_une_note"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Images/images/addNote.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAjouter_une_note->setIcon(icon10);
        actionAjouter_un_s_parateur = new QAction(EditWindowClass);
        actionAjouter_un_s_parateur->setObjectName(QString::fromUtf8("actionAjouter_un_s_parateur"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Images/images/addSep.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAjouter_un_s_parateur->setIcon(icon11);
        actionEnregistrer_sous = new QAction(EditWindowClass);
        actionEnregistrer_sous->setObjectName(QString::fromUtf8("actionEnregistrer_sous"));
        actionEnregistrer_sous->setIcon(icon3);
        actionSupprimer_une_note = new QAction(EditWindowClass);
        actionSupprimer_une_note->setObjectName(QString::fromUtf8("actionSupprimer_une_note"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Images/images/supp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSupprimer_une_note->setIcon(icon12);
        actionPr_f_rences = new QAction(EditWindowClass);
        actionPr_f_rences->setObjectName(QString::fromUtf8("actionPr_f_rences"));
        actionMorphe = new QAction(EditWindowClass);
        actionMorphe->setObjectName(QString::fromUtf8("actionMorphe"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Images/images/morphe.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMorphe->setIcon(icon13);
        actionDebug = new QAction(EditWindowClass);
        actionDebug->setObjectName(QString::fromUtf8("actionDebug"));
        actionVerrouiller_les_timings = new QAction(EditWindowClass);
        actionVerrouiller_les_timings->setObjectName(QString::fromUtf8("actionVerrouiller_les_timings"));
        actionVerrouiller_les_timings->setCheckable(true);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Images/images/lockTime.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionVerrouiller_les_timings->setIcon(icon14);
        actionDoublePrecision = new QAction(EditWindowClass);
        actionDoublePrecision->setObjectName(QString::fromUtf8("actionDoublePrecision"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Images/images/doubleP.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDoublePrecision->setIcon(icon15);
        actionCentrer = new QAction(EditWindowClass);
        actionCentrer->setObjectName(QString::fromUtf8("actionCentrer"));
        actionEnvoyer_une_suggestion_remarque_rapide = new QAction(EditWindowClass);
        actionEnvoyer_une_suggestion_remarque_rapide->setObjectName(QString::fromUtf8("actionEnvoyer_une_suggestion_remarque_rapide"));
        actionEnvoyer_une_suggestion_remarque_rapide->setEnabled(true);
        actionD_caler_les_notes = new QAction(EditWindowClass);
        actionD_caler_les_notes->setObjectName(QString::fromUtf8("actionD_caler_les_notes"));
        centralwidget = new QWidget(EditWindowClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tab = new QTabWidget(centralwidget);
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setGeometry(QRect(0, 0, 821, 621));
        tabEditeur = new QWidget();
        tabEditeur->setObjectName(QString::fromUtf8("tabEditeur"));
        verticalLayoutWidget_2 = new QWidget(tabEditeur);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 10, 811, 521));
        tabEditVLayContener = new QVBoxLayout(verticalLayoutWidget_2);
        tabEditVLayContener->setObjectName(QString::fromUtf8("tabEditVLayContener"));
        tabEditVLayContener->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        tabEditVLayContener->addItem(verticalSpacer_3);

        HLayAudioDevice = new QHBoxLayout();
        HLayAudioDevice->setObjectName(QString::fromUtf8("HLayAudioDevice"));
        lcd_music = new QLCDNumber(verticalLayoutWidget_2);
        lcd_music->setObjectName(QString::fromUtf8("lcd_music"));

        HLayAudioDevice->addWidget(lcd_music);

        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        HLayAudioDevice->addWidget(label);

        Slider_MusiqueVolume = new QSlider(verticalLayoutWidget_2);
        Slider_MusiqueVolume->setObjectName(QString::fromUtf8("Slider_MusiqueVolume"));
        Slider_MusiqueVolume->setOrientation(Qt::Horizontal);

        HLayAudioDevice->addWidget(Slider_MusiqueVolume);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        HLayAudioDevice->addWidget(label_2);

        Slider_NoteVolume = new QSlider(verticalLayoutWidget_2);
        Slider_NoteVolume->setObjectName(QString::fromUtf8("Slider_NoteVolume"));
        Slider_NoteVolume->setOrientation(Qt::Horizontal);

        HLayAudioDevice->addWidget(Slider_NoteVolume);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        HLayAudioDevice->addWidget(label_3);

        spinBox_previous = new QSpinBox(verticalLayoutWidget_2);
        spinBox_previous->setObjectName(QString::fromUtf8("spinBox_previous"));
        spinBox_previous->setMinimum(0);
        spinBox_previous->setMaximum(30);
        spinBox_previous->setValue(2);

        HLayAudioDevice->addWidget(spinBox_previous);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HLayAudioDevice->addItem(horizontalSpacer);


        tabEditVLayContener->addLayout(HLayAudioDevice);

        tabEditeurLayMain = new QGridLayout();
        tabEditeurLayMain->setObjectName(QString::fromUtf8("tabEditeurLayMain"));
        vSlider = new QSlider(verticalLayoutWidget_2);
        vSlider->setObjectName(QString::fromUtf8("vSlider"));
        vSlider->setOrientation(Qt::Vertical);

        tabEditeurLayMain->addWidget(vSlider, 1, 3, 1, 1);

        vScroll = new QScrollBar(verticalLayoutWidget_2);
        vScroll->setObjectName(QString::fromUtf8("vScroll"));
        vScroll->setOrientation(Qt::Vertical);

        tabEditeurLayMain->addWidget(vScroll, 1, 2, 1, 1);

        hSlider = new QSlider(verticalLayoutWidget_2);
        hSlider->setObjectName(QString::fromUtf8("hSlider"));
        hSlider->setOrientation(Qt::Horizontal);

        tabEditeurLayMain->addWidget(hSlider, 4, 1, 1, 1);

        hScroll = new QScrollBar(verticalLayoutWidget_2);
        hScroll->setObjectName(QString::fromUtf8("hScroll"));
        hScroll->setOrientation(Qt::Horizontal);

        tabEditeurLayMain->addWidget(hScroll, 3, 1, 1, 1);

        pushButton_separe = new QPushButton(verticalLayoutWidget_2);
        pushButton_separe->setObjectName(QString::fromUtf8("pushButton_separe"));

        tabEditeurLayMain->addWidget(pushButton_separe, 2, 0, 1, 1);


        tabEditVLayContener->addLayout(tabEditeurLayMain);

        tab->addTab(tabEditeur, QString());
        tabFichier = new QWidget();
        tabFichier->setObjectName(QString::fromUtf8("tabFichier"));
        horizontalLayoutWidget = new QWidget(tabFichier);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(19, 19, 291, 251));
        tabFichierLayMain = new QHBoxLayout(horizontalLayoutWidget);
        tabFichierLayMain->setObjectName(QString::fromUtf8("tabFichierLayMain"));
        tabFichierLayMain->setContentsMargins(0, 0, 0, 0);
        tabFichierLayV = new QVBoxLayout();
        tabFichierLayV->setObjectName(QString::fromUtf8("tabFichierLayV"));
        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        tabFichierLayV->addItem(verticalSpacer_2);

        textFichierSource = new QTextEdit(horizontalLayoutWidget);
        textFichierSource->setObjectName(QString::fromUtf8("textFichierSource"));

        tabFichierLayV->addWidget(textFichierSource);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        tabFichierLayV->addItem(verticalSpacer);


        tabFichierLayMain->addLayout(tabFichierLayV);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        tabFichierLayMain->addWidget(pushButton);

        tab->addTab(tabFichier, QString());
        EditWindowClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EditWindowClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 816, 21));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuAide = new QMenu(menubar);
        menuAide->setObjectName(QString::fromUtf8("menuAide"));
        menuEdition = new QMenu(menubar);
        menuEdition->setObjectName(QString::fromUtf8("menuEdition"));
        menuTiming = new QMenu(menubar);
        menuTiming->setObjectName(QString::fromUtf8("menuTiming"));
        EditWindowClass->setMenuBar(menubar);
        toolBar = new QToolBar(EditWindowClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMinimumSize(QSize(0, 0));
        toolBar->setBaseSize(QSize(0, 40));
        toolBar->setIconSize(QSize(35, 30));
        EditWindowClass->addToolBar(Qt::TopToolBarArea, toolBar);
        statusbar = new QStatusBar(EditWindowClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        EditWindowClass->setStatusBar(statusbar);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuEdition->menuAction());
        menubar->addAction(menuTiming->menuAction());
        menubar->addAction(menuAide->menuAction());
        menuFichier->addAction(actionNouveau);
        menuFichier->addAction(actionOuvrir);
        menuFichier->addAction(actionSauvegarder);
        menuFichier->addAction(actionEnregistrer_sous);
        menuFichier->addSeparator();
        menuFichier->addAction(actionFichiers_r_cents);
        menuFichier->addSeparator();
        menuFichier->addAction(actionPr_f_rences);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menuAide->addAction(actionAide);
        menuEdition->addAction(actionEditer_les_ent_tes);
        menuEdition->addSeparator();
        menuEdition->addAction(actionScinder_une_note);
        menuEdition->addAction(actionFusionner_deux_notes);
        menuEdition->addSeparator();
        menuEdition->addAction(actionNode_normale);
        menuEdition->addAction(actionNote_freestyle);
        menuEdition->addAction(actionNote_Gold);
        menuEdition->addSeparator();
        menuEdition->addAction(actionAjouter_une_note);
        menuEdition->addAction(actionAjouter_un_s_parateur);
        menuEdition->addAction(actionSupprimer_une_note);
        menuEdition->addSeparator();
        menuEdition->addAction(actionMorphe);
        menuEdition->addAction(actionVerrouiller_les_timings);
        menuEdition->addAction(actionDoublePrecision);
        menuTiming->addAction(actionD_caler_les_notes);
        toolBar->addAction(actionNouveau);
        toolBar->addAction(actionOuvrir);
        toolBar->addAction(actionSauvegarder);
        toolBar->addSeparator();
        toolBar->addAction(actionNode_normale);
        toolBar->addAction(actionNote_freestyle);
        toolBar->addAction(actionNote_Gold);
        toolBar->addSeparator();
        toolBar->addAction(actionFusionner_deux_notes);
        toolBar->addAction(actionScinder_une_note);
        toolBar->addSeparator();
        toolBar->addAction(actionAjouter_une_note);
        toolBar->addAction(actionAjouter_un_s_parateur);
        toolBar->addSeparator();
        toolBar->addAction(actionSupprimer_une_note);
        toolBar->addSeparator();
        toolBar->addAction(actionMorphe);
        toolBar->addAction(actionVerrouiller_les_timings);
        toolBar->addAction(actionDoublePrecision);
        toolBar->addAction(actionCentrer);
        toolBar->addAction(actionDebug);

        retranslateUi(EditWindowClass);

        tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditWindowClass)
    {
        EditWindowClass->setWindowTitle(QApplication::translate("EditWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNouveau->setText(QApplication::translate("EditWindowClass", "Nouveau", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionNouveau->setStatusTip(QApplication::translate("EditWindowClass", "Nouveau", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionNouveau->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        actionOuvrir->setText(QApplication::translate("EditWindowClass", "Ouvrir", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionOuvrir->setStatusTip(QApplication::translate("EditWindowClass", "Ouvrir", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionOuvrir->setShortcut(QApplication::translate("EditWindowClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSauvegarder->setText(QApplication::translate("EditWindowClass", "Enregistrer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionSauvegarder->setStatusTip(QApplication::translate("EditWindowClass", "Enregistrer", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSauvegarder->setShortcut(QApplication::translate("EditWindowClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("EditWindowClass", "Quitter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionQuitter->setStatusTip(QApplication::translate("EditWindowClass", "Quitter", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionQuitter->setShortcut(QApplication::translate("EditWindowClass", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAide->setText(QApplication::translate("EditWindowClass", "Aide", 0, QApplication::UnicodeUTF8));
        actionEditer_les_ent_tes->setText(QApplication::translate("EditWindowClass", "Editer les ent\303\252tes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionEditer_les_ent_tes->setStatusTip(QApplication::translate("EditWindowClass", "Editer les ent\303\252tes (Titre, Auteur, Background...)", "Edition", QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionFichiers_r_cents->setText(QApplication::translate("EditWindowClass", "Fichiers r\303\251cents", 0, QApplication::UnicodeUTF8));
        actionScinder_une_note->setText(QApplication::translate("EditWindowClass", "Scinder une note", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionScinder_une_note->setStatusTip(QApplication::translate("EditWindowClass", "Scinder la note en 2", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionFusionner_deux_notes->setText(QApplication::translate("EditWindowClass", "Fusionner deux notes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionFusionner_deux_notes->setStatusTip(QApplication::translate("EditWindowClass", "Fusionner les notes s\303\251lectionn\303\251es", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionNode_normale->setText(QApplication::translate("EditWindowClass", "Node normale", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionNode_normale->setStatusTip(QApplication::translate("EditWindowClass", "Transformer les notes s\303\251lectionn\303\251es en notes Normales", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionNode_normale->setShortcut(QApplication::translate("EditWindowClass", "N", 0, QApplication::UnicodeUTF8));
        actionNote_freestyle->setText(QApplication::translate("EditWindowClass", "Note freestyle", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionNote_freestyle->setStatusTip(QApplication::translate("EditWindowClass", "Transformer les notes s\303\251lectionn\303\251es en notes libres", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionNote_freestyle->setShortcut(QApplication::translate("EditWindowClass", "F", 0, QApplication::UnicodeUTF8));
        actionNote_Gold->setText(QApplication::translate("EditWindowClass", "Note Gold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionNote_Gold->setStatusTip(QApplication::translate("EditWindowClass", "Transformer les notes s\303\251lectionn\303\251es en notes Gold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionNote_Gold->setShortcut(QApplication::translate("EditWindowClass", "G", 0, QApplication::UnicodeUTF8));
        actionAjouter_une_note->setText(QApplication::translate("EditWindowClass", "Ajouter une note", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionAjouter_une_note->setStatusTip(QApplication::translate("EditWindowClass", "Ajouter une note", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAjouter_un_s_parateur->setText(QApplication::translate("EditWindowClass", "Ajouter un s\303\251parateur", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionAjouter_un_s_parateur->setStatusTip(QApplication::translate("EditWindowClass", "Ajouter un s\303\251parateur (pour coup\303\251 une phrase en 2)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionEnregistrer_sous->setText(QApplication::translate("EditWindowClass", "Enregistrer sous...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionEnregistrer_sous->setStatusTip(QApplication::translate("EditWindowClass", "Enregistrer sous", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSupprimer_une_note->setText(QApplication::translate("EditWindowClass", "Supprimer les notes s\303\251lectionn\303\251es", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionSupprimer_une_note->setStatusTip(QApplication::translate("EditWindowClass", "Supprimer les notes s\303\251lectionn\303\251es", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSupprimer_une_note->setShortcut(QApplication::translate("EditWindowClass", "Del", 0, QApplication::UnicodeUTF8));
        actionPr_f_rences->setText(QApplication::translate("EditWindowClass", "Pr\303\251f\303\251rences", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionPr_f_rences->setStatusTip(QApplication::translate("EditWindowClass", "Pr\303\251f\303\251rences du logiciel", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionMorphe->setText(QApplication::translate("EditWindowClass", "Calquer les notes s\303\251lectionn\303\251es", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMorphe->setToolTip(QApplication::translate("EditWindowClass", "Calquer les notes s\303\251lectionn\303\251es sur les notes des phrases d'avant (qui sont affich\303\251 en gris)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionMorphe->setStatusTip(QApplication::translate("EditWindowClass", "Calquer les notes s\303\251lectionn\303\251es sur les notes des phrases d'avant (qui sont affich\303\251 en gris)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionDebug->setText(QApplication::translate("EditWindowClass", "debug", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionDebug->setStatusTip(QApplication::translate("EditWindowClass", "trie toutes les notes et les phrase ( a utiliser si les notes r\303\251agisse bizarement ou si certaine note ne joue pas de son)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionVerrouiller_les_timings->setText(QApplication::translate("EditWindowClass", "Verrouiller les timings", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionVerrouiller_les_timings->setStatusTip(QApplication::translate("EditWindowClass", "Verrouiller les timings (les notes ne bougerons que de bas en haut)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionDoublePrecision->setText(QApplication::translate("EditWindowClass", "Doubler la pr\303\251cision", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionDoublePrecision->setStatusTip(QApplication::translate("EditWindowClass", "Doubler la pr\303\251cision", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCentrer->setText(QApplication::translate("EditWindowClass", "Centrer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCentrer->setToolTip(QApplication::translate("EditWindowClass", "Centrer la vue sur le curseur", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCentrer->setShortcut(QApplication::translate("EditWindowClass", "C", 0, QApplication::UnicodeUTF8));
        actionEnvoyer_une_suggestion_remarque_rapide->setText(QApplication::translate("EditWindowClass", "Envoyer une suggestion/remarque rapide", 0, QApplication::UnicodeUTF8));
        actionD_caler_les_notes->setText(QApplication::translate("EditWindowClass", "D\303\251caler les notes", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditWindowClass", "Musique :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EditWindowClass", "Note :", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("EditWindowClass", "affichage de la phrase avec un retard de :", 0, QApplication::UnicodeUTF8));
        pushButton_separe->setText(QApplication::translate("EditWindowClass", "S\303\251parer (\313\222)", 0, QApplication::UnicodeUTF8));
        tab->setTabText(tab->indexOf(tabEditeur), QApplication::translate("EditWindowClass", "Editeur", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("EditWindowClass", "Actualiser", 0, QApplication::UnicodeUTF8));
        tab->setTabText(tab->indexOf(tabFichier), QApplication::translate("EditWindowClass", "Fichier brute", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("EditWindowClass", "Fichier", 0, QApplication::UnicodeUTF8));
        menuAide->setTitle(QApplication::translate("EditWindowClass", "Aide", 0, QApplication::UnicodeUTF8));
        menuEdition->setTitle(QApplication::translate("EditWindowClass", "Edition", 0, QApplication::UnicodeUTF8));
        menuTiming->setTitle(QApplication::translate("EditWindowClass", "Timing", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("EditWindowClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditWindowClass: public Ui_EditWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORWINDOW_H
