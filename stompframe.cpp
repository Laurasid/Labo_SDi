#include "stompframe.h"
#include <QTextStream>
#include <QtDebug>

STOMPFrame::STOMPFrame(Command command, std::initializer_list<QPair<QString, QString>> headers, const QByteArray& body):
    command_(command), body_(body) {
    for (const auto& header: headers) {
        headers_[header.first] = header.second;
    }
}

qint64 STOMPFrame::send(QIODevice& device) {
    QByteArray encoded;
    QTextStream out {&encoded};
    out << command_ << "\n";
    for (const auto& key: headers_.keys()) {
        out << key << ":" << headers_[key] << "\n";
    }
    if (!headers_.contains("content-length")) {
        out << "content-length" << ":" << body_.size() << "\n";
    }
    out << "\n" << body_ << '\0';
    out.flush();
    return device.write(encoded);
}

STOMPFrame STOMPFrame::receive(QIODevice& device) {
    STOMPFrame frame;
    QTextStream in(&device);

    QString commandStr;
    if (!in.readLineInto(&commandStr)) {
        return {};
    }
    if (commandStr == "STOMP") {
        frame.command_ = STOMPFrame::STOMP;
    } else if (commandStr == "SEND") {
        frame.command_ = STOMPFrame::SEND;
    } else if (commandStr == "SUBSCRIBE") {
        frame.command_ = STOMPFrame::SUBSCRIBE;
    } else if (commandStr == "UNSUBSCRIBE") {
        frame.command_ = STOMPFrame::UNSUBSCRIBE;
    } else if (commandStr == "BEGIN") {
        frame.command_ = STOMPFrame::BEGIN;
    } else if (commandStr == "COMMIT") {
        frame.command_ = STOMPFrame::COMMIT;
    } else if (commandStr == "ABORT") {
        frame.command_ = STOMPFrame::ABORT;
    } else if (commandStr == "ACK") {
        frame.command_ = STOMPFrame::ACK;
    } else if (commandStr == "NACK") {
        frame.command_ = STOMPFrame::NACK;
    } else if (commandStr == "DISCONNECT") {
        frame.command_ = STOMPFrame::DISCONNECT;
    } else if (commandStr == "CONNECTED") {
        frame.command_ = STOMPFrame::CONNECTED;
    } else if (commandStr == "MESSAGE") {
        frame.command_ = STOMPFrame::MESSAGE;
    } else if (commandStr == "RECEIPT") {
        frame.command_ = STOMPFrame::RECEIPT;
    } else if (commandStr == "ERROR") {
        frame.command_ = STOMPFrame::ERROR;
    } else {
        return {};
    }

    QString headerLine;
    while (in.readLineInto(&headerLine) && headerLine != "") {
        auto components = headerLine.split(':');
        if (components.count() != 2) {
            return {};
        }
        frame.headers_.insert(components[0].trimmed(), components[1].trimmed());
    }

    if (frame.headers_.contains("content-length")) {
        bool conversionOk;
        qint64 length = frame.headers_["content-length"].toLongLong(&conversionOk);
        if (!conversionOk) {
            return {};
        }
        while (frame.body_.length() < length) {
            frame.body_ += in.read(length - frame.body_.length()).toUtf8();
        }
    } else {
        in >> frame.body_;
    }

    return frame;
}

QTextStream& operator <<(QTextStream& out, STOMPFrame::Command command) {
    switch (command) {
        case STOMPFrame::INVALID:
            break;

        case STOMPFrame::STOMP:
            out << "STOMP";
            break;

        case STOMPFrame::SEND:
            out << "SEND";
            break;

        case STOMPFrame::SUBSCRIBE:
            out << "SUBSCRIBE";
            break;

        case STOMPFrame::UNSUBSCRIBE:
            out << "UNSUBSCRIBE";
            break;

        case STOMPFrame::BEGIN:
            out << "BEGIN";
            break;

        case STOMPFrame::COMMIT:
            out << "COMMIT";
            break;

        case STOMPFrame::ABORT:
            out << "ABORT";
            break;

        case STOMPFrame::ACK:
            out << "ACK";
            break;

        case STOMPFrame::NACK:
            out << "NACK";
            break;

        case STOMPFrame::DISCONNECT:
            out << "DISCONNECT";
            break;

        case STOMPFrame::CONNECTED:
            out << "CONNECTED";
            break;

        case STOMPFrame::MESSAGE:
            out << "MESSAGE";
            break;

        case STOMPFrame::RECEIPT:
            out << "RECEIPT";
            break;
        case STOMPFrame::ERROR:
            out << "ERROR";
            break;
    }
    return out;
}
