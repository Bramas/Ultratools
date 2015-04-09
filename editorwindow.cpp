/****************************************************************************
**
** Author & Contact: Quentin BRAMAS ( contact@bramas.fr )
**
** This file is part of Ultratools.
**
** GNU General Public License Usage
** ExUlt is free software: you can redistribute it and/or modify it under the
** terms of General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** ExUlt is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** If you have questions regarding the use of this file, please contact
** Quentin BRAMAS (contact@bramas.fr).
**
****************************************************************************/


#include "editorwindow.h"
#include "ui_editorwindow.h"
#include "uDialog_timing.h"
#include "uWydget_timeline.h"
#include "uWydget_lyrics.h"
#include "uNoteManager.h"
#include "uRecorder.h"
#include "uDialogAbout.h"
#include "uWidgetSongData.h"
#include "uShowSentenceWydget.h"
#include <math.h>
#include <QUrl>
#include <QMimeData>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>

#define USEMEMLOAD
#define USEFMOD TRUE


#define WINDOW_TITLE "Ultratools Editor"
#define URL_VERSION "http://ultratools.org/version.php?soft=editor"

UEditorWindow::UEditorWindow(QWidget *parent)
    : QMainWindow(parent), _spaceNoteGeneration(false), ui(new Ui::EditWindowClass)
{

    this->setFocusPolicy(Qt::StrongFocus);
_startTime=0;
    _playViolon = false;
    _currentFile = NULL;
    _isPlaying=false;
setAcceptDrops(true);
USetting::Instance.init();
UCheckUpdate * check = new UCheckUpdate(QUrl(URL_VERSION));
connect(check,SIGNAL(connected()),this,SLOT(onConnected()));


    setupAudio();
    setupUi();

            _currentFile = new UFile(this);// "songs/arkol - vingt ans/Arkol - vingt ans.txt");

            fileConnect();

            this->showSentenceWidget->setHScroll(0);

        connect(ui->vScroll,SIGNAL(valueChanged(int)),this,SLOT(changeVScroll(int)));
        //connect(ui->vScroll,SIGNAL(actionTriggered(int)),this,SLOT(changeVScroll(int)));

        connect(ui->hScroll,SIGNAL(valueChanged(int)),this,SLOT(changeHScroll(int)));
        //connect(ui->hScroll,SIGNAL(actionTriggered(int)),this,SLOT(changeHScroll(int)));

        connect(ui->hSlider,SIGNAL(sliderMoved(int)),this,SLOT(changeHSlider(int)));

        connect(ui->vSlider,SIGNAL(sliderMoved(int)),this,SLOT(changeVSlider(int)));




        connect(ui->actionOuvrir,SIGNAL(triggered()),this,SLOT(openFile()));

        connect(ui->actionEditer_les_ent_tes,SIGNAL(triggered()),this,SLOT(editHeader()));
        connect(ui->actionD_caler_les_notes,SIGNAL(triggered()),this,SLOT(openTiming()));
        connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(playAction, SIGNAL(triggered()), this, SLOT(tooglePlay()));
    connect(pauseAction, SIGNAL(triggered()), this, SLOT(tooglePlay()));
    connect(recordAction, SIGNAL(triggered()), this, SLOT(toggleRecord()));
    connect(showSentenceWidget,SIGNAL(haveToStop()), this, SLOT(tooglePlay()));
        /*connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
        connect(playAction, SIGNAL(triggered()), &UNoteManager::Instance, SLOT(play()));
        connect(playAction, SIGNAL(triggered()), showSentenceWidget, SLOT(play()));
        connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()) );
        connect(pauseAction, SIGNAL(triggered()), &UNoteManager::Instance, SLOT(pause()) );
        connect(pauseAction, SIGNAL(triggered()), showSentenceWidget, SLOT(stop()) );

        connect(showSentenceWidget,SIGNAL(haveToStop()),mediaObject,SLOT(pause()));
        connect(showSentenceWidget,SIGNAL(haveToStop()),&UNoteManager::Instance,SLOT(pause()));
*/
        connect(ui->actionNode_normale,SIGNAL(triggered()),showSentenceWidget, SLOT(setNormal()));
        connect(ui->actionNote_freestyle,SIGNAL(triggered()),showSentenceWidget, SLOT(setFree()));
        connect(ui->actionNote_Gold,SIGNAL(triggered()),showSentenceWidget, SLOT(setGold()));

        connect(ui->actionFusionner_deux_notes,SIGNAL(triggered()),showSentenceWidget, SLOT(fusion()));
        connect(ui->actionScinder_une_note,SIGNAL(triggered()),showSentenceWidget, SLOT(scinder()));

        connect(ui->actionAjouter_une_note,SIGNAL(triggered()),showSentenceWidget, SLOT(nextClickAddNote()));
        connect(ui->actionAjouter_un_s_parateur,SIGNAL(triggered()),showSentenceWidget, SLOT(nextClickAddSeparator()));

        connect(ui->actionSauvegarder,SIGNAL(triggered()),this,SLOT(save()));
        connect(ui->actionEnregistrer_sous,SIGNAL(triggered()),this,SLOT(saveAs()));
        connect(ui->actionNouveau,SIGNAL(triggered()),this,SLOT(newSong()));

        connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(close()));

        connect(&UInputManager::Instance,SIGNAL(spacePressEvent(void)),this,SLOT(tooglePlay()));

        connect(_wydget_timeline, SIGNAL(gapModified(double)),this, SLOT(gapModified(double)));

         connect(ui->actionSupprimer_une_note,SIGNAL(triggered()),showSentenceWidget,SLOT(deleteNotes()));

        connect(ui->actionPr_f_rences,SIGNAL(triggered()),&USetting::Instance,SLOT(showDialog()));

        connect(ui->actionMorphe,SIGNAL(triggered()),showSentenceWidget,SLOT(calquer()));


        connect(ui->actionVerrouiller_les_timings,SIGNAL(toggled(bool)),showSentenceWidget,SLOT(lockTime(bool)));

        connect(ui->actionCentrer,SIGNAL(triggered()),this,SLOT(centerView()));

        connect(ui->actionAide,SIGNAL(triggered()),this,SLOT(displayHelpScreen()));
        connect(ui->actionEnvoyer_une_suggestion_remarque_rapide,SIGNAL(triggered()),this,SLOT(displayFeedback()));



       // connect(ui->menubar,SIGNAL(hovered(QAction*)),this,SLOT(hoverAction(QAction*)));
       // connect(ui->menuFichier,SIGNAL(hovered(QAction*)),this,SLOT(hoverAction(QAction*)));

        ui->vSlider->setValue(12);
        changeVSlider(12);
        changeHScroll(0);


       // _currentFile = new UFile(this);
        this->showSentenceWidget->setLyrics(_currentFile->lyrics);
        _wydget_lyrics->setWidgetWords(showSentenceWidget);

        readLastFile();

        connect(ui->actionFichiers_r_cents,SIGNAL(triggered()),this,SLOT(openLastFile()));



        readSettings();

        _spaceNote = new Recorder(this->showSentenceWidget);

        _autoSaveTimer = new QTimer(this);
          connect(_autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));


}

