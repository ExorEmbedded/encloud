include(../../common.pri)

TEMPLATE = app

# testing
CONFIG += console

TARGET = $$PKGNAME_LOWER

SOURCES += main.cpp

SOURCES += application.cpp
HEADERS += application.h

SOURCES += server.cpp
HEADERS += server.h

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
!noservice {
    win32 {
        QTSERVICE_PATH = $$SRCBASEDIR/../qt-solutions/qtservice
        !exists($$QTSERVICE_PATH) { 
            error("Missing QtService dependency - expected in $$QTSERVICE_PATH") 
        }
        INCLUDEPATH += $$QTSERVICE_PATH/src
        DEPENDPATH += $$QTSERVICE_PATH/src
        LIBS += -L$$QTSERVICE_PATH/lib
    } 
    # else:unix { use system paths }

    CONFIG(debug,debug|release):LIBS += -lQtSolutions_Service-headd
    else:LIBS += -lQtSolutions_Service-head
}

# libencloud
win32 {
    LIBENCLOUD_PATH = $$SRCBASEDIR/../libencloud 
    !exists($$LIBENCLOUD_PATH) { 
        error("Missing libencloud dependency - expected in $$LIBENCLOUD_PATH") 
    }
    INCLUDEPATH += $$LIBENCLOUD_PATH/include
    LIBS += -L$$LIBENCLOUD_PATH/src/$$DESTDIR
    DEPENDPATH += $$LIBENCLOUD_PATH/include $$LIBENCLOUD_PATH/src
}
# else:unix { use system paths }
LIBS += -lencloud

# installation
target.path = $${BINDIR}
INSTALLS += target

# command to run upon 'make check'
# ENCLOUD_WRAP environment variable can be set to "gdb", "valgrind", etc
# e.g. ENCLOUD_WRAP="valgrind --trace-children=yes --leak-check=full" qmake -r
# e.g. ENCLOUD_WRAP="valgrind --trace-children=yes --leak-check=full" ENCLOUD_ARGS="-t" qmake -r
check.commands = LD_LIBRARY_PATH=$$SRCBASEDIR/../libencloud/src $$(ENCLOUD_WRAP) ./$$TARGET $$(ENCLOUD_ARGS)
