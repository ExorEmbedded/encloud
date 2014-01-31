#include "common.h"
#include "handler.h"

namespace encloud {

//
// public methods
//

JsonHandler::JsonHandler ()
{
    ENCLOUD_TRACE;
}

JsonHandler::~JsonHandler ()
{
    ENCLOUD_TRACE;
}

int JsonHandler::handle (const HttpRequest &request, HttpResponse &response)
{
    ENCLOUD_TRACE;

#if 0
    bool ok;
    QVariant inJson;
    QVariant outJson;
#endif

    ENCLOUD_DBG("method: " << request.getMethod());
    ENCLOUD_DBG("url: " << request.getUrl())

    response.setContent("this is the body 123");

#if 0
    inJson = json::parse(message, ok);
    ENCLOUD_ERR_IF (inJson.isNull() || !ok);
    outJson = handleJson(inJson);
    outMessage = json::serialize(outJson, ok).toAscii();
    ENCLOUD_ERR_IF (outJson.isNull() || !ok);
#endif

    return 0;
err:
    return ~0;
}

//
// private methods
//

}  // namespace encloud
