#include <encloud/Common>
#include <encloud/Info>
#include <encloud/Logger>
#include "common.h"
#include "info.h"
#include "application.h"

int main (int argc, char **argv)
{
    libencloud::Logger logger;
    logger.setPath(libencloud::getCommonAppDataDir(ENCLOUD_PKGNAME_LOWER) + "/" + 
            ENCLOUD_PKGNAME_LOWER + "-log.txt");
    ENCLOUD_RETURN_IF (logger.open() || 
            !logger.isValid(),
                EXIT_FAILURE);

    ENCLOUD_TRACE; 

    ENCLOUD_DBG("Starting " << qPrintable(encloud::info::versionInfo())
            << "rev: " << qPrintable(encloud::info::revision()));

    encloud::Application app(argc, argv);
    ENCLOUD_ERR_IF (!app.isValid());

    return app.exec();
err:
    return EXIT_FAILURE;
}