UEditorWindow::~UEditorWindow()
{
    delete ui;
}
void UEditorWindow::editHeader(void)
{
    if(_currentFile)
    {
        _currentFile->editHeader();
    }
}
void UEditorWindow::autoSave()
{
    _currentFile->autoSave();
}

void UEditorWindow::readLastFile()
{    
    foreach(const QString &filename, USetting::Instance.lastOpenFiles())
    {
        QFileInfo info(filename);
        if(!info.exists())
        {
            continue;
        }
        QAction * a = new QAction(info.baseName(), 0);
        a->setProperty("absolutePath", info.absoluteFilePath());
        connect(a, SIGNAL(triggered()), this, SLOT(openLastFile()));
        ui->menuFichier->insertAction(ui->actionFichiers_r_cents, a);
    }
    ui->menuFichier->removeAction(ui->actionFichiers_r_cents);
}
void UEditorWindow::openLastFile()
{
    QAction * from = qobject_cast<QAction*>(sender());
    if(!from)
    {
        return;
    }
    QString filename = from->property("absolutePath").toString();
    if(filename.isEmpty() || !QFileInfo(filename).exists())
    {
        return;
    }
    openFile(filename);
}
void UEditorWindow::gapModified(double d)
{
    _currentFile->setGap(d);
    showSentenceWidget->updateGap();
}

