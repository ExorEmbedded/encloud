#ifndef _ENCLOUD_SERVICE_H_
#define _ENCLOUD_SERVICE_H_

#ifndef ENCLOUD_DISABLE_SERVICE
#  include "qtservice.h"
#endif
#include "server.h"
#include "application.h"
#include <encloud/Logger>

#ifdef ENCLOUD_EXOR
#  define ENCLOUD_SVC_NAME  (ENCLOUD_APP_FULL + QString(" Service"))
#else
#  define ENCLOUD_NEW_NAME    "Connect Service"
// changed to follow new Connect App naming
#  define ENCLOUD_SVC_NAME  ENCLOUD_ORG " " ENCLOUD_NEW_NAME
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
