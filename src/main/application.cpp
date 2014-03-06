#include "service.h"
#include "common.h"
#include "application.h"
#include <encloud/Core>

namespace encloud 
{

//
// public methods
//

Application::Application (int argc, char **argv)
#ifndef ENCLOUD_DISABLE_SERVICE
    : Service(argc, argv)
#else
    : QCoreApplication(argc, argv)
    , _server(NULL)
#endif
    , _isValid(false)
{
    ENCLOUD_TRACE;

#ifndef ENCLOUD_DISABLE_SERVICE
    ENCLOUD_DBG("QtService enabled");
    ENCLOUD_ERR_IF (!Service::isValid());
#else
    ENCLOUD_DBG("QtService disabled");
    ENCLOUD_ERR_IF (_server = new Server(this));
    ENCLOUD_ERR_IF (_server == NULL);
    ENCLOUD_ERR_IF (_server->start());
#endif

    _isValid = true;

err:
    return;
}

Application::~Application ()
{
    ENCLOUD_TRACE;

#ifdef ENCLOUD_DISABLE_SERVICE
    _server->stop();
    ENCLOUD_DELETE(_server);
#endif
}

bool Application::isValid ()
{
    return _isValid;
}

}  // namespace encloud
