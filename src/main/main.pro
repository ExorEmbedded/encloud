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
    PRE_TARGETDEPS += $$SRCBASEDIR/src/common/common.lib
} else {
    PRE_TARGETDEPS += $$SRCBASEDIR/src/common/libcommon.a
}

LIBS += $$PRE_TARGETDEPS

#
# external dependencies
# 

LIBENCLOUD_PATH = $$SRCBASEDIR/../libencloud 
INCLUDEPATH += $$LIBENCLOUD_PATH/include
LIBS += -L$$LIBENCLOUD_PATH/src -lencloud
DEPENDPATH += $$LIBENCLOUD_PATH/include $$LIBENCLOUD_PATH/src

# command to run upon 'make check'
# ENCLOUD_WRAP environment variable can be set to "gdb", "valgrind", etc
check.commands = LD_LIBRARY_PATH=$$SRCBASEDIR/../libencloud/src $$(ENCLOUD_WRAP) ./$$TARGET
