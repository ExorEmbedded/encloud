#ifndef _ENCLOUD_HTTP_HEADERS_H_
#define _ENCLOUD_HTTP_HEADERS_H_

#include <QStringList>
#include <QMap>

namespace encloud {

class HttpHeaders
{
public:
    HttpHeaders ();
    ~HttpHeaders ();

    int decode (QStringList lines);

    QString get (const QString &key);
    void set (const QString &key, const QString &value);

    QMap<QString, QString> *getMap();

private:
    QMap<QString, QString> _map;
};

}  // namespace encloud

#endif  // _ENCLOUD_HTTP_HEADERS_H_