void UEditorWindow::newFile()
{

}
int UEditorWindow::discardChange()
{
    if(_currentFile && _currentFile->isModified())
    {
            QMessageBox msgBox;
            msgBox.setText(tr("Voulez-vous continuer ?"));
            msgBox.setInformativeText(tr("Les changements ne seront pas enregistré"));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            return msgBox.exec();
    }

    return QMessageBox::Yes;
}

void UEditorWindow::openFile(QString fileName)
{



    if(discardChange() != QMessageBox::Yes) return;

    if(fileName=="")
    {
        fileName = QFileDialog::getOpenFileName(this,trUtf8("Choisir un fichier song"),USetting::Instance.getSongsLocation(),tr("texte (*.txt)"));
    }

    if(!fileName.length()) return;

    if(_currentFile)
    {
        fileDisconnect();
        delete _currentFile;
        _currentFile = 0;
    }


    _currentFile = new UFile(this,fileName);// "songs/arkol - vingt ans/Arkol - vingt ans.txt");
    fileConnect();

    USetting::Instance.addOpenFile(fileName);


    this->showSentenceWidget->setLyrics(_currentFile->lyrics);
    UNoteManager::Instance.setLyrics(_currentFile->lyrics);

    _wydget_timeline->setBpm(_currentFile->lyrics->getBpm());
    _wydget_timeline->setGap(_currentFile->lyrics->getGap());

    _wydget_lyrics->setWidgetWords(showSentenceWidget);

    _autoSaveTimer->start(USetting::Instance.getAutoSaveInterval()*60000);

adaptNewFile();
if(!_currentFile->_headMp3.compare(""))
{
    QMessageBox::warning(this,tr("Attention"),tr("Pensez à indiquer où se trouve le fichier mp3 (menu Edition >> Edtiter les Entêtes)"));
}
else
if(!QFile::exists(fileName.replace('\\','/').section('/',0,-2)+"/"+_currentFile->_headMp3))
{
    QMessageBox::warning(this,tr("Attention"),tr("Le fichier mp3 n'a pas été trouvé."));
}
else
{
    if(!UAudioManager::Instance.setSource(fileName.replace('\\','/').section('/',0,-2)+"/"+_currentFile->_headMp3))
    {
        QMessageBox::warning(this,tr("Attention"),tr("Il y a eu un problème lors de la lecture du fichier son")+" : "+fileName.replace('\\','/').section('/',0,-2)+"/"+_currentFile->_headMp3);
    }
}

 }

void UEditorWindow::adaptNewFile()
{

    if(_currentFile->lyrics->words().isEmpty())
    {
        return;
    }
    showSentenceWidget->setVScroll((255-_currentFile->lyrics->words().at(0)->getPitch())*2);

    //qDebug()<<*range;
    ui->hScroll->setMaximum(_currentFile->getMax()+_currentFile->lyrics->timeToBeat(_currentFile->lyrics->getGap()));

    ui->vScroll->setValue((255-_currentFile->lyrics->words().at(0)->getPitch()));

    UNoteManager::Instance.setMaxPitch(_currentFile->lyrics->getPitchMax());

       ui->vScroll->setRange((245-_currentFile->lyrics->getPitchMax()),(255-_currentFile->lyrics->getPitchMin()));
    //qDebug()<<"maxR "<<(255-lyrics->getPitchMax())<<" , "<<(255-lyrics->getPitchMin());
    //qDebug()<<((lyrics->getSentences()->at(0)->getPitchMin()+lyrics->getSentences()->at(0)->getPitchMax())/2);



    if((_currentFile->lyrics->getPitchMin()+_currentFile->lyrics->getPitchMax())/2+20>_currentFile->lyrics->getPitchMax())
    {
         this->changeVScroll(255-_currentFile->lyrics->getPitchMax());
         ui->vScroll->setValue(255-_currentFile->lyrics->getPitchMax());
    }
    else
    {
         this->changeVScroll((235-(_currentFile->lyrics->getPitchMin()+_currentFile->lyrics->getPitchMax())/2));
         ui->vScroll->setValue((235-(_currentFile->lyrics->getPitchMin()+_currentFile->lyrics->getPitchMax())/2));
     }


    this->changeHScroll((_currentFile->lyrics->getGap()>2000?_currentFile->lyrics->getGap()-2000:0)*_currentFile->lyrics->getBpm()/15000.0);
      ui->hScroll->setValue((_currentFile->lyrics->getGap()>2000?_currentFile->lyrics->getGap()-2000:0)*_currentFile->lyrics->getBpm()/15000.0);

      onFileModified(false);
}

