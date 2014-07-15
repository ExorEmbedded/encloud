#ifndef _ENCLOUD_DEFAULTS_H_
#define _ENCLOUD_DEFAULTS_H_

// Required by qsettings values and used for info()
#define ENCLOUD_APP                 ENCLOUD_PKGNAME
#define ENCLOUD_LIBENCLOUD_APP      "libencloud"

#ifdef LIBENCLOUD_USE_ABOUT

#include "../../../libencloud/about/about.h"

static char libEncloudFullAppNameBuffer[256];
#define ENCLOUD_APP_FULL            LibEncloudFullAppName(libEncloudFullAppNameBuffer, ENCLOUD_APP )

// e.g Endian/ConnectClient, Exor/JMConnect
static char libEncloudProductDirBuffer[512];
#define ENCLOUD_PRODUCTDIR          LibEncloudProductDir(libEncloudProductDirBuffer, ENCLOUD_ORG, ENCLOUD_PRODUCT)

// e.g Endian/ConnectClient/encloud | Exor/JMConnect/encloud
static char libEncloudInstallDirBuffer[512];
#define ENCLOUD_INSTALLDIR          LibEncloudInstallDir(libEncloudInstallDirBuffer, ENCLOUD_PRODUCTDIR, ENCLOUD_PKGNAME_LOWER)

#else

#define ENCLOUD_APP_FULL            ENCLOUD_ORG " "ENCLOUD_APP

// e.g Endian/ConnectClient, Exor/JMConnect
#define ENCLOUD_PRODUCTDIR          ENCLOUD_ORG "/" ENCLOUD_PRODUCT

// e.g Endian/ConnectClient/encloud | Exor/JMConnect/encloud
#define ENCLOUD_INSTALLDIR          ENCLOUD_PRODUCTDIR "/" ENCLOUD_PKGNAME_LOWER

#endif



#ifndef ENCLOUD_REVISION
  #define ENCLOUD_REVISION          ""
#endif

#ifndef ENCLOUD_VERSION_TAG
  #define ENCLOUD_VERSION_TAG       ""
#endif

#ifndef ENCLOUD_PREFIX_PATH                             /* [overridable] */
#define ENCLOUD_PREFIX_PATH         "/"
#endif
#ifdef Q_OS_WIN32  // relative paths - refer to src/common/config.cpp
#  define ENCLOUD_DATA_PREFIX       ""          // => %AppData% \ ENCLOUD_INSTALLDIR
#else  // absolute paths
#  define ENCLOUD_DATA_PREFIX       "/var/efw/encloud/"
#endif

#ifdef Q_OS_WIN32
#  define ENCLOUD_LOG_FILE          ENCLOUD_PKGNAME_LOWER "-log.txt"
#else
#  define ENCLOUD_LOG_FILE          ENCLOUD_PKGNAME_LOWER ".log"
#endif

#endif
