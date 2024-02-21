QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    getcoordinatscity.cpp \
    getweathercity.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    getcoordinatscity.h \
    getweathercity.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc


################ Add for SSL 1.1.1 #######################
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/openssl/ -lcrypto
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/openssl/ -lcryptod
else:unix: LIBS += -L$$PWD/openssl/ -lcrypto

INCLUDEPATH += $$PWD/openssl
DEPENDPATH += $$PWD/openssl

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/openssl/libcrypto.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/openssl/libcryptod.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/openssl/crypto.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/openssl/cryptod.lib
else:unix: PRE_TARGETDEPS += $$PWD/openssl/libcrypto.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/openssl/ -lssl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/openssl/ -lssld
else:unix: LIBS += -L$$PWD/openssl/ -lssl

INCLUDEPATH += $$PWD/openssl
DEPENDPATH += $$PWD/openssl

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/openssl/libssl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/openssl/libssld.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/openssl/ssl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/openssl/ssld.lib
else:unix: PRE_TARGETDEPS += $$PWD/openssl/libssl.a

######################################################
