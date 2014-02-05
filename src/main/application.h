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
    public QObject, public QtService<QCoreApplication>
#else
    public QCoreApplication
#endif
{
    Q_OBJECT

public:

    Application (int argc, char **argv);

private slots:

    void stateChanged (const QString &state);

private:

#ifdef ENCLOUD_DISABLE_SERVICE
    libencloud::HttpServer _server;
#endif
    libencloud::HttpHandler _handler;

    libencloud::Core core;
};

}  // namespace encloud

#endif  // _ENCLOUD_APPLICATION_H_
