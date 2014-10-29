#ifndef _ENCLOUD_SERVICE_H_
#define _ENCLOUD_SERVICE_H_

#include "qtservice.h"
#include "server.h"
#include <encloud/Logger>

#ifdef ENCLOUD_ENDIAN
// changed to follow new Connect Client App naming
#  define ENCLOUD_SVC_NAME  "Endian Connect Service"
#else
#  define ENCLOUD_SVC_NAME  (ENCLOUD_APP_FULL + QString(" Service"))
#endif

#define ENCLOUD_SVC_DESC    (ENCLOUD_SVC_NAME + QString(" provides an API for Cloud functionality"))

namespace encloud 
{

class Service : public QObject, public QtService<QCoreApplication>
{
    Q_OBJECT

public:
    Service (int argc, char **argv);
    ~Service ();

    bool isValid ();

protected:
    void start ();
    void stop ();

    libencloud::Logger *_logger;
    bool _isValid;
    bool _isRunning;
    Server *_server;
};

}  // namespace encloud

#endif  // _ENCLOUD_SERVICE_H_
