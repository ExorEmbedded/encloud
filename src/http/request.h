#ifndef _ENCLOUD_HTTP_REQUEST_H_
#define _ENCLOUD_HTTP_REQUEST_H_

#include "headers.h"

namespace encloud {

class HttpRequest
{
public:
    HttpRequest ();
    ~HttpRequest ();

    int decode (const QByteArray &data);

    QString getMethod () const;
    QString getUrl () const;
    QString getVersion () const;

private:
    QString _method;
    QString _url;
    QString _version;
    HttpHeaders _headers;
};

}  // namespace encloud

#endif  // _ENCLOUD_HTTP_REQUEST_H_
