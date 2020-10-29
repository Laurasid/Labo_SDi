QT += network gui widgets
CONFIG += c++14 console
CONFIG -= app_bundle
HEADERS += \
        istomp_clienttoprotocol.h \
        istomp_protocoltoclient.h \
        stompclient.h \
        stompframe.h \
        stompprotocollayer.h
SOURCES += \
        main.cpp \
        stompclient.cpp \
        stompframe.cpp \
        stompprotocollayer.cpp
