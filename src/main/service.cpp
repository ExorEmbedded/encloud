#include <ENCLOUD/Config.h>
#include "service.h"
#include "server.h"
#include "common.h"

namespace encloud 
{

//
// public methods
//

Service::Service (int argc, char **argv)
    : QtService<QCoreApplication> (argc, argv, ENCLOUD_SVC_NAME)
    , server(NULL)
{
    ENCLOUD_SVC_TRACE;

    setServiceDescription(ENCLOUD_SVC_NAME);
    setServiceFlags(QtServiceBase::Default);  // can be stopped, but not suspended
    setStartupType(QtServiceController::AutoStartup);  // autostart
}

//
// private slots
//

//
// protected methods
//

void Service::start ()
{
    ENCLOUD_SVC_TRACE;

    ENCLOUD_SVC_RETURN_IF (_server != NULL, ); 

    QCoreApplication *app = application();
    ENCLOUD_SVC_ERR_IF (app == NULL);

    _server = new HttpServer(app);
    ENCLOUD_SVC_ERR_IF (_server == NULL);
    ENCLOUD_SVC_ERR_IF (_server->start());
    ENCLOUD_SVC_ERR_IF (!_server->isListening());

    return;
err:
    app->quit();
    return;
}

void Service::stop ()
{
    ENCLOUD_SVC_TRACE;

    ENCLOUD_SVC_ERR_IF (_server == NULL); 
    ENCLOUD_SVC_ERR_IF (_server->stop()); 
    ENCLOUD_DELETE(_server);
err:
    return;
}

}  // namespace encloud
