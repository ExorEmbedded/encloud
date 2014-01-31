#include <QByteArray>
#include "request.h"
#include "common.h"

namespace encloud 
{

//
// public methods
//

HttpRequest::HttpRequest ()
{
    ENCLOUD_TRACE;
}

HttpRequest::~HttpRequest ()
{
    ENCLOUD_TRACE;
}

int HttpRequest::decode (const QByteArray &data)
{
    ENCLOUD_TRACE;

    QStringList lines;
    QStringList fields;

    lines = QString(data).split("\r\n");
    ENCLOUD_ERR_IF (lines.count() == 0);

    fields = lines[0].split(' ');
    ENCLOUD_ERR_IF (fields.count() < 3);

    _method = fields[0];
    _url = fields[1];
    _version = fields[2];

    lines.removeFirst(); 
    ENCLOUD_ERR_IF (lines.count() == 0);
    ENCLOUD_ERR_IF (_headers.decode(lines));

    return 0;
err:
    return ~0;
}

QString HttpRequest::getMethod() const      { return _method; }
QString HttpRequest::getUrl() const         { return _url; }
QString HttpRequest::getVersion () const    { return _version; }

}  // namespace encloud
