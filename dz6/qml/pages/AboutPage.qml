import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "aboutPage"
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("Информация о пользователе")
    }
    Column {
        id: columnSelfLayout
        objectName: "columnSelfLayout"
        anchors.centerIn: parent
        width: parent.width
        spacing: 5

        TextField {
            id: surnameField
            objectName: "surnameField"
            width: parent.width
            placeholderText: qsTr("Фамилия")

        }
        TextField {
            id: nameField
            objectName: "nameField"
            width: parent.width
            placeholderText: qsTr("Имя")
        }
        TextField {
            id: lastnameField
            objectName: "lastnameField"
            width: parent.width
            placeholderText: qsTr("Отчество")
        }
        Label {
            width: parent.width
            text: qsTr("Выберите ЯП которые вы знаете:")
        }
        TextSwitch{
            width: page.width
            text: qsTr("C/C++")
        }
        TextSwitch{
            width: page.width
            text: qsTr("Python")
        }
        TextSwitch{
            width: page.width
            text: qsTr("Java")
        }
        Row {
            width: parent.width
            spacing: 5
            Label {
                text: qsTr("Согласен на обработку данных ")
            }
            TextSwitch {
                text: checked ? qsTr("Да") : qsTr("Нет")
            }
        }
        Row {
            width: parent.width
            spacing: 5
            Label {
                text: qsTr("Согласен на рассылку")
            }
            TextSwitch {
                text: checked ? qsTr("Да") : qsTr("Нет")
            }
        }

    }
}
