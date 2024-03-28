TARGET = ru.auroraos.homeWork

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    myclass.cpp \
    src/main.cpp \

HEADERS += \
    myclass.h

DISTFILES += \
    rpm/ru.auroraos.homeWork.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n
QT += dbus

TRANSLATIONS += \
    translations/ru.auroraos.homeWork.ts \
    translations/ru.auroraos.homeWork-ru.ts \
