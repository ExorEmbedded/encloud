#ifndef _ENCLOUD_HTTP_HANDLER_H_
#define _ENCLOUD_HTTP_HANDLER_H_

#include "abstracthandler.h"

namespace encloud {

class JsonHandler : public HttpAbstractHandler
{
public:
    JsonHandler ();
    ~JsonHandler ();
    int handle (const HttpRequest &request, HttpResponse &response);
};

}  // namespace encloud

#endif  // _ENCLOUD_HTTP_HANDLER_H_
