#pragma once
#include <QString>
#include <QPair>
#include <QTextStream>

class STOMPFrame {
  public:
    enum Command {
        INVALID,

        // Client messages
        STOMP, SEND, SUBSCRIBE, UNSUBSCRIBE, BEGIN, COMMIT, ABORT, ACK, NACK, DISCONNECT,

        // Server messages
        CONNECTED, MESSAGE, RECEIPT, ERROR
    };

    explicit STOMPFrame(Command command, std::initializer_list<QPair<QString,QString>> headers = {}, const QByteArray& body = {});

    bool isNull() const {
        return command_ == INVALID;
    }

    Command command() const {
        return command_;
    }

    void setCommand(Command command) {
        command_ = command;
    }

    const QMap<QString, QString>& headers() const {
        return headers_;
    }

    void setHeaders(const QMap<QString, QString>& headers) {
        headers_ = headers;
    }

    const QByteArray& body() const {
        return body_;
    }

    void setBody(const QByteArray& body) {
        body_ = body;
    }

    qint64 send(QIODevice& device);
    static STOMPFrame receive(QIODevice& device);

  private:
    STOMPFrame() = default;

    Command command_ = INVALID;
    QMap<QString,QString> headers_;
    QByteArray body_;
};

QTextStream& operator <<(QTextStream& out, STOMPFrame::Command command);
