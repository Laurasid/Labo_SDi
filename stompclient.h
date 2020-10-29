#ifndef STOMPCLIENT_H
#define STOMPCLIENT_H

#include "istomp_protocoltoclient.h"
#include "istomp_clienttoprotocol.h"
#include <qcryptographichash.h>

class STOMPClient : public ISTOMP_ProtocolToClient
{

public:
    STOMPClient();
    ~STOMPClient();

    inline void initRelation(ISTOMP_ClientToProtocol* ProtocolLayer){_protocolLayer = ProtocolLayer;}

    //Connection services
    void connectConfirmation(bool status);
    void disconnectConfirmation(bool status);
    void disconnectIndication();

    //Data services
    void sendConfirmation(bool status);
    void subscribeConfirmation(bool status);
    void unsubscribeConfirmation(bool status);
    void messageConfirmation(bool status);
    void messageIndication(QString id, QString destination, QString body);

    inline bool isConnected(){return _isConnected;}
    inline QString getID(){return ID;}

private:

    //Client information
    static const QString host;
    static const QString port;
    static const QString ID;
    static const QString username;

    bool _isConnected;
    bool _sendStatus;
    bool _subscribeStatus;
    bool _messageStatus;

    QString destinationTemp;
    QString bodyTemp;

    ISTOMP_ClientToProtocol* _protocolLayer;
};

#endif // STOMPCLIENT_H
