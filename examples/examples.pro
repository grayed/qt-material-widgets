QT += core gui widgets
TEMPLATE = app
CONFIG += c++11
SOURCES = mainwindow.cpp \
    main.cpp \
    avatarsettingseditor.cpp \
    badgesettingseditor.cpp \
    checkboxsettingseditor.cpp \
    fabsettingseditor.cpp \
    raisedbuttonsettingseditor.cpp \
    flatbuttonsettingseditor.cpp \
    iconbuttonsettingseditor.cpp \
    progresssettingseditor.cpp \
    circularprogresssettingseditor.cpp \
    slidersettingseditor.cpp \
    radiobuttonsettingseditor.cpp \
    togglesettingseditor.cpp \
    textfieldsettingseditor.cpp \
    tabssettingseditor.cpp \
    snackbarsettingseditor.cpp \
    dialogsettingseditor.cpp \
    drawersettingseditor.cpp \
    scrollbarsettingseditor.cpp \
    appbarsettingseditor.cpp \
    autocompletesettingseditor.cpp \
    menusettingseditor.cpp
HEADERS = mainwindow.h \
    avatarsettingseditor.h \
    badgesettingseditor.h \
    checkboxsettingseditor.h \
    fabsettingseditor.h \
    raisedbuttonsettingseditor.h \
    flatbuttonsettingseditor.h \
    iconbuttonsettingseditor.h \
    progresssettingseditor.h \
    circularprogresssettingseditor.h \
    slidersettingseditor.h \
    radiobuttonsettingseditor.h \
    togglesettingseditor.h \
    textfieldsettingseditor.h \
    tabssettingseditor.h \
    snackbarsettingseditor.h \
    dialogsettingseditor.h \
    drawersettingseditor.h \
    scrollbarsettingseditor.h \
    appbarsettingseditor.h \
    autocompletesettingseditor.h \
    menusettingseditor.h


win32 {
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/components.lib
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/components.lib
}
win64 {
}
macx {
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
}
unix:!macx{
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
}



INCLUDEPATH += $$top_srcdir/components/
TARGET = examples-exe


RESOURCES += \
    examples.qrc

FORMS += \
    avatarsettingsform.ui \
    badgesettingsform.ui \
    checkboxsettingsform.ui \
    fabsettingsform.ui \
    flatbuttonsettingsform.ui \
    iconbuttonsettingsform.ui \
    progresssettingsform.ui \
    circularprogresssettingsform.ui \
    slidersettingsform.ui \
    snackbarsettingsform.ui \
    radiobuttonsettingsform.ui \
    togglesettingsform.ui \
    textfieldsettingsform.ui \ 
    tabssettingsform.ui \
    dialogsettingsform.ui \
    drawersettingsform.ui \
    scrollbarsettingsform.ui \
    appbarsettingsform.ui
