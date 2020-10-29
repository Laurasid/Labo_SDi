#include "stompclient.h"

STOMPClient::STOMPClient()
{
    host = "sdi.hevs.ch";
    port = "61614";
    ID = "1703";
    username = "sdi09";
    static const auto password = QCryptographicHash::hash(username.toUtf8(),QCryptographicHash::Md5).toHex().toLower();
}

STOMPClient::~STOMPClient()
{
    _isConnected = false;
}

void STOMPClient::connectConfirmation(bool status)
{
    _isConnected = status;
}

void STOMPClient::disconnectConfirmation(bool status)
{
    _isConnected = !status;
}

void STOMPClient::disconnectIndication()
{
    _isConnected = false;
}

void STOMPClient::sendConfirmation(bool status)
{
    _sendStatus = status;
}

void STOMPClient::subscribeConfirmation(bool status)
{
    _subscribeStatus = status;
}

void STOMPClient::unsubscribeConfirmation(bool status)
{
    _subscribeStatus = !status;
}

void STOMPClient::messageConfirmation(bool status)
{
    _messageStatus = status;
}

void STOMPClient::messageIndication(QString id, QString destination, QString body)
{
    if(id==ID){
        destinationTemp = destination;
        bodyTemp = body;
    }
}