void UEditorWindow::changeVSlider(int s)
{
this->showSentenceWidget->setVScale(s*20);


this->showLines->setMin(ui->vScroll->value());
this->showLines->setMax(s*2+ui->vScroll->value());
//qDebug()<<"vScale : "<<s;
}
void UEditorWindow::changeHSlider(int s)
{
    ui->hScroll->setPageStep(exp(((double)ui->hSlider->value())/100.0));
 //  this->hScroll->setMaximum(*range/10-hSlider->value());
   this->showSentenceWidget->setHScale(s);
   _widgetSongData->setHScale(s);

    _wydget_timeline->setMin(ui->hScroll->value());
    // _wydget_timeline->setMax(exp(((double)_lastHSlideValue)/100.0) + ui->hScroll->value());
    _wydget_timeline->setMax(exp(((double)ui->hSlider->value())/100.0) + ui->hScroll->value());

    _wydget_lyrics->onScroll();
}

QScrollBar * UEditorWindow::verticalScrollBar()
{
    return this->ui->vScroll;
}
QScrollBar * UEditorWindow::horizontalScrollBar()
{
    return this->ui->hScroll;
}

void UEditorWindow::changeVScroll(int s)
{

this->showSentenceWidget->setVScroll(s);
this->showLines->setMin(s);
////qDebug()<<this->vSlider->value();
//qDebug()<<"vScale : "<<this->vSlider->value();
this->showLines->setMax(s+ui->vSlider->value()*2);

}
void UEditorWindow::changeHScroll(int s)
{
if(s!=ui->hScroll->value()) //it's mean that something else that the scroll want to scroll
{
    ui->hScroll->setValue(s);//so update the scrollBar
}


_widgetSongData->setHScroll(s);
this->showSentenceWidget->setHScroll(s);

//_wydget_timeline->setMin(s);
//_wydget_timeline->setMax(exp(((double)ui->hSlider->value())/100.0) + s);
_wydget_timeline->update();
_wydget_lyrics->onScroll();

}

void UEditorWindow::bpmChanged(int n)
{
    _wydget_timeline->setBpm(n);
    showSentenceWidget->updateGap();
}
void UEditorWindow::gapChanged(float n)
{

    _wydget_timeline->setGap(n);
    showSentenceWidget->updateGap();
}

