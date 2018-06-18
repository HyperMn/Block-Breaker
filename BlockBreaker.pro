#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T13:22:19
#
#-------------------------------------------------

RC_FILE = icon.rc

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlockBreaker
TEMPLATE = app


SOURCES += main.cpp\
    abstractball.cpp \
    normalball.cpp \
    bordersquare.cpp \
    abstractplank.cpp \
    normalplank.cpp \
    gamescene.cpp \
    abstractbrick.cpp \
    normalbrick.cpp \
    ballfactory.cpp \
    fastball.cpp \
    abstractsurprisingbrick.cpp \
    gift.cpp \
    addballbrick.cpp \
    forbiddensquare.cpp \
    shrinkplankbrick.cpp \
    brickfactory.cpp \
    shorterplank.cpp \
    plankfactory.cpp \
    stretchplankbrick.cpp \
    longerplank.cpp \
    slowball.cpp \
    hardbrick.cpp \
    harderbrick.cpp \
    hardestbrick.cpp \
    accelerateplankbrick.cpp \
    decelerateplankbrick.cpp \
    bigball.cpp \
    smallball.cpp \
    superball.cpp \
    fastplank.cpp \
    slowplank.cpp \
    gamewindow.cpp \

HEADERS  += \
    abstractball.h \
    normalball.h \
    bordersquare.h \
    abstractplank.h \
    normalplank.h \
    gamescene.h \
    abstractbrick.h \
    normalbrick.h \
    ballfactory.h \
    fastball.h \
    abstractsurprisingbrick.h \
    gift.h \
    addballbrick.h \
    forbiddensquare.h \
    shrinkplankbrick.h \
    brickfactory.h \
    shorterplank.h \
    plankfactory.h \
    stretchplankbrick.h \
    longerplank.h \
    slowball.h \
    hardbrick.h \
    harderbrick.h \
    hardestbrick.h \
    accelerateplankbrick.h \
    decelerateplankbrick.h \
    bigball.h \
    smallball.h \
    superball.h \
    fastplank.h \
    slowplank.h \
    gamewindow.h \
    gamelevel.h \

RESOURCES += \
    image.qrc \
    music.qrc \
    icon.qrc

FORMS += \
    gamewindow.ui \

DISTFILES += \
    BlockBreaker.pro.user \
    icon.ico \
    icon.rc

SUBDIRS += \
    BlockBreaker.pro
