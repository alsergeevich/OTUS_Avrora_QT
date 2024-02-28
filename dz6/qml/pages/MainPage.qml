import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    PageHeader {
        objectName: "pageHeader"
        title: qsTr("Регистрация")
    }

    Column {
        id: columnRegLayout
        objectName: "columnRegLayout"
        anchors.centerIn: parent
        width: parent.width

            TextField {
                objectName:  "numberPhoneField"
                placeholderText: qsTr("Введите номер телефона")
                width: parent.width
                inputMethodHints: Qt.ImhDialableCharactersOnly
            }

            TextField {
                objectName: "loginField"
                placeholderText: qsTr("Введите имя пользователя")
                width: parent.width
                validator: RegExpValidator {
                    regExp: /^[a-z][a-z0-9_-]{2,15}$/
                }
                inputMethodHints: Qt.ImhNoAutoUppercase
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Зарегистрироваться")
                preferredWidth: Theme.buttonWidthMedium
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }

    }
}


