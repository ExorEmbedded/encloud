# Config options:
#
# [ General ]
#
#   endian      Endian build - used for local install paths
#   exor        Exor build - used for local install paths
#   debug       compile libraries with debugging symbols
#
# [ Modes ]
# 
# Note: mode selection has implications on behaviour and packaging!
#
#   modeqic     Endian 4i Connect / Exor JMConnect mode
#   modeece     Endian Cloud Enabler mode
#   modesece    Software Endian Cloud Enabler mode
#
# [ Feature Disabling ]
#
#   noservice   disable service functionality (simple QtCoreApplication)
#
#
# [ About definitions ]
#   about       use brand info from about dll, instead of using default for major brand (exor/endian)


# Local configuration overrides. Sample content:
#     CONFIG += endian
#     CONFIG += modeqic
LOCALCONFIG=$$(HOME)/.qmake.pri
exists($${LOCALCONFIG}): include($${LOCALCONFIG})


#
# global defs
#
PKGNAME = Encloud
PKGNAME_LOWER = encloud

PRODUCT_4IC="4iConnect"
PRODUCT_JMC="JMConnect"
PRODUCT_ENCLOUD="Encloud"
PRODUCT_SECE="SECE"  # FIXME

# only x.x.x.x format allowed, where x is a number
VERSION = 0.1.1
#VERSION_TAG = Wip  # Dev version - comment this for official release!
VERSION_TAG = Beta  # Beta version - comment this for official releases!

endian {
    ORG = Endian
} else:exor {
    ORG = Exor
} else {
    error("organisation must be defined (CONFIG += endian|exor)!")
}

unix:CONFIG -= debug
CONFIG += ordered
CONFIG += qtjson  # GPL/self-contained
# TODO
#CONFIG += qjson  # LGPL/external

#
# test different configurations
# 
#CONFIG += noservice

#
# Qt settings
# 

QT += core
QT += network
QT -= gui

# suffix for libraries
win32 {
    CONFIG(debug,debug|release) {
        DBG_SUFFIX = d
    }
} else {
    DBG_SUFFIX =
}

#
# custom compilation macros and flags
# 

modeqic {
    endian {
        PROGDIR=$$(ProgramFiles)/$${ORG}/$${PRODUCT_4IC}
        DEFINES += ENCLOUD_PRODUCT=\\\"$${PRODUCT_4IC}\\\"
    } else {
        PROGDIR=$$(ProgramFiles)/$${ORG}/$${PRODUCT_JMC}
        DEFINES += ENCLOUD_PRODUCT=\\\"$${PRODUCT_JMC}\\\"
    }
} else:modeece {
    PROGDIR=$$(ProgramFiles)/$${ORG}/$${PRODUCT_ENCLOUD}
    DEFINES += ENCLOUD_PRODUCT=\\\"$${PRODUCT_ENCLOUD}\\\"
} else:modesece {
    PROGDIR=$$(ProgramFiles)/$${ORG}/$${PRODUCT_SECE}
    DEFINES += ENCLOUD_PRODUCT=\\\"$${PRODUCT_SECE}\\\"
} else {
    error("a mode must be defined (CONFIG += modeqic|modeece|modesece)!")
}

DEFINES += ENCLOUD_VERSION=\\\"$$VERSION\\\"
!isEmpty(VERSION_TAG) {
    DEFINES += ENCLOUD_VERSION_TAG=\\\"$$VERSION_TAG\\\"
}
exists(".git") {
    REVISION=$$system(git rev-parse --short HEAD)
    DEFINES += ENCLOUD_REVISION=\\\"$${REVISION}\\\"
} else {
    DEFINES += ENCLOUD_REVISION=\\\"$$cat(.revision)\\\"
}
DEFINES += ENCLOUD_PKGNAME=\\\"$$PKGNAME\\\"
DEFINES += ENCLOUD_PKGNAME_LOWER=\\\"$$PKGNAME_LOWER\\\"
DEFINES += ENCLOUD_ORG=\\\"$$ORG\\\"

# custom flags
noservice {
    DEFINES += ENCLOUD_DISABLE_SERVICE=1
}
debug:unix {
    QMAKE_CXXFLAGS += -g
}

about       { DEFINES += LIBENCLOUD_USE_ABOUT }

#
# build settings
# 

SRCBASEDIR = $$PWD

# dependency for common headers, etc
INCLUDEPATH += $$SRCBASEDIR/src/common
DEPENDPATH += $$INCLUDEPATH

# install dirs
windows {  # used only for dev - installer handles positioning on target
           # and runtime paths are defined in src/common/defaults.h
    INSTALLDIR = "$${PROGDIR}"
    BINDIR = "$${INSTALLDIR}/bin"
} else {  # used for dev and production
    INSTALLDIR = /usr/local
    BINDIR = /usr/sbin
}

#message("BINDIR: $$BINDIR")

# keep build files separate from sources
UI_DIR = build/uics
MOC_DIR = build/mocs
RCC_DIR = build/rcc
OBJECTS_DIR = build/objs
win32 {
    Release:DESTDIR = release
    Debug:DESTDIR = debug
} else {
    DESTDIR =
}
