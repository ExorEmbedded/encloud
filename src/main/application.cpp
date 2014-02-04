#include "service.h"
#include "common.h"
#include "application.h"

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
{
    ENCLOUD_SVC_TRACE;

#ifndef ENCLOUD_DISABLE_SERVICE
    setHandler(&handler);
#else
    _server.setHandler(&_handler);
    _server.start();
#endif

    core.start();
}

}  // namespace encloud
