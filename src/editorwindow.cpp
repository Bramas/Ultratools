/* Copyright (c) 2015 Quentin Bramas
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */



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
#include "richhscrollbar.h"
#include <cmath>
#include <QUrl>
#include <QMimeData>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QSpinBox>

#define USEMEMLOAD
#define USEFMOD TRUE


#define WINDOW_TITLE "Ultratools Editor"
#define URL_VERSION "http://ultratools.org/version.php?soft=editor"

UEditorWindow::UEditorWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::EditWindowClass),
      _confirmCloseMessageBox(0),
      _redoAction(0),
      _undoAction(0),
      _spaceNoteGeneration(false)
{

    this->setFocusPolicy(Qt::StrongFocus);
_startTime=0;
    _playViolon = false;
    _currentFile = NULL;
    _isPlaying=false;
setAcceptDrops(true);
USetting::Instance.init();

#ifdef QT_MODULE_NETWORK
UCheckUpdate * check = new UCheckUpdate(QUrl(URL_VERSION));
connect(check,SIGNAL(connected()),this,SLOT(onConnected()));
#endif


    setupAudio();
    setupUi();

            _currentFile = new UFile(this);// "songs/arkol - vingt ans/Arkol - vingt ans.txt");

            fileConnect();

            this->showSentenceWidget->setHScroll(0);

        connect(ui->vScroll,SIGNAL(valueChanged(int)),this,SLOT(onUpdateVScrollAndScale(int)));
        connect(ui->vSlider,SIGNAL(valueChanged(int)),this,SLOT(onUpdateVScrollAndScale(int)));
        connect(ui->vScroll,SIGNAL(sliderPressed()),this,SLOT(onUpdateVScrollAndScale()));
        connect(ui->vSlider,SIGNAL(sliderPressed()),this,SLOT(onUpdateVScrollAndScale()));
        //connect(ui->vScroll,SIGNAL(actionTriggered(int)),this,SLOT(changeVScroll(int)));

        connect(_hScroll,SIGNAL(valueChanged(int)),this,SLOT(changeHScroll(int)));
        //connect(ui->hSlider,SIGNAL(valueChanged(int)),this,SLOT(changeHSlider(int)));
        connect(_hScroll,SIGNAL(sliderPressed()),this,SLOT(changeHScroll()));
        //connect(ui->hSlider,SIGNAL(sliderPressed()),this,SLOT(changeHSlider()));
        connect(_hScroll,SIGNAL(pageStepChanged(int)),this,SLOT(changeHSlider(int)));





        connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));

        connect(ui->actionEditHeaders,SIGNAL(triggered()),this,SLOT(editHeader()));
        connect(ui->actionApplyOffset,SIGNAL(triggered()),this,SLOT(openTiming()));
        connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
        connect(playAction, SIGNAL(triggered()), this, SLOT(tooglePlay()));
        connect(pauseAction, SIGNAL(triggered()), this, SLOT(tooglePlay()));
        connect(recordAction, SIGNAL(triggered()), this, SLOT(toggleRecord()));
        connect(showSentenceWidget,SIGNAL(haveToStop()), this, SLOT(tooglePlay()));

        connect(this->ui->offsetSpinBox, SIGNAL(valueChanged(int)), showSentenceWidget, SLOT(setPreviousDisplayed(int)));
        this->ui->offsetSpinBox->setValue(2);
        connect(ui->actionSetNormalNote,SIGNAL(triggered()),showSentenceWidget, SLOT(setNormal()));
        connect(ui->actionSetFreeNote,SIGNAL(triggered()),showSentenceWidget, SLOT(setFree()));
        connect(ui->actionSetGoldNote,SIGNAL(triggered()),showSentenceWidget, SLOT(setGold()));

        connect(ui->actionMergeNotes,SIGNAL(triggered()),showSentenceWidget, SLOT(fusion()));
        connect(ui->actionSplitNote,SIGNAL(triggered()),showSentenceWidget, SLOT(split()));

        connect(ui->actionAddNote,SIGNAL(triggered()),showSentenceWidget, SLOT(nextClickAddNote()));
        connect(ui->actionAddSeparator,SIGNAL(triggered()),showSentenceWidget, SLOT(nextClickAddSeparator()));

        connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
        connect(ui->actionSaveAs,SIGNAL(triggered()),this,SLOT(saveAs()));
        connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newSong()));

        connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));

        connect(&UInputManager::Instance,SIGNAL(spacePressEvent(void)),this,SLOT(tooglePlay()));

        connect(_wydget_timeline, SIGNAL(gapModified(double)),this, SLOT(gapModified(double)));

         connect(ui->actionDeleteNote,SIGNAL(triggered()),showSentenceWidget,SLOT(deleteNotes()));

        connect(ui->actionPreferences,SIGNAL(triggered()),&USetting::Instance,SLOT(showDialog()));

        connect(ui->actionMorphe,SIGNAL(triggered()),showSentenceWidget,SLOT(calquer()));


        connect(ui->actionLockTimings,SIGNAL(toggled(bool)),showSentenceWidget,SLOT(lockTime(bool)));

        connect(ui->actionCenter,SIGNAL(triggered()),this,SLOT(centerView()));

        connect(ui->actionHelp,SIGNAL(triggered()),this,SLOT(displayHelpScreen()));
        connect(ui->actionSendFeedback,SIGNAL(triggered()),this,SLOT(displayFeedback()));




        onUpdateVScrollAndScale();
        changeHScroll(0);


       // _currentFile = new UFile(this);
        this->showSentenceWidget->setLyrics(_currentFile->lyrics);
        _wydget_lyrics->setWidgetWords(showSentenceWidget);


        _undoAction = _currentFile->lyrics->history().createUndoAction(this->ui->menuEdit, tr("Annuler "));
        _undoAction->setShortcut(QKeySequence::Undo);
        _undoAction->setIcon(QIcon(":/images/undo.png"));
        this->ui->menuEdit->addAction(_undoAction);
        this->ui->toolBar->insertAction(this->ui->actionSetNormalNote, _undoAction);

        _redoAction = _currentFile->lyrics->history().createRedoAction(this->ui->menuEdit, tr("Refaire "));
        _redoAction->setShortcut(QKeySequence::Redo);
        _redoAction->setIcon(QIcon(":/images/redo.png"));
        this->ui->menuEdit->addAction(_redoAction);
        this->ui->toolBar->insertAction(this->ui->actionSetNormalNote, _redoAction);


        readLastFile();

        connect(ui->actionRecentFiles,SIGNAL(triggered()),this,SLOT(openLastFile()));



        readSettings();

        _spaceNote = new Recorder(this->showSentenceWidget);

        _autoSaveTimer = new QTimer(this);
          connect(_autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));

          adaptNewFile();


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
        ui->menuFile->insertAction(ui->actionRecentFiles, a);
    }
    ui->menuFile->removeAction(ui->actionRecentFiles);
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
bool UEditorWindow::fileCanBeClosed()
{
    if(!_currentFile || !_currentFile->isModified())
    {
        return true;
    }

    QString insertedFilename = "";
    if(!_currentFile->getFileName().isEmpty())
    {
        insertedFilename = " \""+QFileInfo(_currentFile->getFileName()).baseName()+"\"";
    }
    if(!_confirmCloseMessageBox)
    {
        _confirmCloseMessageBox = new QMessageBox(trUtf8("Continuer?"),
                                              trUtf8("Le fichier%1 a été modifié.").arg(insertedFilename) + "\n" +
          trUtf8("Voullez-vous sauvegarder les changements?"),//Do you want to save your changes?"),
            QMessageBox::Warning,
            QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::No,
            QMessageBox::Cancel | QMessageBox::Escape,
            this, Qt::Sheet);
        _confirmCloseMessageBox->setButtonText(QMessageBox::Yes,
              _currentFile->getFileName().isEmpty() ? trUtf8("Sauvegarder")+"..." : trUtf8("Sauvegarder"));
        _confirmCloseMessageBox->setButtonText(QMessageBox::No,
            trUtf8("Ne pas sauvegarder"));
        _confirmCloseMessageBox->setButtonText(QMessageBox::Cancel,
            trUtf8("Annuler"));
    }

    int i = _confirmCloseMessageBox->exec();

    if(i == QMessageBox::Cancel)
    {
        return false;
    }
    else
    {
        if(i == QMessageBox::Yes)
        {
            if(!this->save())
            {
                return false;
            }
        }
    }
    return true;
}

