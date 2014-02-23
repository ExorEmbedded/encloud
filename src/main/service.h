#ifndef _ENCLOUD_SERVICE_H_
#define _ENCLOUD_SERVICE_H_

#include <QFile>
#include <QTextStream>
#include <encloud/Core>
#include <encloud/HttpServer>
#include <encloud/HttpHandler>
#include "qtservice.h"

#define ENCLOUD_SVC_NAME            ENCLOUD_APP_FULL " Service"
#define ENCLOUD_SVC_DESC            ENCLOUD_SVC_NAME" provides an API for cloud functionality"

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
    ~Service ();

protected:
    void initService ();

    void start ();
    void stop ();

    libencloud::Core _core;
    libencloud::HttpServer _server;
    libencloud::HttpHandler _handler;
};

}  // namespace encloud

#endif  // _ENCLOUD_SERVICE_H_
