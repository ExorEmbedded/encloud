#include <QCoreApplication>
#include "common.h"
#include "utils.h"

//encloud::Config *g_cfg = NULL;  // for ENCLOUD_ macro usage

int main(int argc, char **argv)
{
    ENCLOUD_TRACE; 

    qDebug() << "Starting" << encloud::utils::versionInfo() << " rev: " << encloud::utils::revision();

    QCoreApplication app(argc, argv);

    //g_cfg = &config;  // for ENCLOUD_ macro usage
    //ENCLOUD_DBG(g_cfg->dump());

    return (app.exec());
}
