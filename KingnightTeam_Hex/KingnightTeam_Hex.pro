#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T20:19:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KingnightTeam_Hex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chessboard.cpp \
    handle.cpp \
    computer.cpp \
    location.cpp \
    findachannel.cpp \
    play.cpp \
    negativemaxminsearch.cpp \
    move.cpp \
    uctsearch.cpp \
    uctmove.cpp \
    uctnode.cpp \
    alphabetasearch.cpp \
    judgeiswin.cpp \
    findthelongeststepconnection.cpp \
    playchess_start.cpp \
    transform.cpp \
    commonmethod.cpp \
    calculatethemaximumflow.cpp \
    finalalgorithm.cpp

HEADERS  += mainwindow.h \
    chessboard.h \
    handle.h \
    hexdefine.h \
    computer.h \
    location.h \
    findachannel.h \
    play.h \
    negativemaxminsearch.h \
    move.h \
    uctsearch.h \
    uctmove.h \
    uctnode.h \
    alphabetasearch.h \
    judgeiswin.h \
    findthelongeststepconnection.h \
    playchess_start.h \
    transform.h \
    commonmethod.h \
    calculatethemaximumflow.h \
    finalalgorithm.h \
    dfs.h

FORMS    += mainwindow.ui \
    chessboard.ui \
    handle.ui

RESOURCES += \
    image.qrc
