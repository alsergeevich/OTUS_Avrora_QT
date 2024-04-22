import QtQuick 2.0
import Sailfish.Silica 1.0
import passwordmanager 1.0

ApplicationWindow {
    objectName: "applicationWindow"
    PasswordManager {
        id: passwordManager
    }
    initialPage: passwordManager.isFirstRun() ? Qt.resolvedUrl("pages/DialogPagePasswordSet.qml") :Qt.resolvedUrl("pages/MainPage.qml")
    cover: Qt.resolvedUrl("cover/DefaultCoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
}

