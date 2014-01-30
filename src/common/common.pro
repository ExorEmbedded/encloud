include(../../common.pri)

TEMPLATE = lib

TARGET = common

CONFIG += staticlib

HEADERS += common.h
HEADERS += helpers.h

HEADERS += utils.h
SOURCES += utils.cpp

HEADERS += json.h
SOURCES += json.cpp

contains(CONFIG, qtjson) {
    HEADERS += qtjson.h
    SOURCES += qtjson.cpp
    SOURCES += json-qtjson.cpp
}

# new/default LGPL Json implementation (larger: external package)
contains(CONFIG, qjson) {
    SOURCES += json-qjson.cpp
    LIBS += -lqjson
}