void UEditorWindow::openFile(QString fileName)
{

    if(!fileCanBeClosed())
    {
        return;
    }

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
    UAudioManager::Instance.clear();

    this->showSentenceWidget->setLyrics(_currentFile->lyrics);
    this->_hScroll->setLyrics(_currentFile->lyrics);
    UNoteManager::Instance.setLyrics(_currentFile->lyrics);

    if(_undoAction) {
        _undoAction->deleteLater();
    }
    _undoAction = _currentFile->lyrics->history().createUndoAction(this->ui->menuEdit, tr("Annuler "));
    _undoAction->setShortcut(QKeySequence::Undo);
    _undoAction->setIcon(QIcon(":/images/undo.png"));
    this->ui->menuEdit->addAction(_undoAction);
    this->ui->toolBar->insertAction(this->ui->actionSetNormalNote, _undoAction);

    if(_redoAction) {
        _redoAction->deleteLater();
    }
    _redoAction = _currentFile->lyrics->history().createRedoAction(this->ui->menuEdit, tr("Refaire "));
    _redoAction->setShortcut(QKeySequence::Redo);
    _redoAction->setIcon(QIcon(":/images/redo.png"));
    this->ui->menuEdit->addAction(_redoAction);
    this->ui->toolBar->insertAction(this->ui->actionSetNormalNote, _redoAction);



    _wydget_timeline->setBpm(_currentFile->lyrics->getBpm());
    _wydget_timeline->setGap(_currentFile->lyrics->getGap());

    _wydget_lyrics->setWidgetWords(showSentenceWidget);

    _autoSaveTimer->start(USetting::Instance.getAutoSaveInterval()*60000);

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
            UAudioManager::Instance.clear();
            QMessageBox::warning(this,tr("Attention"),tr("Il y a eu un problème lors de la lecture du fichier son")+" : "+fileName.replace('\\','/').section('/',0,-2)+"/"+_currentFile->_headMp3);
        }
    }
    adaptNewFile();

 }

