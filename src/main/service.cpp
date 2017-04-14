#include "service.h"
#include "common.h"

namespace encloud 
{

//
// public methods
//

// IMPORTANT NOTE: All heap allocation/deallocation MUST happen in
// start()/stop() to avoid QtService memory corruption
Service::Service (int argc, char **argv)
#ifndef ENCLOUD_DISABLE_SERVICE
    : QtService<Application> (argc, argv, ENCLOUD_SVC_NAME)
#else
    : QCoreApplication(argc, argv)
#endif
    , _logger(NULL)
    , _isValid(false)
    , _isRunning(false)
    , _server(NULL)
{
#ifndef ENCLOUD_DISABLE_SERVICE
    ENCLOUD_DBG("QtService enabled");

    setServiceDescription(ENCLOUD_SVC_DESC);

    // can be stopped, but not suspended
    setServiceFlags(QtServiceBase::Default);

    // autostart
    setStartupType(QtServiceController::AutoStartup);
#else
    ENCLOUD_DBG("QtService disabled");

    _server = new Server(this);
    ENCLOUD_ERR_IF (_server == NULL);
    ENCLOUD_ERR_IF (!_server->isValid());
    ENCLOUD_ERR_IF (_server->start());
#endif

    _isValid = true;

err:
    return;
}

// SEE NOTE ABOVE
Service::~Service ()
{
    ENCLOUD_TRACE;

#ifdef ENCLOUD_DISABLE_SERVICE
    _server->stop();
    ENCLOUD_DELETE(_server);
#endif
}

bool Service::isValid () { return _isValid; } 

int Service::exec () 
{
#ifdef ENCLOUD_DISABLE_SERVICE
    return QCoreApplication::exec();
#else
    return QtService<Application>::exec();
#endif
} 

//
// protected methods
//

#ifndef ENCLOUD_DISABLE_SERVICE
void Service::start ()
{
    QCoreApplication *app = NULL;

    if (_isRunning)
        return;

    _logger = new libencloud::Logger;
    ENCLOUD_ERR_IF (_logger == NULL);

    // create new logger in append mode because logger was already created in main()
    ENCLOUD_ERR_IF (_logger->setPath(
                libencloud::getCommonLogDir(ENCLOUD_PKGNAME_LOWER) + "/" +
                ENCLOUD_LOG_FILE));
    ENCLOUD_ERR_IF (_logger->setExtraMode(QFile::Append));
    ENCLOUD_ERR_IF (_logger->open());
    ENCLOUD_ERR_IF (!_logger->isValid());

    ENCLOUD_TRACE;

    app = application();
    ENCLOUD_ERR_IF (app == NULL);

    _server = new Server(app);
    ENCLOUD_ERR_IF (_server == NULL);

    ENCLOUD_TRACE;

    ENCLOUD_ERR_IF (!_server->isValid());
    ENCLOUD_ERR_IF (_server->start());

    _isRunning = true;

    ENCLOUD_TRACE;
    return;
err:
    ENCLOUD_DELETE(_server);
    ENCLOUD_DELETE(_logger);
    return;
}
#endif

#ifndef ENCLOUD_DISABLE_SERVICE
void Service::stop ()
{
    ENCLOUD_TRACE;

    if (!_isRunning)
        return;

    ENCLOUD_ERR_IF (_server->stop());
err:
    ENCLOUD_DELETE (_server);
    ENCLOUD_DELETE (_logger);
    qApp->quit();
    return;
}
#endif

}  // namespace encloud
