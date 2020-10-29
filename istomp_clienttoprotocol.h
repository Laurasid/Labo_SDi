#ifndef ISTOMP_CLIENTTOPROTOCOL_H
#define ISTOMP_CLIENTTOPROTOCOL_H

#include <QString>

class ISTOMP_ClientToProtocol
{
public:
    virtual ~ISTOMP_ClientToProtocol() = default;

    //Connection services
    virtual void connectRequest(QString host, uint32_t port, QString username, QString password) = 0;
    virtual void disconnectRequest() = 0;

    //Data services
    virtual void subscribeRequest(uint32_t id, QString destination) = 0;
    virtual void unsubscribeRequest(uint32_t id, QString destination) = 0;
    virtual void sendRequest(QString destination, QString body) = 0;
    virtual void messageResponse(QString destination, QString body) = 0;

protected :
    ISTOMP_ClientToProtocol() = default;
};

#endif // ISTOMP_CLIENTTOPROTOCOL_H
