#ifndef _ENCLOUD_SERVER_H_
#define _ENCLOUD_SERVER_H_

#include <QSettings>
#include <encloud/Server>

namespace encloud 
{

class Server : public libencloud::Server
{
    Q_OBJECT

public:
    Server (QObject *parent);
    ~Server ();

    inline bool isValid () const { return _isValid; };

    //
    // overrides
    //

    int start ();

private slots:
    void _portBound (int port);

private:
    bool _isValid;
    QSettings *_settings;
};

}  // namespace encloud

#endif  // _ENCLOUD_SERVER_H_

