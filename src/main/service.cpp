#include <QDir>
#include <QMutex>
#include <QTextStream>
#if defined(Q_OS_WIN32)
#  include <qt_windows.h>
#endif
#include <encloud/Common>
#include "service.h"
#include "common.h"


namespace encloud 
{

//
// public methods
//

Service::Service (int argc, char **argv)
    : QtService<QCoreApplication> (argc, argv, ENCLOUD_SVC_NAME)
    , _server(NULL)
{
    ENCLOUD_SVC_TRACE;

    initService();
}

Service::~Service ()
{
    ENCLOUD_SVC_TRACE;
}

//
// protected methods
//

void Service::initService ()
{
    ENCLOUD_SVC_TRACE;

    setServiceDescription(ENCLOUD_SVC_NAME);

    // can be stopped, but not suspended
    setServiceFlags(QtServiceBase::Default);

    // autostart
    setStartupType(QtServiceController::AutoStartup);
}

void Service::start ()
{
    ENCLOUD_SVC_TRACE;

    QCoreApplication *app = application();
    ENCLOUD_SVC_ERR_IF (app == NULL);

    ENCLOUD_SVC_ERR_IF (!_core.isValid());

    _server.setHandler(&_handler);

    ENCLOUD_SVC_ERR_IF (_core.attachServer(&_server));
    ENCLOUD_SVC_ERR_IF (_core.start());

    ENCLOUD_SVC_ERR_IF (_server.start());
    ENCLOUD_SVC_ERR_IF (!_server.isListening());

    return;
err:
    app->quit();
    return;
}

void Service::stop ()
{
    ENCLOUD_SVC_TRACE;

    ENCLOUD_SVC_ERR_IF (_server.stop()); 
    ENCLOUD_SVC_ERR_IF (_core.stop()); 
err:
    return;
}

}  // namespace encloud
