QT += network gui widgets
CONFIG += c++14 console
CONFIG -= app_bundle
HEADERS += \
        istomp_clienttoprotocol.h \
        istomp_protocoltoclient.h \
        stompframe.h
SOURCES += \
        istomp_clienttoprotocol.cpp \
        istomp_protocoltoclient.cpp \
        main.cpp \
        stompframe.cpp
