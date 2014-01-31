#ifndef _ENCLOUD_HTTP_HTTP_H_
#define _ENCLOUD_HTTP_HTTP_H_

#include <QString>

namespace encloud {

typedef enum {
    ENCLOUD_HTTP_RC_OK = 200
} HttpStatus;

QString httpStatusString (HttpStatus status);

}  // namespace encloud

#endif  // _ENCLOUD_HTTP_HTTP_H_
