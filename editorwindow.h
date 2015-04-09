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
   void save(void);
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
    int discardChange(void);
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

 /*   QSlider * hSlider;
    QSlider * vSlider;
    QScrollBar * hScroll;
    QScrollBar * vScroll;*/

};

#endif // MAINWINDOW_H
