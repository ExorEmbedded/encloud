include(../../common.pri)

TEMPLATE = app

TARGET = $$PKGNAME_LOWER

SOURCES += main.cpp

#SOURCES += Server.cpp
#HEADERS += Server.h

#SOURCES += Service.cpp
#HEADERS += Service.h

win32 {
    PRE_TARGETDEPS += $$SRCBASEDIR/src/common/common.lib
} else {
    PRE_TARGETDEPS += $$SRCBASEDIR/src/common/libcommon.a
}

LIBS += $$PRE_TARGETDEPS
