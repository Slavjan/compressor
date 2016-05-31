TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    compressfile.cpp \
    decompressfile.cpp \
    stringtable.cpp \
    coder.cpp

HEADERS += \
    compressfile.h \
    decompressfile.h \
    stringtable.h \
    coder.h
