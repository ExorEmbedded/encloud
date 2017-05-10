include(../../common.pri)

TEMPLATE = app

# testing
CONFIG += console
CONFIG -= app_bundle

TARGET = $$PKGNAME_LOWER

SOURCES += main.cpp

SOURCES += application.cpp
HEADERS += application.h

SOURCES += server.cpp
HEADERS += server.h

SOURCES += service.cpp
HEADERS += service.h

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

    LIBS += -lQtSolutions_Service-head$${DBG_SUFFIX}
}

# libencloud
LIBENCLOUD_PATH = $$SRCBASEDIR/../libencloud 
INCLUDEPATH += $$LIBENCLOUD_PATH/include
win32 {
    !exists($$LIBENCLOUD_PATH) { 
        error("Missing libencloud dependency - expected in $$LIBENCLOUD_PATH") 
    }

    DEPENDPATH += $$LIBENCLOUD_PATH/include $$LIBENCLOUD_PATH/src $$LIBENCLOUD_PATH/about

    # must be administrator to run it
    QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""

    PRE_TARGETDEPS += $$LIBENCLOUD_PATH/src/$$DESTDIR/encloud$${DBG_SUFFIX}.lib
    PRE_TARGETDEPS += $$LIBENCLOUD_PATH/about/$$DESTDIR/about$${DBG_SUFFIX}.lib

    LIBS += $$PRE_TARGETDEPS
} else {
    !splitdeps {
        about {
            LIBS += -L$$LIBENCLOUD_PATH/about
        }
        LIBS += -L$$LIBENCLOUD_PATH/src
    }
    LIBS += -lencloud -labout
}

# yaml-cpp
YAMLCPP_PATH = $${SRCBASEDIR}/../yaml-cpp
!exists($$LIBENCLOUD_PATH): error("Missing libencloud dependency - expected in $$YAMLCPP_PATH") 
!splitdeps {
    INCLUDEPATH += $${YAMLCPP_PATH}/include
    LIBS += -L$${YAMLCPP_PATH}/src/$$DESTDIR 
}
LIBS += -lyaml-cpp

#
# installation
#
target.path = $${BINDIR}
INSTALLS += target

# command to run upon 'make check'
# ENCLOUD_WRAP environment variable can be set to "gdb", "valgrind", etc
# e.g. ENCLOUD_WRAP="valgrind --trace-children=yes --leak-check=full" qmake -r
# e.g. ENCLOUD_WRAP="valgrind --trace-children=yes --leak-check=full" ENCLOUD_ARGS="-t" qmake -r
check.commands = LD_LIBRARY_PATH=$$SRCBASEDIR/../libencloud/src:$$SRCBASEDIR/../libencloud/about \
                 $$(ENCLOUD_WRAP) ./$$TARGET $$(ENCLOUD_ARGS)
