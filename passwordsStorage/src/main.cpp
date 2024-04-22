#include <auroraapp.h>
#include <QtQuick>
#include "passwordmanager.h"


int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.home"));
    application->setApplicationName(QStringLiteral("passwordsStorage"));
    qmlRegisterType<PasswordManager>("passwordmanager", 1, 0, "PasswordManager");
    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/passwordsStorage.qml")));
    view->show();

    return application->exec();
}
