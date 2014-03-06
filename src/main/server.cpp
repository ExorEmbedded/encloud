#include "server.h"
#include "common.h"

namespace encloud 
{

//
// public methods
//

Server::Server (QObject *parent)
    : libencloud::Server(parent, libencloud::Server::EncloudMode)
    , _settings(NULL)
{
    ENCLOUD_TRACE;

    //
    // port is read and written to libencloud settings
    //
    _settings = new QSettings(ENCLOUD_ORG, ENCLOUD_LIBENCLOUD_APP);
    ENCLOUD_ERR_IF (_settings == NULL);

    connect(this, SIGNAL(portBound(int)), this, SLOT(_portBound(int)));

err:
    return;
}

Server::~Server ()
{
    ENCLOUD_TRACE;

    ENCLOUD_DELETE(_settings);
}

// before starting, grab port from settings
int Server::start ()
{
    if (_settings->contains("port"))
        ENCLOUD_ERR_IF (setInitialPort(_settings->value("port").toInt()));

    return libencloud::Server::start();
err:
    return ~0;
}

//
// private slots
//

// once bound, save the port to settings
void Server::_portBound (int port)
{
    ENCLOUD_DBG("port: " << QString::number(port));

    _settings->setValue("port", QString::number(port));
    _settings->sync();

    ENCLOUD_ERR_MSG_IF (_settings->status() != QSettings::NoError, 
            "could not write configuration to file - check permissions!");
err:
    return;
}

}  // namespace encloud
