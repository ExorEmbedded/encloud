#include "http.h"

namespace encloud {

//
// public methods
//

QString httpStatusString (HttpStatus status)
{
    switch (status)
    {
        case ENCLOUD_HTTP_RC_OK:
            return "OK";
        default:
            return "";
    }
}

}  // namespace encloud
