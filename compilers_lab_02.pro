#-------------------------------------------------
#
# Project created by Ilya Fateev
#
#-------------------------------------------------
QT       -= gui

TARGET = compilers_lab_02
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

# Lexeme scanner sources ##########
# Parser sources ##########
SOURCES += \
    scanner/ccode.cpp \
    scanner/cconstrecognizer.cpp \
    scanner/cwordrecognizer.cpp \
    scanner/cscanner.cpp \
    scanner/ctoken.cpp \
    scanner/ctokensflow.cpp \
    parser/main.cpp \
    parser/cllparser.cpp \
    parser/cproduction.cpp


#Lexeme scanner headers ##########
#Parser headers ##########
HEADERS += \
    scanner/ccode.h \
    scanner/cconstrecognizer.h \
    scanner/cwordrecognizer.h \
    scanner/cscanner.h \
    scanner/ctoken.h \
    scanner/ctokensflow.h \
    parser/parser.h \
    parser/cllparser.h \
    parser/cproduction.h


