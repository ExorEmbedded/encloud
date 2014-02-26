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
#endif
    , _isValid(false)
{
    ENCLOUD_TRACE;

#ifndef ENCLOUD_DISABLE_SERVICE
    ENCLOUD_DBG("QtService enabled");
    ENCLOUD_ERR_IF (0);  // just to reference err label
#else
    ENCLOUD_DBG("QtService disabled");
    ENCLOUD_ERR_IF (!_core.isValid());
    _server.setHandler(&_handler);
    ENCLOUD_ERR_IF (_core.attachServer(&_server));
    ENCLOUD_ERR_IF (_server.start() ||
                    _core.start());
#endif

    _isValid = true;

err:
    return;
}

Application::~Application ()
{
    ENCLOUD_TRACE;
}

bool Application::isValid ()
{
    return _isValid;
}

}  // namespace encloud
