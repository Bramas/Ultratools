# -------------------------------------------------
# Project created by QtCreator 2009-09-10T14:23:16
# -------------------------------------------------
QT += core widgets network
CONFIG += c++11
TARGET = "UltraTools Editor"
TEMPLATE = app

VERSION = \\\"'1.7'\\\"
DEFINES += "VERSION=$${VERSION}"

DEFINES += "VERSION_HEX=0x0107"

SOURCES += main.cpp \
    editorwindow.cpp \
    timebase.cpp \
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
    uAudioManager.cpp \
    uDialogHelp.cpp \
    uRecorder.cpp \
    uDialog_timing.cpp \
    uDialogAbout.cpp \
    uWidgetSongData.cpp \
    undocommands.cpp \
    wordselection.cpp \
    richhscrollbar.cpp
HEADERS += editorwindow.h \
    timebase.h \
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
    uAudioManager.h \
    uDialogHelp.h \
    uRecorder.h \
    uDialog_timing.h \
    uDialogAbout.h \
    uWidgetSongData.h \
    undocommands.h \
    wordselection.h \
    richhscrollbar.h
FORMS += editorwindow.ui \
    udialog_fileheader.ui \
    uNewSongForm_Browse.ui \
    uNewSongForm_Lyrics.ui \
    uSettingDialog.ui \
    uDialogHelp.ui \
    uDialog_timing.ui \
    uDialogAbout.ui

contains(QT, network) {
    SOURCES += uCheckUpdate.cpp \
        uDialogFeedback.cpp
    HEADERS += uCheckUpdate.h \
        uDialogFeedback.h
    FORMS += uDialogFeedback.ui
}

RESOURCES = data.qrc \
    Lang.qrc


linux{
    INCLUDEPATH += /usr/local/include/fmod
    TARGET = ultratools-editor

    linux-g++-64 {
        CONFIG(release, debug|release):LIBS += -lfmodex64
        CONFIG(debug, debug|release):LIBS += -lfmodexL64
    } else {
        CONFIG(release, debug|release):LIBS += -lfmodex
        CONFIG(debug, debug|release):LIBS += -lfmodexL
    }

    OS_STRING = \\\"'Linux'\\\"

    isEmpty(PREFIX):PREFIX = "/usr/local"
    target.path = $$PREFIX/bin
    notes.path = $$PREFIX/share/Ultratools/Editor
    notes.files = violon
    INSTALLS += target notes
}

# CODECFORSRC     = UTF-8
TRANSLATIONS = UltraTools_Editor_fr.ts \
    UltraTools_Editor_en.ts \
    UltraTools_Editor_es.ts

for(ts, TRANSLATIONS) {
    qm = $$ts
    qm ~= s/\.ts$/.qm/
    !exists($$qm) {
        system($$[QT_INSTALL_BINS]/lrelease $$ts)
    }
}

QMAKE_EXTRA_COMPILERS += lrelease
lrelease.input = TRANSLATIONS
lrelease.output = ${QMAKE_FILE_BASE}.qm
lrelease.commands = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_BASE}.qm
lrelease.CONFIG += no_link target_predeps


mac{
    ICON = ultratools.icns
    CONFIG += ppc \
        x86
    LIBS += -l/usr/local/lib/fmodex
    INCLUDEPATH += /usr/local/include/fmod
    OS_STRING = \\\"'Mac'\\\"
}
win32{


    INCLUDEPATH += C:\FMODEx\api\inc
    RC_FILE = icone/icone.rc
    LIBS += -LC:\FMODEx\api\lib -lfmodex
    OS_STRING = \\\"'Windows'\\\"
}
DEFINES += "OS_STRING=$${OS_STRING}"

load(configure)
qtCompileTest(portmidi) {
    LIBS += -lportmidi
    DEFINES += USE_MIDI
    SOURCES += uMidiManager.cpp
    HEADERS += uMidiManager.h
}

DISTFILES += \
    qt_licence.txt \
    ../.travis.yml
