import QtQuick 2.0
import Sailfish.Silica 1.0
import passwordmanager 1.0


Page {
    id: passwPage
    objectName: "passwPage"
    allowedOrientations: Orientation.All
    PasswordManager {
        id: passwordManager
    }

    Column {
        width: parent.width
        spacing: Theme.paddingLarge
        PageHeader {
            id: pheader
            title: qsTr("Задайте ключ")
        }

        TextField {
            id: txtFieldPassw

            placeholderText: qsTr("введите ключ пароль")
        }

        Button {
            id: btn1
            anchors.horizontalCenter: parent.horizontalCenter
            preferredWidth: Theme.buttonWidthMedium
            text: qsTr("Сохранить")
            enabled: txtFieldPassw.text.length >= 6

            onClicked: {
                 passwordManager.saveEncryptionKey(txtFieldPassw.text)
                 pageStack.push(Qt.resolvedUrl("MainPage.qml"))
            }
        }

    }


}

