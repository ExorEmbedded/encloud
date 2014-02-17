#ifndef _ENCLOUD_SERVICE_H_
#define _ENCLOUD_SERVICE_H_

#include "qtservice.h"
#include <encloud/HttpServer>
#include <encloud/HttpHandler>

#define ENCLOUD_SVC_NAME            ENCLOUD_PRODUCT" Service"
#define ENCLOUD_SVC_DESC            ENCLOUD_SVC_NAME" provides an API for cloud functionality"

// TODO QtServiceBase::instance()->logMessage("Sample message");
#define ENCLOUD_SVC_TRACE           ENCLOUD_TRACE
#define ENCLOUD_SVC_DBG(msg)        ENCLOUD_DBG(msg)
#define ENCLOUD_SVC_ERR_IF(cond)    ENCLOUD_ERR_IF(cond)
#define ENCLOUD_SVC_RETURN_IF(cond, res)    ENCLOUD_RETURN_IF(cond, res)

namespace encloud 
{

class Service : public QObject, public QtService<QCoreApplication>
{
    Q_OBJECT

public:
    Service (int argc, char **argv);

    void setHandler (libencloud::HttpHandler *handler);

protected:
    void start ();
    void stop ();

    libencloud::HttpServer *_server;
    libencloud::HttpHandler *_handler;
};

}  // namespace encloud

#endif  // _ENCLOUD_SERVICE_H_