void UEditorWindow::adaptNewFile()
{
    if(UAudioManager::Instance.length() > 0)
    {
        quint32 l = UAudioManager::Instance.length();
        ui->spinBoxMinute->setValue(l/60000);
        ui->spinBoxSecond->setValue((l/1000) % 60000);
        _hScroll->setTotalMaximum(_currentFile->lyrics->timeToBeat(l));
    }
    else
    {
        ui->spinBoxMinute->setValue(4);
        ui->spinBoxSecond->setValue(0);
        _hScroll->setTotalMaximum(_currentFile->lyrics->timeToBeat(4*60*1000));
    }

    if(_currentFile->lyrics->words().isEmpty())
    {
        return;
    }

    //_hScroll->setMaximum(_currentFile->getMax()+_currentFile->lyrics->timeToBeat(_currentFile->lyrics->getGap()));


    UNoteManager::Instance.setMaxPitch(_currentFile->lyrics->getPitchMax());

    //ui->vScroll->setRange((245-_currentFile->lyrics->getPitchMax()),(255-_currentFile->lyrics->getPitchMin()));


/*
    if((_currentFile->lyrics->getPitchMin()+_currentFile->lyrics->getPitchMax())/2+20>_currentFile->lyrics->getPitchMax())
    {
         ui->vScroll->setValue(255-_currentFile->lyrics->getPitchMax());
    }
    else
    {
         ui->vScroll->setValue((235-(_currentFile->lyrics->getPitchMin()+_currentFile->lyrics->getPitchMax())/2));
     }
     */
    onUpdateVScrollAndScale();


    this->changeHScroll((_currentFile->lyrics->getGap()>2000?_currentFile->lyrics->getGap()-2000:0)*_currentFile->lyrics->getBpm()/15000.0);
      _hScroll->setValue((_currentFile->lyrics->getGap()>2000?_currentFile->lyrics->getGap()-2000:0)*_currentFile->lyrics->getBpm()/15000.0);

      onFileModified(false);
}

void UEditorWindow::changeHSlider(int s)
{
    //s = ui->hSlider->value();
    //_hScroll->setPageStep(exp(ui->hSlider->value()/100.0));
   this->showSentenceWidget->setHScale(s);
   _widgetSongData->setHScale(s);

    //_wydget_timeline->setMin(_hScroll->value());
    //_wydget_timeline->setMax(exp(((double)ui->hSlider->value())/100.0) + _hScroll->value());
    _wydget_timeline->setMax(s + _hScroll->value());
    _wydget_lyrics->onScroll();
}

QScrollBar * UEditorWindow::verticalScrollBar()
{
    return this->ui->vScroll;
}
QAbstractSlider * UEditorWindow::horizontalScrollBar()
{
    return this->_hScroll;
}

