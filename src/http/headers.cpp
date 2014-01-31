#include "headers.h"
#include "common.h"

namespace encloud 
{

//
// public methods
//

HttpHeaders::HttpHeaders ()
{
    ENCLOUD_TRACE;
}

HttpHeaders::~HttpHeaders ()
{
    ENCLOUD_TRACE;
}

int HttpHeaders::decode (QStringList lines)
{
    ENCLOUD_TRACE;

    _map.clear();

    foreach (QString line, lines)
    {
        if (line == "")
            continue;

        QStringList keyval = line.split(':');
        if (keyval.count() != 2)
            continue;

        set(keyval[0].trimmed(), keyval[1].trimmed());
    }

    ENCLOUD_DBG("headers: " << _map);

    return 0;
err:
    return ~0;
}

QString HttpHeaders::get (const QString &key)
{ 
    return _map[key.toLower()]; 
}

void HttpHeaders::set (const QString &key, const QString &value)
{ 
    _map[key.toLower()] = value; 
}

QMap<QString, QString> *HttpHeaders::getMap()
{ 
    return &_map;
}

}  // namespace encloud
