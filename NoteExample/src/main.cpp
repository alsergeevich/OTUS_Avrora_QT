#include <auroraapp.h>
#include <QtQuick>

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("NoteExample"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/NoteExample.qml")));
    view->show();

    return application->exec();
}