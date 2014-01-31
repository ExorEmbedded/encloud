#ifndef _ENCLOUD_SERVICE_H_
#define _ENCLOUD_SERVICE_H_

#include "Server.h"
#include "qtservice.h"

#define ENCLOUD_SVC_NAME            ENCLOUD_PRODUCT" Service"
#define ENCLOUD_SVC_DESC            ENCLOUD_SVC_NAME" provides an API for VPN functionality"

// TODO QtServiceBase::instance()->logMessage("Sample message");
#define ENCLOUD_SVC_TRACE           ENCLOUD_TRACE
#define ENCLOUD_SVC_LOG(msg)        ENCLOUD_DBG(msg)
#define ENCLOUD_SVC_ERR_IF(cond)    ENCLOUD_ERR_IF(cond)
#define ENCLOUD_SVC_RETURN_IF(cond, res)    ENCLOUD_RETURN_IF(cond, res)

namespace encloud 
{

class Service : public QObject, public QtService<QCoreApplication>
{
    Q_OBJECT

public:
    Service (int argc, char **argv);

protected:
    void start ();
    void stop ();

    Server *_server;
};

}  // namespace encloud

#endif  // _ENCLOUD_SERVICE_H_
