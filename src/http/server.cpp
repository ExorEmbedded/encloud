#include <QTcpSocket>
#include <QStringList>
#include <QRegExp>
#include <qtservice.h>
#include "server.h"
#include "request.h"
#include "common.h"

#define ENCLOUD_SRV_LISTEN          "127.0.0.1"

#ifdef ENCLOUD_DISABLE_SERVICE
#  define ENCLOUD_SVC_TRACE         ENCLOUD_TRACE
#  define ENCLOUD_SVC_LOG(msg)      ENCLOUD_DBG(msg)
#  define ENCLOUD_SVC_ERR_IF(cond)  ENCLOUD_ERR_IF(cond)
#  define ENCLOUD_SVC_RETURN_IF(cond, res) ENCLOUD_RETURN_IF(cond, res)
#  define ENCLOUD_SVC_DBG(msg)      ENCLOUD_DBG(msg)
#else
#  include "service.h"
#endif

namespace encloud 
{

//
// public methods
//

HttpServer::HttpServer (QObject *parent)
    : QTcpServer(parent)
{
    ENCLOUD_SVC_TRACE;
}

HttpServer::~HttpServer ()
{
    ENCLOUD_SVC_TRACE;

    ENCLOUD_DELETE(_socket);
    close();
}

int HttpServer::setHandler (HttpAbstractHandler *handler)
{
    ENCLOUD_ERR_IF (handler == NULL);

    _handler = handler;

    return 0;
err:
    return ~0;
}

int HttpServer::start ()
{
    ENCLOUD_SVC_TRACE;

    /* TODO listen also VPN tap interface once connected! */
    ENCLOUD_ERR_IF(!listen(QHostAddress(ENCLOUD_SRV_LISTEN), 
                ENCLOUD_SRV_PORT_DFT));  
    return 0;
err:
    return ~0;
}

int HttpServer::stop ()
{
    ENCLOUD_SVC_TRACE;
    
    close();

    return 0;
}

void HttpServer::incomingConnection (int sd)
{
    ENCLOUD_SVC_TRACE;

    _socket = new QTcpSocket(this); 
    ENCLOUD_SVC_ERR_IF (_socket == NULL);

    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), 
            this, SLOT(error(QAbstractSocket::SocketError)));
    _socket->setSocketDescriptor(sd);

err:
    return;
}

//
// private slots
//

void HttpServer::readyRead ()
{
    ENCLOUD_SVC_TRACE;

    enum { MAX_MSG = 1024 * 10 };
    QTcpSocket* socket = (QTcpSocket*)sender();
    QByteArray inData;
    QByteArray outData;

    if (!socket->canReadLine())
        return;
    
    inData = socket->readAll();
    ENCLOUD_ERR_IF (inData.isEmpty());

    outData = handleMessage(inData);
    ENCLOUD_ERR_IF (outData.isEmpty());

    ENCLOUD_DBG("<<<" << inData);
    ENCLOUD_DBG(">>>" << outData);

    socket->write(outData);
err:
    return;
}

void HttpServer::disconnected ()
{
    ENCLOUD_SVC_TRACE;

    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->deleteLater();
}

void HttpServer::error (QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);

    QTcpSocket* socket = (QTcpSocket*)sender();

    ENCLOUD_SVC_DBG("err: " << QString::number(socket->error())
            << " (" << socket->errorString() << ")");
}

//
// private methods
//

QByteArray HttpServer::handleMessage (QByteArray message)
{
    ENCLOUD_SVC_TRACE;

    QByteArray outMessage;
    HttpRequest request;
    HttpResponse response;

    ENCLOUD_ERR_IF (_handler == NULL);
    ENCLOUD_ERR_IF (request.decode(message));
    ENCLOUD_ERR_IF (_handler->handle(request, response));
    ENCLOUD_ERR_IF (response.encode(outMessage));

    return outMessage;
err:
//TODO 404
    return "{ \"error\" : \"bad error\" }";
}

QVariant HttpServer::handleJson (QVariant json)
{
    QVariantMap jm = json.toMap();
    QVariant outJson;
    bool ok;

    QString action = jm["action"].toString();

    outJson = json::parse("{ \"error\" : \"none\", \"action\" : \"" + action + "\" }", ok);
    ENCLOUD_ERR_IF (outJson.isNull() || !ok);

    return outJson;
err:
    return "{ \"error\" : \"bad error\" }";
}

}  // namespace encloud
