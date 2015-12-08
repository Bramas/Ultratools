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





#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#ifdef QT_NETWORK_LIB
#include "uCheckUpdate.h"
#include "uDialogFeedback.h"
#endif
#include "uDialogHelp.h"
#include "uInputManager.h"
#include "uFile.h"
#include "uNewSongForm_Lyrics.h"

class ShowSentenceWidget;
class ShowLines;
class UWydget_Timeline;
class UWydget_Lyrics;
class Recorder;
class QScrollBar;
class WidgetSongData;
class QMessageBox;
class RichHScrollBar;
class QAbstractSlider;
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
   void changeHSlider(int s = 0);
   void onUpdateVScrollAndScale(int s = 0);
   void changeHScroll(int s =0);
   void openFile(QString fileName="");
   void openLastFile(void);
   void openTiming(void);
   void readLastFile(void);
   void writeSettings();
   void setSpeed(int);
   void bpmChanged(int);
   void gapChanged(double);
   void changeSeek(quint64);
   void onSongLengthChanged(int);
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
    QAbstractSlider *horizontalScrollBar();
    UFile * getFile() { return _currentFile; }

private:
    void fileConnect(void);
    void fileDisconnect(void);
    void adaptNewFile(void);
    void setupUi(void);
    void setupAudio(void);
    bool fileCanBeClosed(void);
    Ui::EditWindowClass *ui;


    bool _playViolon;
    bool _isPlaying;
    RichHScrollBar * _hScroll;
    WidgetSongData * _widgetSongData;
    QMessageBox * _confirmCloseMessageBox;

    qint64 _startTime;
    QAction *playAction;
    QAction *pauseAction;
    QAction *recordAction;
    QAction * _redoAction;
    QAction * _undoAction;
    QString _recentFiles;


    UFile * _currentFile;

    ShowSentenceWidget * showSentenceWidget;
    ShowLines * showLines;
    UWydget_Timeline * _wydget_timeline;
    UWydget_Lyrics * _wydget_lyrics;

    UNewSongForm_Browse * _newSongBrowse;
    Recorder * _spaceNote;

    QTimer * _autoSaveTimer;
    bool _spaceNoteGeneration;


};

#endif // MAINWINDOW_H
