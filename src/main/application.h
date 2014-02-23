#ifndef _ENCLOUD_APPLICATION_H_
#define _ENCLOUD_APPLICATION_H_

#include <QCoreApplication>

#ifndef ENCLOUD_DISABLE_SERVICE
#  include "service.h"
#  include "qtservice.h"
#endif

#include <encloud/Core>
#include <encloud/HttpServer>
#include <encloud/HttpHandler>

namespace encloud  {

class Application :
#ifndef ENCLOUD_DISABLE_SERVICE
    public Service
#else
    public QCoreApplication
#endif
{
    Q_OBJECT

public:

    Application (int argc, char **argv);

    bool isValid ();

private:

    bool _isValid;

#ifdef ENCLOUD_DISABLE_SERVICE
    libencloud::HttpServer _server;
    libencloud::HttpHandler _handler;

    libencloud::Core _core;
#endif
};

}  // namespace encloud

#endif  // _ENCLOUD_APPLICATION_H_
