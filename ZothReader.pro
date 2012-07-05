#-------------------------------------------------
#
# Project created by QtCreator 2012-07-05T14:40:41
#
#-------------------------------------------------

QT       += core gui webkit xml

TARGET = ZothReader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    enexport.cpp \
    enexportparser.cpp \
    ennote.cpp \
    enresource.cpp \
    endisplay.cpp \
    encontent.cpp \
    encontentparser.cpp \
    settingsdialog.cpp \
    hellodialog.cpp \
    tools.cpp \
    enview.cpp
    #tests/test_enexport.cpp \
    #tests/test_enexportparser.cpp

HEADERS  += mainwindow.h \
    enexport.h \
    enexportparser.h \
    ennote.h \
    enresource.h \
    endisplay.h \
    encontent.h \
    encontentparser.h \
    settingsdialog.h \
    hellodialog.h \
    tools.h \
    enview.h

RESOURCES += \
    res.qrc