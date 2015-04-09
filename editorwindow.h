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


#include "uCheckUpdate.h"
#include "uDialogHelp.h"
#include "uDialogFeedback.h"

namespace Ui
{
    class EditWindowClass;
}

class UEditorWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent * event) { UInputManager::Instance.keyPressed(event);   };
   void keyReleaseEvent(QKeyEvent * event) { UInputManager::Instance.keyReleased(event);   };
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
   void gapModified();
   void saveAs(void);
   void save(void);
   void newFile(void);
   void tooglePlay(void);
   void newSong(void);
   void updatePlainText(void);
   void centerView(void);
   void onFileModified(bool k);


private slots:
  void stateChanged(Phonon::State newState);
   void tick(qint64 time);
   void aboutToFinish();


public:
    UEditorWindow(QWidget *parent=0);
    ~UEditorWindow();
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

    qint64 _startTime;
    QAction *playAction;
    QAction *pauseAction;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;

    QString _recentFiles;

    Ui::EditWindowClass *ui;

    UFile * _currentFile;

    ShowSentenceWidget * showSentenceWidget;
    ShowLines * showLines;
    UWydget_Timeline * _wydget_timeline;
    UWydget_Lyrics * _wydget_lyrics;

    UNewSongForm_Browse * _newSongBrowse;
    USpaceNoteGenerator * _spaceNote;

    int _lastHSlideValue;
    float _lastHScrollValue;

    QTimer * _autoSaveTimer;

 /*   QSlider * hSlider;
    QSlider * vSlider;
    QScrollBar * hScroll;
    QScrollBar * vScroll;*/

};

#endif // MAINWINDOW_H
