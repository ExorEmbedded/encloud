include(../../common.pri)

TEMPLATE = app

TARGET = $$PKGNAME_LOWER

SOURCES += main.cpp

SOURCES += application.cpp
HEADERS += application.h

!noservice {
    SOURCES += service.cpp
    HEADERS += service.h
}

#
# local libraries
# 

win32 {
    PRE_TARGETDEPS += $$SRCBASEDIR/src/common/$$DESTDIR/common.lib
} else {
    PRE_TARGETDEPS += $$SRCBASEDIR/src/common/libcommon.a
}

LIBS += $$PRE_TARGETDEPS

#
# external dependencies
# 

# qtservice
win32 {
    QTSERVICE_PATH = $$SRCBASEDIR/../qt-solutions/qtservice
    !exists($$QTSERVICE_PATH) { 
        error("Missing QtService dependency - expected in $$QTSERVICE_PATH") 
    }
    INCLUDEPATH += $$QTSERVICE_PATH/src
    DEPENDPATH += $$QTSERVICE_PATH/src
    debug {
        LIBS += -L$$QTSERVICE_PATH/lib -lQtSolutions_Service-headd
    } else {
        LIBS += -L$$QTSERVICE_PATH/lib -lQtSolutions_Service-head
    }
} 
# else:unix { use system paths }

# libencloud
LIBENCLOUD_PATH = $$SRCBASEDIR/../libencloud 
!exists($$LIBENCLOUD_PATH) { 
    error("Missing libencloud dependency - expected in $$LIBENCLOUD_PATH") 
}
INCLUDEPATH += $$LIBENCLOUD_PATH/include
LIBS += -L$$LIBENCLOUD_PATH/src/$$DESTDIR -lencloud
DEPENDPATH += $$LIBENCLOUD_PATH/include $$LIBENCLOUD_PATH/src

# installation
target.path = $${BINDIR}
INSTALLS += target

# command to run upon 'make check'
# ENCLOUD_WRAP environment variable can be set to "gdb", "valgrind", etc
check.commands = LD_LIBRARY_PATH=$$SRCBASEDIR/../libencloud/src $$(ENCLOUD_WRAP) ./$$TARGET
