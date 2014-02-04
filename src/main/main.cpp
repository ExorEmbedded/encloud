#include <encloud/Info>
#include "common.h"
#include "info.h"
#include "application.h"

//encloud::Config *g_cfg = NULL;  // for ENCLOUD_ macro usage

int main (int argc, char **argv)
{
    ENCLOUD_TRACE; 

    encloud::Application app(argc, argv);

    qDebug() << "Starting" << qPrintable(encloud::info::versionInfo())
             << "rev: " << qPrintable(encloud::info::revision())
             << " - " << qPrintable(libencloud::info::versionInfo())
             << "rev: " << qPrintable(libencloud::info::revision());

    //g_cfg = &config;  // for ENCLOUD_ macro usage
    //ENCLOUD_DBG(g_cfg->dump());

    return app.exec();
}
