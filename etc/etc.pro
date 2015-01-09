include(../common.pri)

TEMPLATE = subdirs

INITDIR = "$${CONFDIR}/init.d"

# avoid stripping config files..
QMAKE_STRIP = echo

init.path = $${INITDIR}
init.files = init.d/encloud

INSTALLS += init
