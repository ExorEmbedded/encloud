#include <QCoreApplication>
#include "common.h"
#include "utils.h"
#ifndef ENCLOUD_DISABLE_SERVICE
#  include "service.h"
#endif
#include "server.h"
#include "handler.h"

//encloud::Config *g_cfg = NULL;  // for ENCLOUD_ macro usage

namespace encloud {

int runApplication (int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    HttpServer server;
    JsonHandler handler;
    server.setHandler(&handler);
    server.start();
    return app.exec();
};

#ifndef ENCLOUD_DISABLE_SERVICE
int runService (int argc, char *argv[])
{
    Service service(argc, argv);
    return service.exec();
};
#endif

}  // namespace encloud

//
// no namespace
//

int main (int argc, char **argv)
{
    ENCLOUD_TRACE; 

    qDebug() << "Starting" << encloud::utils::versionInfo()
             << " rev: " << encloud::utils::revision();

    //g_cfg = &config;  // for ENCLOUD_ macro usage
    //ENCLOUD_DBG(g_cfg->dump());

#ifdef ENCLOUD_DISABLE_SERVICE
    return encloud::runApplication(argc, argv);
#else
    return encloud::runService(argc, argv);
#endif
}
