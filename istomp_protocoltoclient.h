#ifndef ISTOMP_PROTOCOLTOCLIENT_H
#define ISTOMP_PROTOCOLTOCLIENT_H

#include <QString>

class ISTOMP_ProtocolToClient
{
public:
    virtual ~ISTOMP_ProtocolToClient() = default;

    //Connection services
    virtual void connectConfirmation(bool status) = 0;
    virtual void disconnectConfirmation(bool status) = 0;
    virtual void disconnectIndication() = 0;

    //Data services
    virtual void sendConfirmation(bool status) = 0;
    virtual void subscribeConfirmation(bool status) = 0;
    virtual void messageConfirmation(bool status) = 0;
    virtual void messageIndication(uint32_t id, QString destination, QString body) = 0;

protected:
    ISTOMP_ProtocolToClient() = default;

};

#endif // ISTOMP_PROTOCOLTOCLIENT_H
