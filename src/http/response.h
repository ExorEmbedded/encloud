#ifndef _ENCLOUD_HTTP_RESPONSE_H_
#define _ENCLOUD_HTTP_RESPONSE_H_

#include "http.h"
#include "headers.h"

namespace encloud {

class HttpResponse
{

public:
    HttpResponse ();
    ~HttpResponse ();

    HttpHeaders *getHeaders  ();
    void setContent (const QString &content);

    int encode (QByteArray &data);

private:
    HttpStatus _status;
    QString _version;
    HttpHeaders _headers;
    QString _content;
};

}  // namespace encloud

#endif  // _ENCLOUD_HTTP_RESPONSE_H_
