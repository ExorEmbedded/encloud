#ifndef _ENCLOUD_HTTP_SERVER_H_
#define _ENCLOUD_HTTP_SERVER_H_

#include <QTcpServer>
#include <QByteArray>
#include "abstracthandler.h"

// default port in case nothing is written to registry
#define ENCLOUD_SRV_PORT_DFT 8081

namespace encloud {

class HttpServer : public QTcpServer
{
    Q_OBJECT

public:
    HttpServer (QObject *parent = 0);
    ~HttpServer ();

    int setHandler (HttpAbstractHandler *handler);

    int start ();
    int stop ();

protected:
    void incomingConnection (int sd);

private slots:
    void readyRead ();
    void disconnected ();
    void error (QAbstractSocket::SocketError socketError);

private:
    QByteArray handleMessage (QByteArray message);
    QVariant handleJson (QVariant json);

    QTcpSocket *_socket;
    HttpAbstractHandler *_handler;
};

}  // namespace encloud

#endif  // _ENCLOUD_HTTP_SERVER_H_
