#-------------------------------------------------
#
# Project created by QtCreator 2013-12-13T00:30:09
#
#-------------------------------------------------
#QT       += core

QT       -= gui

TARGET = compilers_lab_02
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

SOURCES +=  main.cpp \
    ctoken.cpp \
    ctokensflow.cpp

HEADERS += \
    ctoken.h \
    parser.h \
    ctokensflow.h
