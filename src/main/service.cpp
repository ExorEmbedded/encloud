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
    , _isValid(false)
    , _isRunning(false)
    , _server(NULL)
{
    ENCLOUD_TRACE;

    setServiceDescription(ENCLOUD_SVC_DESC);

    // can be stopped, but not suspended
    setServiceFlags(QtServiceBase::Default);

    // autostart
    setStartupType(QtServiceController::AutoStartup);

    _isValid = true;
}

Service::~Service ()
{
    ENCLOUD_TRACE;

    stop();
}

bool Service::isValid () { return _isValid; } 

//
// protected methods
//

void Service::start ()
{
    ENCLOUD_TRACE;

    if (_isRunning)
        return;

    QCoreApplication *app = application();
    ENCLOUD_ERR_IF (app == NULL);

    _server = new Server(app);
    ENCLOUD_ERR_IF (_server == NULL);

    ENCLOUD_ERR_IF (_server->start());

    _isRunning = true;
err:
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
    return;
}

}  // namespace encloud
