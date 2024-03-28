#include <auroraapp.h>
#include <QtQuick>
#include "myclass.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("homeWork"));
    qmlRegisterType<MyClass>("myClass", 1, 0, "MyClass");
    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/homeWork.qml")));
    view->show();

    return application->exec();
}
