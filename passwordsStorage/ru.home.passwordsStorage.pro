TARGET = ru.home.passwordsStorage
QT += sql
CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/backend.cpp \
    src/main.cpp \
    src/passwordmanager.cpp \
    src/xtea.cpp

HEADERS += \
    src/backend.h \
    src/passwordmanager.h \
    src/xtea.h

DISTFILES += \
    qml/pages/CreateRecordDialog.qml \
    qml/pages/DialogPagePasswordSet.qml \
    qml/pages/ListNotesPage.qml \
    qml/pages/SettingsPage.qml \
    rpm/ru.home.passwordsStorage.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.home.passwordsStorage.ts \
    translations/ru.home.passwordsStorage-ru.ts \

RESOURCES += \
    qml/img.qrc