void UEditorWindow::setupUi()
{

    ui->setupUi(this);
       // QScrollArea *sa = new QScrollArea( ui->tab );

        showLines = new  ShowLines();
        showSentenceWidget = new ShowSentenceWidget(this);
        _wydget_timeline = new UWydget_Timeline(this);
        _wydget_timeline->setWidgetSentence(this->showSentenceWidget);
        _wydget_lyrics = new UWydget_Lyrics();


   // hSlider=new QSlider(Qt::Horizontal,this);
    ui->hSlider->setRange((log(30)*100.0),(log(10000)*100.0));// 30 beats to 10000 beats
    ui->hSlider->setValue((log(100)*100.0));

    //vSlider=new QSlider(Qt::Vertical,this);
    ui->vSlider->setRange(6,20);


    _widgetSongData = new WidgetSongData(this);
    _widgetSongData->setWidgetSentence(this->showSentenceWidget);
    UAudioManager::Instance.setWidgetSongData(_widgetSongData);

    //ui->hScroll = new QScrollBar(Qt::Horizontal);
    //ui->vScroll = new QScrollBar(Qt::Vertical);
    ui->hScroll->setRange(0,999);
    ui->vScroll->setRange(185,235);

        ui->tabEditeurLayMain->setColumnMinimumWidth(0,70);// the minimal width to display the showline wydget
        ui->tabEditeurLayMain->setRowMinimumHeight(1,30);// the minimal height to display the timeline wydget
        ui->tabEditeurLayMain->addWidget(_wydget_timeline,1,1);
        ui->tabEditeurLayMain->addWidget(showLines,2,0);
        ui->tabEditeurLayMain->addWidget(showSentenceWidget,2,1);
        ui->tabEditeurLayMain->addWidget(_widgetSongData,0,1);
        ui->mainHorizontalLayout->addWidget(_wydget_lyrics);
        //ui->tabEditeurLayMain->setRowMinimumHeight(2,40);
        //ui->tabEditeurLayMain->setColumnMinimumWidth(4,100);

     //ui->tabEditeurLayMain->addWidget(ui->hScroll,1,1);
    // ui->tabEditeurLayMain->addWidget(ui->vScroll,0,2);

     //ui->tabEditeurLayMain->addWidget(ui->vSlider,0,3);
     //ui->tabEditeurLayMain->addWidget(ui->hSlider,2,1);


        playAction = new QAction(QIcon(":/images/player_play.png"), tr("Play"), this);
        playAction->setShortcut(tr("Crl+P"));
        pauseAction = new QAction(QIcon(":/images/player_pause.png"), tr("Pause"), this);
        pauseAction->setShortcut(tr("Ctrl+A"));
        pauseAction->setVisible(false);
        recordAction = new QAction(QIcon(":/images/recordnormal.png"), tr("Record"), this);
        recordAction->setShortcut(tr("Ctrl+R"));

        ui->lcd_music->display("00:00");


        ui->Slider_MusiqueVolume->setRange(0,100);
        ui->Slider_MusiqueVolume->setValue(100);
        connect( ui->Slider_MusiqueVolume, SIGNAL(sliderMoved(int)), &UAudioManager::Instance, SLOT(changeVolume(int)));
        ui->Slider_NoteVolume->setRange(0,100);
        ui->Slider_NoteVolume->setValue(100);
        connect( ui->Slider_NoteVolume, SIGNAL(sliderMoved(int)), &UNoteManager::Instance, SLOT(setVolume(int)));



        QToolBar *bar = new QToolBar;

        bar->addAction(playAction);
        bar->addAction(pauseAction);
        bar->addAction(recordAction);

        ui->HLayAudioDevice->insertWidget(1,bar);



        connect(showSentenceWidget, SIGNAL(click(quint64)), this, SLOT(changeSeek(quint64)));
        connect(_wydget_timeline, SIGNAL(click(quint64)), this, SLOT(tick(quint64)));
        connect(showSentenceWidget, SIGNAL(modified()), _wydget_lyrics, SLOT(onScroll()));
        connect(showSentenceWidget, SIGNAL(emptyClik()), _wydget_lyrics, SLOT(onScroll()));
        connect(showSentenceWidget, SIGNAL(selection(int,int)), _wydget_lyrics, SLOT(onSelectionChange(int,int)));
        connect(showSentenceWidget, SIGNAL(doubleClik(int)), _wydget_lyrics, SLOT(ondoubleClick(int)));

        connect(showSentenceWidget,SIGNAL(autoScroll(int)),this, SLOT(changeHScroll(int)));
        
        

}
void UEditorWindow::changeSeek(quint64 time)
{
    _startTime = time;
    UAudioManager::Instance.seek(time);
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

    ui->lcd_music->display(displayTime.toString("mm:ss"));
    _wydget_timeline->setSeek(time);
    //UNoteManager::Instance.pause();
}

void UEditorWindow::setupAudio()
{
    //UMidiManager  * mgr = new UMidiManager();



    UAudioManager::Instance.init();

    UNoteManager::Instance.setupAudio(this);

    connect( &UAudioManager::Instance, SIGNAL(tick(quint64)), this, SLOT(tick(quint64)));
    connect( &UAudioManager::Instance, SIGNAL(endOfSong()), this, SLOT(pause()));



}

