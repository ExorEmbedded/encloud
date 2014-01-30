#ifndef _ENCLOUD_JSON_H_
#define _ENCLOUD_JSON_H_

#include <QVariant>
#include <QString>

namespace encloud {
namespace json {

    // implementation-specific interfaces (defined in json-xxx.cpp)
    QVariant parse (const QString &str, bool &ok);
    QString serialize (const QVariant &json, bool &ok);

    // generic helpers (defined in json.cpp)
    QVariant parseFromFile (const QString &filename, bool &ok);

}  // namespace json
}  // namespace encloud

#endif
