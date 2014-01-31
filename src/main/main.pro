include(../../common.pri)

TEMPLATE = app

TARGET = $$PKGNAME_LOWER

SOURCES += main.cpp

!noservice {
    SOURCES += service.cpp
    HEADERS += service.h
}

SOURCES += handler.cpp
HEADERS += handler.h

win32 {
    PRE_TARGETDEPS += $$SRCBASEDIR/src/http/http.lib
    PRE_TARGETDEPS += $$SRCBASEDIR/src/common/common.lib
} else {
    PRE_TARGETDEPS += $$SRCBASEDIR/src/http/libhttp.a
    PRE_TARGETDEPS += $$SRCBASEDIR/src/common/libcommon.a
}

# dependencies
INCLUDEPATH += $$SRCBASEDIR/src/http

LIBS += $$PRE_TARGETDEPS
