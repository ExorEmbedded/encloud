#ifndef _ENCLOUD_DEFAULTS_H_
#define _ENCLOUD_DEFAULTS_H_

// Required by qsettings values and used for info()
#define ENCLOUD_APP                 ENCLOUD_PKGNAME
#define ENCLOUD_APP_FULL            ENCLOUD_ORG " "ENCLOUD_APP

// e.g Endian/4iConnect, Exor/JMConnect
#define ENCLOUD_PRODUCTDIR          ENCLOUD_ORG "/" ENCLOUD_PRODUCT

// e.g Endian/4iConnect/encloud | Exor/JMConnect/encloud
#define ENCLOUD_INSTALLDIR          ENCLOUD_PRODUCTDIR "/" ENCLOUD_PKGNAME_LOWER

#ifndef ENCLOUD_REVISION
  #define ENCLOUD_REVISION          ""
#endif

#ifndef ENCLOUD_VERSION_TAG
  #define ENCLOUD_VERSION_TAG       ""
#endif

#ifndef ENCLOUD_PREFIX_PATH                             /* [overridable] */
#define ENCLOUD_PREFIX_PATH          "/"
#endif
#ifdef Q_OS_WIN32  // relative paths - refer to src/common/config.cpp
#  define ENCLOUD_DATA_PREFIX        ""          // => %AppData% \ ENCLOUD_INSTALLDIR
#else  // absolute paths
#  define ENCLOUD_DATA_PREFIX        "/var/lib/encloud/"
#endif

#endif
