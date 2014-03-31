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
    : QtService<QCoreApplication> (argc, argv, ENCLOUD_SVC_NAME)
    , _logger(NULL)
    , _isValid(false)
    , _isRunning(false)
    , _server(NULL)
{

    setServiceDescription(ENCLOUD_SVC_DESC);

    // can be stopped, but not suspended
    setServiceFlags(QtServiceBase::Default);

    // autostart
    setStartupType(QtServiceController::AutoStartup);

    _isValid = true;
}

// SEE NOTE ABOVE
Service::~Service ()
{
    ENCLOUD_TRACE;
}

bool Service::isValid () { return _isValid; } 

//
// protected methods
//

void Service::start ()
{
    if (_isRunning)
        return;

    _logger = new libencloud::Logger;
    ENCLOUD_ERR_IF (_logger == NULL);

    // create new logger in append mode because logger was already created in main()
    ENCLOUD_ERR_IF (_logger->setPath(
                libencloud::getCommonAppDataDir(ENCLOUD_PKGNAME_LOWER) + "/" + 
                ENCLOUD_PKGNAME_LOWER + "-log.txt"));
    ENCLOUD_ERR_IF (_logger->setExtraMode(QFile::Append));
    ENCLOUD_ERR_IF (_logger->open());
    ENCLOUD_ERR_IF (!_logger->isValid());

    ENCLOUD_TRACE;

    QCoreApplication *app = application();
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

}  // namespace encloud
