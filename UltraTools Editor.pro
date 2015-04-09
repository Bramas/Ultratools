# -------------------------------------------------
# Project created by QtCreator 2009-09-10T14:23:16
# -------------------------------------------------
QT += core widgets network
TARGET = "UltraTools Editor"
TEMPLATE = app

VERSION = \\\"'1.1.beta'\\\"
DEFINES += "VERSION=$${VERSION}"

SOURCES += main.cpp \
    editorwindow.cpp \
    uWord.cpp \
    uLyrics.cpp \
    uShowSentenceWydget.cpp \
    uShowLines.cpp \
    uFile.cpp \
    uDialog_fileheader.cpp \
    uWydget_timeline.cpp \
    uInputManager.cpp \
    uWydget_lyrics.cpp \
    uNoteManager.cpp \
    uNewSongForm_Browse.cpp \
    uSetting.cpp \
    uNewSongForm_Lyrics.cpp \
    uSettingDialog.cpp \
    uCheckUpdate.cpp \
    uAudioManager.cpp \
    uDialogHelp.cpp \
    uDialogFeedback.cpp \
    uRecorder.cpp \
    uDialog_timing.cpp \
    uDialogAbout.cpp \
    uWidgetSongData.cpp
HEADERS += editorwindow.h \
    uWord.h \
    uLyrics.h \
    uShowSentenceWydget.h \
    uShowLines.h \
    uFile.h \
    uDialog_fileheader.h \
    uWydget_timeline.h \
    uInputManager.h \
    uWydget_lyrics.h \
    uNoteManager.h \
    uNewSongForm_Browse.h \
    uSetting.h \
    uNewSongForm_Lyrics.h \
    uSettingDialog.h \
    uCheckUpdate.h \
    uAudioManager.h \
    uDialogHelp.h \
    uDialogFeedback.h \
    uRecorder.h \
    uDialog_timing.h \
    uDialogAbout.h \
    uWidgetSongData.h
FORMS += editorwindow.ui \
    udialog_fileheader.ui \
    uNewSongForm_Browse.ui \
    uNewSongForm_Lyrics.ui \
    uSettingDialog.ui \
    uDialogHelp.ui \
    uDialogFeedback.ui \
    uDialog_timing.ui \
    uDialogAbout.ui


RESOURCES = data.qrc \
    Lang.qrc

OS_STRING = \\\"'Linux'\\\"


# CODECFORSRC     = UTF-8
TRANSLATIONS = UltraTools_Editor_fr.ts \
    UltraTools_Editor_en.ts \
    UltraTools_Editor_es.ts


mac{
    ICON = ultratools.icns
    CONFIG += ppc \
        x86
    LIBS += -L/usr/local/lib -lfmodex
    OS_STRING = \\\"'Mac'\\\"
}

win32{
    RC_FILE = icone/icone.rc
    LIBS += -LC:\FMODEx\api\lib -lfmodex
    OS_STRING = \\\"'Windows'\\\"
}
DEFINES += "OS_STRING=$${OS_STRING}"
