#include "common.h"

namespace encloud {
namespace info {

QString org () 
{ 
    return ENCLOUD_ORG;
}

QString app () 
{ 
    return ENCLOUD_PKGNAME; 
}

QString version () 
{ 
    return ENCLOUD_VERSION; 
}

QString revision () 
{ 
    return ENCLOUD_REVISION; 
}

QString versionTag () 
{ 
    return ENCLOUD_VERSION_TAG; 
}

QString versionInfo ()
{
    QString info;

    info += org() + " ";
    info += app() + " v" + version();

    // revision is printed only to logs (not very user-friendly)
    //if (revision() != "")
    //    info += " rev " + revision();

    if (versionTag() != "")
        info += " (" + versionTag() + ")";

    return info;
}

}  // namespace info
}  // namespace encloud
