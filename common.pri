# Config options:
#
# [ General ]
#
#   debug       compile libraries with debugging symbols
#   splitdeps   Dependencies are split into different parts of the system
#               (Default behaviour is to package all dependencies together into a self-contained package/bundle
#               Split mode is used when dependencies are handled as separate packages - e.g. Yocto Encloud services)
#
# [ Modes ]
# 
# Note: mode selection has implications on behaviour and packaging!
#
#   modeqcc     Endian Connect App / Exor JMCloudConnect mode
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

SRCBASEDIR = $$PWD

# Local configuration overrides. Sample content:
#     CONFIG += modeqcc
LOCALCONFIG=$$(HOME)/.qmake.pri
exists($${LOCALCONFIG}): include($${LOCALCONFIG})
LOCALCONFIG=.qmake.pri
exists($${LOCALCONFIG}): include($${LOCALCONFIG})

include($${SRCBASEDIR}/defines.pri)

PKGNAME = Encloud
PKGNAME_LOWER = encloud

# only x.x.x.x format allowed, where x is a number
VERSION = 0.4.0
#VERSION_TAG = Wip  # Dev version - comment this for official release!
#VERSION_TAG = Beta  # Beta version - comment this for official releases!

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

DEFINES += ENCLOUD_PRODUCT=\\\"$${PRODUCT_DIR}\\\"

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

xbrand {
    DEFINES += ENCLOUD_ORG=\\\"\\\"
} else {
    DEFINES += ENCLOUD_ORG=\\\"$$ORG\\\"
}

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

# dependency for common headers, etc
INCLUDEPATH += $$SRCBASEDIR/src/common
DEPENDPATH += $$INCLUDEPATH

# extra dependency paths 
# TODO: QT_INSTALL_PREFIX is native Qt build directory (not valid for cross-compile) => use a staging path
macx {
    INCLUDEPATH += $$[QT_INSTALL_PREFIX]/usr/include
    LIBPATH += $$[QT_INSTALL_PREFIX]/usr/lib
}

# 
# install dirs
# 

# overrides for Connect packaging
CONNECT_DEFINES=$${SRCBASEDIR}/../connectapp/defines.pri
exists($${CONNECT_DEFINES}): include($${CONNECT_DEFINES})

# local overrides
windows {
    CONFDIR = "$${INSTALLDIR}/$${PKGNAME}/etc"
} unix {  # used for dev and production
    splitdeps {
        SBINDIR = /usr/sbin
        CONFDIR = /etc
    }
}

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
