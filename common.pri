# Config options:
#
#   debug       add debugging symbols
#   noservice   disable service functionality (simple QtCoreApplication)

PKGNAME = Encloud
PKGNAME_LOWER = encloud
ORG = Endian

# only x.x.x.x format allowed, where x is a number
VERSION = 0.1
VERSION_TAG = Wip  # Dev version - comment this for official release!
#VERSION_TAG = Beta  # Beta version - comment this for official releases!

CONFIG += ordered
CONFIG += qtjson  # GPL/self-contained
# TODO
#CONFIG += qjson  # LGPL/external

#
# test config
# 
CONFIG += noservice

#
# Qt settings
# 

QT += core
QT += network


#
# custom compilation macros and flags
# 

DEFINES += ENCLOUD_VERSION=\\\"$$VERSION\\\"
!isEmpty(VERSION_TAG) {
    DEFINES += ENCLOUD_VERSION_TAG=\\\"$$VERSION_TAG\\\"
}
exists(".git") {
    DEFINES += ENCLOUD_REVISION=\\\"$$system(git rev-parse --short HEAD)\\\"
}
DEFINES += ENCLOUD_PKGNAME=\\\"$$PKGNAME\\\"
DEFINES += ENCLOUD_PKGNAME_LOWER=\\\"$$PKGNAME_LOWER\\\"
DEFINES += ENCLOUD_ORG=\\\"$$ORG\\\"

# custom flags
noservice {
    DEFINES += ENCLOUD_DISABLE_SERVICE=1
}
debug {
    QMAKE_CXXFLAGS += -g
}

#
# build settings
# 

SRCBASEDIR = $$PWD

# dependency for common headers, etc
INCLUDEPATH += $$SRCBASEDIR/src/common
DEPENDPATH += $$INCLUDEPATH

# keep build files separate from sources
UI_DIR = build/uics
MOC_DIR = build/mocs
RCC_DIR = build/rcc
OBJECTS_DIR = build/objs
Release:DESTDIR = release
Debug:DESTDIR = debug
