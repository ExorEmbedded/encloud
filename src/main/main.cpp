#include <QTextCodec>
#include <encloud/Common>
#include <encloud/Info>
#include <encloud/Logger>
#include "common.h"
#include "info.h"
#include "service.h"

int main (int argc, char **argv)
{
    encloud::Service service(argc, argv);

#ifndef ENCLOUD_DISABLE_SERVICE
    // This logger lives until service is created (a new logger is created within service)
    libencloud::Logger logger;
    ENCLOUD_RETURN_IF (logger.setPath(
                libencloud::getCommonLogDir(ENCLOUD_PKGNAME_LOWER) + "/" +
                ENCLOUD_LOG_FILE),
            EXIT_FAILURE);
    ENCLOUD_RETURN_IF (logger.open() || !logger.isValid(),
            EXIT_FAILURE);
#endif

    ENCLOUD_RETURN_IF (!service.isValid(), EXIT_FAILURE);

    qDebug() << "Starting " << qPrintable(encloud::info::versionInfo())
            << "rev: " << qPrintable(encloud::info::revision());

    // Set Codec for translations and C strings to UTF-8
    // NOTE: Qt4-specific, no longer needed in Qt5
#if QT_VERSION < 0x050000
    QTextCodec *utf8Codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(utf8Codec);
    QTextCodec::setCodecForCStrings(utf8Codec);
    QTextCodec::setCodecForLocale(utf8Codec);
#endif

    ENCLOUD_ERR_IF (service.exec());

    ENCLOUD_DBG("Success");
    return 0;

err:
    ENCLOUD_DBG("Failure");
    return EXIT_FAILURE;
}
