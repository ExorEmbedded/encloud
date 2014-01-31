#include <QByteArray>
#include "response.h"
#include "common.h"

namespace encloud 
{

//
// public methods
//

HttpResponse::HttpResponse ()
{
    ENCLOUD_TRACE;

    // set defaults
    _version = "HTTP/1.0";
    _status = ENCLOUD_HTTP_RC_OK;
    _headers.set("Content-Type", "text/html");
}

HttpResponse::~HttpResponse ()
{
    ENCLOUD_TRACE;
}

HttpHeaders *HttpResponse::getHeaders ()
{
    return &_headers;
}

void HttpResponse::setContent (const QString &content)
{
    _content = content;
}

int HttpResponse::encode (QByteArray &data)
{
    ENCLOUD_TRACE;

    data.append(_version + " " + QString::number(_status) + " " +
            httpStatusString(_status) + "\r\n");

    _headers.set("Content-Length", QString::number(_content.size()));

    QMapIterator<QString, QString> i(*_headers.getMap());

    while (i.hasNext()) {
        i.next();
        data.append(i.key() + ": " + i.value() + "\r\n");
    }
    data.append("\r\n");
    data.append(_content);
    data.append("\r\n");

    return 0;
}

}  // namespace encloud