void UEditorWindow::onUpdateVScrollAndScale(int /*s*/)
{
    // s is now the minimum pitch visible in the editor
    double vScroll = 70 - ui->vScroll->value()/10.0;

    // slider value is an integer so this gives more precision
    qreal vScale = ui->vSlider->value()/10.0;

    this->showSentenceWidget->setVScroll(vScroll);
    this->showSentenceWidget->setVScale(vScale);
    this->showLines->setMin(vScroll);
    this->showLines->setMax(vScroll+vScale);

}
void UEditorWindow::changeHScroll(int s)
{
    s = _hScroll->value();

_widgetSongData->setHScroll(s);
this->showSentenceWidget->setHScroll(s);

//_wydget_timeline->setMin(s);
//_wydget_timeline->setMax(exp(((double)ui->hSlider->value())/100.0) + s);
_wydget_timeline->update();
_wydget_lyrics->onScroll();

}

void UEditorWindow::setSpeed(int n)
{
    n -= 24;
    UNoteManager::Instance.changePitch(n);
    UAudioManager::Instance.changeSpeed(pow(2, n / 12.0));
}

void UEditorWindow::bpmChanged(int n)
{
    _wydget_timeline->setBpm(n);
    showSentenceWidget->updateGap();
}
void UEditorWindow::gapChanged(double n)
{

    _wydget_timeline->setGap(n);
    showSentenceWidget->updateGap();
}

void UEditorWindow::setupUi()
{

    ui->setupUi(this);
    _hScroll = new RichHScrollBar();
       // QScrollArea *sa = new QScrollArea( ui->tab );

        showLines = new  ShowLines();
        showSentenceWidget = new ShowSentenceWidget(this);
        _wydget_timeline = new UWydget_Timeline(this);
        _wydget_timeline->setWidgetSentence(this->showSentenceWidget);
        _wydget_lyrics = new UWydget_Lyrics();


   // hSlider=new QSlider(Qt::Horizontal,this);
    //ui->hSlider->setRange((log(30)*100.0),(log(10000)*100.0));// 30 beats to 10000 beats
    //ui->hSlider->setValue((log(100)*100.0));
    _hScroll->setPageStep(100);

    //vSlider=new QSlider(Qt::Vertical,this);
    ui->vSlider->setRange(120,500);
    ui->vSlider->setValue(290);


    _widgetSongData = new WidgetSongData(this);
    _widgetSongData->setWidgetSentence(this->showSentenceWidget);
    UAudioManager::Instance.setWidgetSongData(_widgetSongData);

    _hScroll->setRange(0,999);
    ui->vScroll->setRange(0,710);
    ui->vScroll->setValue(710);


        ui->tabEditeurLayMain->setColumnMinimumWidth(0,70);// the minimal width to display the showline wydget
        ui->tabEditeurLayMain->setRowMinimumHeight(1,30);// the minimal height to display the timeline wydget
        ui->tabEditeurLayMain->addWidget(_wydget_timeline,1,1);
        ui->tabEditeurLayMain->addWidget(showLines,2,0);
        ui->tabEditeurLayMain->addWidget(showSentenceWidget,2,1);
        ui->tabEditeurLayMain->addWidget(_hScroll,3,1);
        ui->tabEditeurLayMain->addWidget(_widgetSongData,0,1);
        ui->mainHorizontalLayout->addWidget(_wydget_lyrics);
        //ui->tabEditeurLayMain->setRowMinimumHeight(2,40);
        //ui->tabEditeurLayMain->setColumnMinimumWidth(4,100);

     //ui->tabEditeurLayMain->addWidget(_hScroll,1,1);
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
        connect( ui->Slider_MusiqueVolume, SIGNAL(valueChanged(int)), &UAudioManager::Instance, SLOT(changeVolume(int)));
        ui->Slider_NoteVolume->setRange(0,100);
        ui->Slider_NoteVolume->setValue(100);
        connect( ui->Slider_NoteVolume, SIGNAL(valueChanged(int)), &UNoteManager::Instance, SLOT(setVolume(int)));
        ui->Slider_NoteVolume->setRange(0,48);
        ui->Slider_NoteVolume->setValue(24);
        connect( ui->Slider_Speed, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));



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

        connect(showSentenceWidget, &ShowSentenceWidget::autoScroll,[this](int v) { this->_hScroll->setValue(v);} );
        connect(showSentenceWidget, SIGNAL(octaveChanged(int)), showLines, SLOT(setOctaveOffset(int)));


        connect(ui->spinBoxMinute, SIGNAL(valueChanged(int)), this, SLOT(onSongLengthChanged(int)));
        connect(ui->spinBoxSecond, SIGNAL(valueChanged(int)), this, SLOT(onSongLengthChanged(int)));

}

