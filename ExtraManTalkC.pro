#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T20:57:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0.0.0
QMAKE_TARGET_COMPANY = Mandarin Studio
QMAKE_TARGET_PRODUCT = Mandarin Chat
QMAKE_TARGET_DESCRIPTION = TCP Chat
QMAKE_TARGET_COPYRIGHT = MS

TARGET = ExtraManTalkC
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp

HEADERS  += client.h

FORMS    += client.ui

RC_FILE = logo.rc
