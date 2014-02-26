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
    , _core(NULL)
    , _handler(NULL)
    , _server(NULL)
{
    ENCLOUD_TRACE;

    ENCLOUD_ERR_IF (initService());
    ENCLOUD_ERR_IF (initEncloud());

err:
    return;
}

Service::~Service ()
{
    ENCLOUD_TRACE;

    stop();

    ENCLOUD_DELETE(_server);
    ENCLOUD_DELETE(_handler);
    ENCLOUD_DELETE(_core);
}

//
// protected methods
//

int Service::initService ()
{
    ENCLOUD_TRACE;

    setServiceDescription(ENCLOUD_SVC_NAME);

    // can be stopped, but not suspended
    setServiceFlags(QtServiceBase::Default);

    // autostart
    setStartupType(QtServiceController::AutoStartup);

    return 0;
}

int Service::initEncloud ()
{
    _core = new libencloud::Core();
    ENCLOUD_ERR_IF (_core == NULL);
    ENCLOUD_ERR_IF (!_core->isValid());

    _handler = new libencloud::HttpHandler();
    ENCLOUD_ERR_IF (_handler == NULL);

    _server = new libencloud::HttpServer();
    ENCLOUD_ERR_IF (_server == NULL);

    _server->setHandler(_handler);

    return 0;
err:
    ENCLOUD_DELETE(_server);
    ENCLOUD_DELETE(_handler);
    ENCLOUD_DELETE(_core);

    return ~0;
}

void Service::start ()
{
    ENCLOUD_TRACE;

    QCoreApplication *app = application();
    ENCLOUD_ERR_IF (app == NULL);

    ENCLOUD_ERR_IF (_core->attachServer(_server));
    ENCLOUD_ERR_IF (_core->start());

    ENCLOUD_ERR_IF (_server->start());
    ENCLOUD_ERR_IF (!_server->isListening());

    return;
err:
    app->quit();
    return;
}

void Service::stop ()
{
    ENCLOUD_TRACE;

    _server->stop();
    _core->stop();
}

}  // namespace encloud
