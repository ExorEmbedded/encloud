#include "service.h"
#include "common.h"
#include "application.h"

namespace encloud 
{

//
// public methods
//

Application::Application (int argc, char **argv)
    : _isValid(false)
#ifndef ENCLOUD_DISABLE_SERVICE
    , Service(argc, argv)
#else
    , QCoreApplication(argc, argv)
#endif
{
    ENCLOUD_SVC_TRACE;

#ifndef ENCLOUD_DISABLE_SERVICE
    setHandler(&_handler);
#else
    _server.setHandler(&_handler);
    _server.start();
#endif

    if (!_core.isValid() ||
        _core.attachServer(&_server) ||
        _core.start())
        goto err;

    _isValid = true;

err:
    return;
}

bool Application::isValid ()
{
    return _isValid;
}

}  // namespace encloud
