#ifndef _ENCLOUD_HTTP_ABSTRACT_HANDLER_H_
#define _ENCLOUD_HTTP_ABSTRACT_HANDLER_H_

#include "request.h"
#include "response.h"

namespace encloud {

class HttpAbstractHandler
{
public:
    virtual ~HttpAbstractHandler() {};
    virtual int handle (const HttpRequest &request, HttpResponse &response) = 0;
};

}  // namespace encloud

#endif  // _ENCLOUD_HTTP_ABSTRACT_HANDLER_H_
