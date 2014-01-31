include(../../common.pri)

TEMPLATE = lib

TARGET = http

CONFIG += staticlib

HEADERS += http.h
SOURCES += http.cpp

HEADERS += server.h
SOURCES += server.cpp

HEADERS += request.h
SOURCES += request.cpp

HEADERS += response.h
SOURCES += response.cpp

HEADERS += headers.h
SOURCES += headers.cpp

HEADERS += abstracthandler.h
