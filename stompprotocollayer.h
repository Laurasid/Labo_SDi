#ifndef STOMPPROTOCOLLAYER_H
#define STOMPPROTOCOLLAYER_H

#include "istomp_clienttoprotocol.h"
#include "istomp_protocoltoclient.h"

class STOMPProtocolLayer : public ISTOMP_ClientToProtocol
{
public:
    STOMPProtocolLayer();
    ~STOMPProtocolLayer();

    inline void initRelations(ISTOMP_ProtocolToClient* Client){_client = Client;}

    //Connection services
    void connectRequest(QString host, QString port, QString username, QString password);
    void disconnectRequest();

    //Data services
    void subscribeRequest(QString id, QString destination);
    void unsubscribeRequest(QString id, QString destination);
    void sendRequest(QString destination, QString body);
    void messageResponse(QString destination, QString body);

private:
    ISTOMP_ProtocolToClient* _client;
};

#endif // STOMPPROTOCOLLAYER_H
