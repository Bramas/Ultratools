# -------------------------------------------------
# Project created by QtCreator 2009-09-10T14:23:16
# -------------------------------------------------
QT += core widgets network
TARGET = UltraTools_Editor
TEMPLATE = app
SOURCES += main.cpp \
    editorwindow.cpp \
    uSentence.cpp \
    uWord.cpp \
    uLyrics.cpp \
    uShowSentenceWydget.cpp \
    uShowLines.cpp \
    uFile.cpp \
    uDialog_fileheader.cpp \
    uWydget_timeline.cpp \
    uInputManager.cpp \
    uWydget_lyrics.cpp \
    uSeparateur.cpp \
    uNoteManager.cpp \
    uNewSongForm_Browse.cpp \
    uSpaceNoteGenerator.cpp \
    uSetting.cpp \
    uNewSongForm_Lyrics.cpp \
    uSettingDialog.cpp \
    uCheckUpdate.cpp \
    uAudioManager.cpp \
    uDialogHelp.cpp \
    uDialogFeedback.cpp
HEADERS += editorwindow.h \
    uSentence.h \
    uWord.h \
    uLyrics.h \
    uShowSentenceWydget.h \
    uShowLines.h \
    uFile.h \
    uDialog_fileheader.h \
    uWydget_timeline.h \
    uInputManager.h \
    uWydget_lyrics.h \
    uSeparateur.h \
    uNoteManager.h \
    uNewSongForm_Browse.h \
    uSpaceNoteGenerator.h \
    uSetting.h \
    uNewSongForm_Lyrics.h \
    uSettingDialog.h \
    uCheckUpdate.h \
    uAudioManager.h \
    uDialogHelp.h \
    uDialogFeedback.h
FORMS += editorwindow.ui \
    udialog_fileheader.ui \
    uNewSongForm_Browse.ui \
    uNewSongForm_Lyrics.ui \
    uSettingDialog.ui \
    uDialogHelp.ui \
    uDialogFeedback.ui


RESOURCES = data.qrc \
    Lang.qrc

# CODECFORSRC     = UTF-8
TRANSLATIONS = UltraTools_Editor_fr.ts \
    UltraTools_Editor_en.ts \
    UltraTools_Editor_es.ts
mac { 
    CONFIG += ppc \
        x86
    ICON = icone/icone.icns
}
CONFIG( debug, debug|release ):

# debug
else:

# release
win32:RC_FILE = icone/icone.rc
LIBS += -L/usr/local/lib -lfmodex