void UEditorWindow::onSongLengthChanged(int v)
{
    _hScroll->setTotalMaximum(_currentFile->lyrics->timeToBeat(
        (ui->spinBoxMinute->value()*60 + ui->spinBoxSecond->value()) * 1000));
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


  //qDebug()<<time<<" : s :"<<_currentFile->beatToMsc(_currentFile->lyrics->getSentences()->first()->getSepAfter()->getTime2())<< "Sentence commençant par "<<s->getWords()->first()->getWord();

  if(UNoteManager::Instance.isPlaying())
  foreach(const Word & w,_currentFile->lyrics->words())
  {
        if(!w.isSeparator() && _currentFile->lyrics->beatToMsc(w.getTime())-20<=time
           && _currentFile->lyrics->beatToMsc(w.getTime()+w.getLength())>time
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

    if(!fileCanBeClosed())
    {
        event->ignore();
        return;
    }

    _currentFile->cleanBAK();

    writeSettings();
    event->accept();

}

void UEditorWindow::saveAs()
{

    QString file = QFileDialog::getSaveFileName(this,tr("Sauvegarder"),"","");
    if(!file.length()) return;

    _currentFile->saveInFile(file);

}

bool UEditorWindow::save()
{
    return _currentFile->saveInFile();
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
    if(!fileCanBeClosed())
    {
        return;
    }

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

    if (!UAudioManager::Instance.setSource(_currentFile->getMp3Location()))
    {
        UAudioManager::Instance.clear();
        QMessageBox::warning(this,tr("Attention"),tr("Il y a eu un problème lors de la lecture du fichier son")+" : "+_currentFile->getMp3Location());
        return;
    }
    adaptNewFile();

      QMessageBox::information(this,tr("Prochaine étape"),

tr("Maintenant Votre musique va se lancez et vous devrez appuyer la touche "
   "Entrée a chaque nouvelle note. Nous vous conseillons de regarder un exemple"
   " sur le site http://www.ultratools.org pour bien comprendre comment cela "
   "fonctionne.\n\n\nUtilisez votre feeling et appuyer sur la touche Entrée un peu "
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
    connect(_currentFile,SIGNAL(gapChanged(double)),this,SLOT(gapChanged(double)));
    connect(_currentFile,SIGNAL(hasBeenModified(bool)),this,SLOT(onFileModified(bool)));
    connect(ui->actionDoublePrecision,SIGNAL(triggered()),_currentFile,SLOT(doublePrecision()));
}
void UEditorWindow::fileDisconnect()
{
    if(!_currentFile) return;

    disconnect(_currentFile,SIGNAL(bpmChanged(int)),this,SLOT(bpmChanged(int)));
    disconnect(_currentFile,SIGNAL(gapChanged(double)),this,SLOT(gapChanged(double)));
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
    if(_hScroll->value()>_currentFile->lyrics->timeToBeat(time) || _hScroll->value() + showSentenceWidget->getHScale()<_currentFile->lyrics->timeToBeat(time))
    {
        this->_hScroll->setValue(max(0.0,_currentFile->lyrics->timeToBeat(time)-showSentenceWidget->getHScale()/2));
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
    //QMenu * m = new QMenu(tr("Envoyer une suggestion/remarque rapide"),NULL);
    //QList<QAction*> l;
    //l.append(ui->actionEnvoyer_une_suggestion_remarque_rapide);
    //m->addActions(l);
    //ui->menubar->addMenu(m);
 // ui->menuEnvoyer_une_suggestion_remarque_rapide->setEnabled(true);
}
void UEditorWindow::displayFeedback()
{
   // QMessageBox::information(NULL,"","lol");
#ifdef QT_MODULE_NETWORK
    UDialogFeedback f(NULL);
    f.exec();
#endif
}
void UEditorWindow::openTiming(void)
{
    UDialog_timing * edit = new UDialog_timing(this,_currentFile);
    edit->show();

}
void UEditorWindow::onFileModified(bool k)
{
    UNoteManager::Instance.setMaxPitch(_currentFile->lyrics->getPitchMax());

       if(k)
            setWindowTitle(USetting::Instance.getWindowTitle(this->windowTitle()," - "+_currentFile->getFileName().section('/',-1,-1)+"*"));
        else
            setWindowTitle(USetting::Instance.getWindowTitle(this->windowTitle()," - "+_currentFile->getFileName().section('/',-1,-1)));


        showSentenceWidget->update();
}
