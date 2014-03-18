#ifndef _ENCLOUD_APPLICATION_H_
#define _ENCLOUD_APPLICATION_H_

#include <QCoreApplication>
#ifndef ENCLOUD_DISABLE_SERVICE
#  include "service.h"
#  include "qtservice.h"
#else
#  include "server.h"
#endif

namespace encloud {

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
    ~Application ();

    bool isValid ();

private:

#ifdef ENCLOUD_DISABLE_SERVICE
    Server *_server;
#endif

    bool _isValid;
};

}  // namespace encloud

#endif  // _ENCLOUD_APPLICATION_H_
