/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Quentin Bramas <quentin@bramas.fr> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Quentin Bramas
 *
 * "LICENCE BEERWARE" (Révision 42):
 * Quentin Bramas <quentin@bramas.fr> a créé ce fichier. Tant que vous conservez cet avertissement,
 * vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
 * que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
 * retour. Quentin Bramas
 * ----------------------------------------------------------------------------
 */





#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uCheckUpdate.h"
#include "uDialogHelp.h"
#include "uDialogFeedback.h"
#include "uInputManager.h"
#include "uFile.h"

class ShowSentenceWidget;
class ShowLines;
class UWydget_Timeline;
class UWydget_Lyrics;
class Recorder;
class QScrollBar;
class WidgetSongData;
class QMessageBox;
namespace Ui
{
    class EditWindowClass;
}

class UEditorWindow : public QMainWindow
{
    Q_OBJECT
protected:
   void keyPressEvent(QKeyEvent * event) { QMainWindow::keyPressEvent(event); UInputManager::Instance.keyPressed(event);   }
   void keyReleaseEvent(QKeyEvent * event) {QMainWindow::keyReleaseEvent(event); UInputManager::Instance.keyReleased(event);   }
   void readSettings();
   void closeEvent(QCloseEvent *event);
   void dropEvent(QDropEvent *);
   void dragEnterEvent(QDragEnterEvent *);


public slots:

   void onConnected(void);
   void displayFeedback(void);
   void displayHelpScreen(void);
   void hoverAction(QAction*);
   void autoSave(void);
    void editHeader(void);
   void changeVSlider(int);
   void changeHSlider(int);
   void changeVScroll(int);
   void changeHScroll(int);
   void openFile(QString fileName="");
   void openLastFile(void);
   void openTiming(void);
   void readLastFile(void);
   void writeSettings();
   void bpmChanged(int);
   void gapChanged(float);
   void changeSeek(quint64);
   void gapModified(double d);
   void saveAs(void);
   bool save(void);
   void newFile(void);
   void tooglePlay(void);
   void play();
   void pause();
   void toggleRecord();
   void newSong(void);
   void centerView(void);
   void onFileModified(bool k);


private slots:
   void tick(quint64 time);
   void aboutToFinish();
   void about();


public:
    UEditorWindow(QWidget *parent=0);
    ~UEditorWindow();


    QScrollBar * verticalScrollBar();
    QScrollBar * horizontalScrollBar();
    UFile * getFile() { return _currentFile; }

private:
    void fileConnect(void);
    void fileDisconnect(void);
    void adaptNewFile(void);
    void setupUi(void);
    void setupAudio(void);
    bool fileCanBeClosed(void);
    bool _playViolon;

    bool _isPlaying;
    bool _spaceNoteGeneration;
    WidgetSongData * _widgetSongData;

    qint64 _startTime;
    QAction *playAction;
    QAction *pauseAction;
    QAction *recordAction;

    QString _recentFiles;

    Ui::EditWindowClass *ui;

    UFile * _currentFile;

    ShowSentenceWidget * showSentenceWidget;
    ShowLines * showLines;
    UWydget_Timeline * _wydget_timeline;
    UWydget_Lyrics * _wydget_lyrics;

    UNewSongForm_Browse * _newSongBrowse;
    Recorder * _spaceNote;

    QTimer * _autoSaveTimer;

    QMessageBox * _confirmCloseMessageBox;

};

#endif // MAINWINDOW_H
