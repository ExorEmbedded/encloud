#ifndef _ENCLOUD_SERVICE_H_
#define _ENCLOUD_SERVICE_H_

#ifndef ENCLOUD_DISABLE_SERVICE
#  include "qtservice.h"
#endif
#include "server.h"
#include "application.h"
#include <encloud/Logger>

#ifdef QICC_PKGNAME_BASE
#  define ENCLOUD_SVC_SUFFIX  QICC_PKGNAME_BASE " " "Service"
#else
#  define ENCLOUD_SVC_SUFFIX  "Connect Service"
#endif

#ifdef QICC_XBRAND
#  define ENCLOUD_SVC_NAME  ENCLOUD_SVC_SUFFIX
#else
#  define ENCLOUD_SVC_NAME  ENCLOUD_ORG " " ENCLOUD_SVC_SUFFIX
#endif

#define ENCLOUD_SVC_DESC    (ENCLOUD_SVC_NAME + QString(" provides an API for Cloud functionality"))

namespace encloud 
{

class Service 
#ifndef ENCLOUD_DISABLE_SERVICE
    : public QObject, public QtService<Application>
#else
    : public QCoreApplication
#endif
{
    Q_OBJECT

public:
    Service (int argc, char **argv);
    ~Service ();

    bool isValid ();
    int exec ();

protected:

#ifndef ENCLOUD_DISABLE_SERVICE
    void start ();
    void stop ();
#endif

    libencloud::Logger *_logger;
    bool _isValid;
    bool _isRunning;
    Server *_server;
};

}  // namespace encloud

#endif  // _ENCLOUD_SERVICE_H_
