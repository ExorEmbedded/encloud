#ifndef _ENCLOUD_DEFAULTS_H_
#define _ENCLOUD_DEFAULTS_H_

#ifndef ENCLOUD_REVISION
  #define ENCLOUD_REVISION ""
#endif

#ifndef ENCLOUD_VERSION_TAG
  #define ENCLOUD_VERSION_TAG ""
#endif

// Required by qsettings values and used for info()
#define ENCLOUD_APP            ENCLOUD_PKGNAME

#define ENCLOUD_PKGNAME_4IC    "4iConnect"
#define ENCLOUD_PRODUCT        ENCLOUD_ORG" "ENCLOUD_APP

//
// overrideable macros
//
#ifdef _WIN32
#define ENCLOUD_ETC_PREFIX      "\\etc\\"
#else
#define ENCLOUD_ETC_PREFIX      "etc/"ENCLOUD_PKGNAME_LOWER"/"
#endif

#define ENCLOUD_CONF_FILE       ENCLOUD_PKGNAME_LOWER".json"

#endif
