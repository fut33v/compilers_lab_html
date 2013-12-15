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
    parser/main.cpp \
    parser/ctoken.cpp \
    parser/ctokensflow.cpp \
    parser/cpredictiveparser.cpp \
    parser/cnonterminals.cpp \
    parser/cllparser.cpp


#Lexeme scanner headers ##########
#Parser headers ##########
HEADERS += \
    scanner/ccode.h \
    scanner/cconstrecognizer.h \
    scanner/cwordrecognizer.h \
    scanner/cscanner.h \
    parser/ctoken.h \
    parser/parser.h \
    parser/ctokensflow.h \
    parser/cpredictiveparser.h \
    parser/cnonterminals.h \
    parser/cllparser.h


