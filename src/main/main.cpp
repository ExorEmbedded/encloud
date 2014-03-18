#include <encloud/Common>
#include <encloud/Info>
#include <encloud/Logger>
#include "common.h"
#include "info.h"
#include "application.h"

int main (int argc, char **argv)
{
    // This logger lives:
    // - throughout the application in noservice mode
    // - until services is created in service mode (a new logger is created within service)
    libencloud::Logger logger;
    ENCLOUD_RETURN_IF (logger.setPath(libencloud::getCommonAppDataDir(ENCLOUD_PKGNAME_LOWER) + "/" + 
            ENCLOUD_PKGNAME_LOWER + "-log.txt"), 
            EXIT_FAILURE);
    ENCLOUD_RETURN_IF (logger.open() || !logger.isValid(),
            EXIT_FAILURE);

    qDebug() << "Starting " << qPrintable(encloud::info::versionInfo())
            << "rev: " << qPrintable(encloud::info::revision());

    encloud::Application app(argc, argv);
    ENCLOUD_ERR_IF (!app.isValid());
    ENCLOUD_ERR_IF (app.exec());

    ENCLOUD_DBG("Success");
    return 0;
err:
    ENCLOUD_DBG("Failure");
    return EXIT_FAILURE;
}