void UEditorWindow::tick(quint64 time)
{
   UNoteManager::Instance.tick(time);
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

    ui->lcd_music->display(displayTime.toString("mm:ss"));


    showSentenceWidget->setSeekPosition(_currentFile->lyrics->timeToBeat(time));
    _wydget_timeline->setSeek(time);
    _widgetSongData->setSeekPosition(time);
    _wydget_timeline->setSeekPosition(time);


if(_currentFile->lyrics->words().empty()) return;


  Word * w = NULL;

  //qDebug()<<time<<" : s :"<<_currentFile->beatToMsc(_currentFile->lyrics->getSentences()->first()->getSepAfter()->getTime2())<< "Sentence commençant par "<<s->getWords()->first()->getWord();

  if(UNoteManager::Instance.isPlaying())
  foreach(w,_currentFile->lyrics->words())
  {
        if(!w->isSeparator() && _currentFile->lyrics->beatToMsc(w->getTime())-20<=time
           && _currentFile->lyrics->beatToMsc(w->getTime()+w->getLength())>time
           )
        {

            UNoteManager::Instance.play(w);
        }
  }


}
void UEditorWindow::about()
{
    DialogAbout a(this);
    a.exec();
}

void UEditorWindow::aboutToFinish()
{

}

void UEditorWindow::writeSettings()
{
    QSettings settings;

    settings.beginGroup("EditorWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void UEditorWindow::readSettings()
{
    //this->setWindowTitle(WINDOW_TITLE);

    QSettings settings;

    settings.beginGroup("EditorWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void UEditorWindow::closeEvent(QCloseEvent *event)
{

    int ret = discardChange();

    if(ret != QMessageBox::Yes) {  event->ignore(); return; }

    //if (userReallyWantsToQuit()) {

    _currentFile->cleanBAK();

    writeSettings();

    event->accept();
    //} else {
    //    event->ignore();
    //}
}

void UEditorWindow::saveAs()
{

    QString file = QFileDialog::getSaveFileName(this,tr("Sauvegarder"),"","");
    if(!file.length()) return;

    _currentFile->saveInFile(file);

}

void UEditorWindow::save()
{

    _currentFile->saveInFile();

}
void UEditorWindow::toggleRecord()
{
    if(_spaceNote->isRecording())
    {
        _spaceNote->stop();
        recordAction->setIcon(QIcon(":/images/recordnormal.png"));
    }
    else
    {
        _spaceNote->start();
        recordAction->setIcon(QIcon(":/images/recordpressed.png"));
    }
}

void UEditorWindow::pause()
{
    UAudioManager::Instance.pause();
    UNoteManager::Instance.pause();
    showSentenceWidget->stop();
    if(USetting::Instance.isRestartAfterStop())
    {
        UAudioManager::Instance.seek(_startTime);
    }
    pauseAction->setVisible(false);
    playAction->setVisible(true);
}
void UEditorWindow::play()
{
    _startTime = UAudioManager::Instance.currentTime();
    UAudioManager::Instance.play();
    UNoteManager::Instance.play();
    showSentenceWidget->play();
    playAction->setVisible(false);
    pauseAction->setVisible(true);
}

void UEditorWindow::tooglePlay()
{
    if(UNoteManager::Instance.isPlaying())
    {
        pause();
    }
    else
    {
        play();
    }
}

void UEditorWindow::newSong(void)
{
    if(discardChange() != QMessageBox::Yes) return;

    if(_currentFile)
    {
        fileDisconnect();
        delete _currentFile;
    }


    _currentFile = new UFile(this);// "songs/arkol - vingt ans/Arkol - vingt ans.txt");

    fileConnect();

    this->showSentenceWidget->setLyrics(_currentFile->lyrics);
    UNoteManager::Instance.setLyrics(_currentFile->lyrics);

    _wydget_timeline->setBpm(_currentFile->lyrics->getBpm());
    _wydget_timeline->setGap(_currentFile->lyrics->getGap());


    _newSongBrowse = new UNewSongForm_Browse(this,_currentFile);
    _newSongBrowse->exec();


    if(!_currentFile->_headMp3.compare(""))
    {
        QMessageBox::warning(this,tr("Attention"),tr("Pensez à indiquer où ce trouve le fichier mp3 (menu Edition >> Edtiter les Entêtes)"));
        return;
    }

    if(!QFile::exists(_currentFile->getMp3Location()))
    {
        QMessageBox::warning(this,tr("Attention"),tr("Le fichier mp3 n'a pas été trouvé."));
        return;
    }

    UAudioManager::Instance.setSource(_currentFile->getMp3Location());
      QMessageBox::information(this,tr("Prochaine étape"),

tr("Maintenant Votre musique va se lancez et vous devrez appuyer la barre "
   "d'espace a chaque nouvelle note. Nous vous conseillons de regarder un exemple"
   " sur le site http://www.ultratools.org pour bien comprendre comment cela "
   "fonctionne.\n\n\nUtilisez votre feeling et appuyer sur la bar d'espace un peu "
   "comme si vous chantiez. Si vous avez l'impression d'avoir ratez une partie ne "
   "vous arretez pas et essayer de rester calé, cela vous fera gagner beaucoup de "
   "temps lors de l'édition.\n c'est partie."));


     play();
     if(!_spaceNote->isRecording())
     {
         recordAction->trigger();
     }

}

void UEditorWindow::fileConnect()
{
    if(!_currentFile) return;


    connect(_currentFile,SIGNAL(bpmChanged(int)),this,SLOT(bpmChanged(int)));
    connect(_currentFile,SIGNAL(gapChanged(float)),this,SLOT(gapChanged(float)));
    connect(_currentFile,SIGNAL(hasBeenModified(bool)),this,SLOT(onFileModified(bool)));
    connect(ui->actionDoublePrecision,SIGNAL(triggered()),_currentFile,SLOT(doublePrecision()));
}
void UEditorWindow::fileDisconnect()
{
    if(!_currentFile) return;

    disconnect(_currentFile,SIGNAL(bpmChanged(int)),this,SLOT(bpmChanged(int)));
    disconnect(_currentFile,SIGNAL(gapChanged(float)),this,SLOT(gapChanged(float)));
    disconnect(_currentFile,SIGNAL(hasBeenModified(bool)),this,SLOT(onFileModified(bool)));
    disconnect(ui->actionDoublePrecision,SIGNAL(triggered()),_currentFile,SLOT(doublePrecision()));
}

void UEditorWindow::hoverAction(QAction *a)
{
    //QMessageBox::information(NULL,"lol",a->statusTip());
    this->statusBar()->showMessage("a"+a->statusTip(),10000);
}

void UEditorWindow::dropEvent(QDropEvent *event)
{

    if (event->mimeData()->urls().isEmpty())
        return;


        QUrl urlfile = event->mimeData()->urls().first();
        QString file = urlfile.toLocalFile();
        QFileInfo fileInfo(file);

        if(fileInfo.suffix().toLower() == "txt"){

            openFile(file);

        }

}
void UEditorWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void UEditorWindow::centerView()
{
    int time = UAudioManager::Instance.currentTime();
    if(ui->hScroll->value()>_currentFile->lyrics->timeToBeat(time) || ui->hScroll->value() + showSentenceWidget->getHScale()<_currentFile->lyrics->timeToBeat(time))
    {
        changeHScroll(max(0.0,_currentFile->lyrics->timeToBeat(time)-showSentenceWidget->getHScale()/2));
        //QMessageBox::warning(NULL,"","ok");
    }
}


void UEditorWindow::displayHelpScreen()
{
    UDialogHelp f(NULL);
    f.exec();
}
void UEditorWindow::onConnected()
{
    qDebug()<<"onConnected";
    if(!ui)
    {
        return;
    }
    QMenu * m = new QMenu(tr("Envoyer une suggestion/remarque rapide"),NULL);
    QList<QAction*> l;
    l.append(ui->actionEnvoyer_une_suggestion_remarque_rapide);
    m->addActions(l);
    ui->menubar->addMenu(m);
 // ui->menuEnvoyer_une_suggestion_remarque_rapide->setEnabled(true);
}
void UEditorWindow::displayFeedback()
{
   // QMessageBox::information(NULL,"","lol");
    UDialogFeedback f(NULL);
    f.exec();
}
void UEditorWindow::openTiming(void)
{
    UDialog_timing * edit = new UDialog_timing(this,_currentFile);
    edit->show();

}
void UEditorWindow::onFileModified(bool k)
{
       if(k)
            setWindowTitle(USetting::Instance.getWindowTitle(this->windowTitle()," - "+_currentFile->getFileName().section('/',-1,-1)+"*"));
        else
            setWindowTitle(USetting::Instance.getWindowTitle(this->windowTitle()," - "+_currentFile->getFileName().section('/',-1,-1)));


        showSentenceWidget->update();
}
