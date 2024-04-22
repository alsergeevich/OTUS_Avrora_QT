import QtQuick 2.0
import Sailfish.Silica 1.0
import passwordmanager 1.0




Page {
    id: page
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    property string temp_passw
    property string count_records
    backNavigation: false
    PasswordManager {
        id: passwordManager
    }

        SilicaListView {
            id: noteList
            clip: true
            anchors.top: btn2.bottom
            anchors.margins: 10
            width: parent.width
            spacing: 20
            anchors.bottom: parent.bottom
            model: ListModel {id: listmodel }
            delegate: ListItem {
                anchors.left: parent.left
                anchors.right: parent.right
                height:  150 + (contextmenu.visible ? contextmenu.height : 20)
                anchors.margins: 20
                menu: ContextMenu {
                    id: contextmenu
                    MenuItem {
                        text: qsTr("редактировать")
                        onClicked: {
                            var dialog = pageStack.push(Qt.resolvedUrl("CreateRecordDialog.qml"))
                            var id = parseInt(rowid)
                            dialog.url = url
                            dialog.login = login
                            dialog.password = passwordManager.getDecriptionPassword(password, passwordManager.getEncryptionKey());
                            dialog.onAccepted.connect(function () { passwordManager.updateRecord(id, dialog.url, dialog.login, dialog.password)})
                        }
                    }
                    MenuItem {
                        text: qsTr("удалить")
                        onClicked: {
                            var id = parseInt(rowid)
                            console.log("id = " + id)
                            if(passwordManager.deleteRecord(id)) {
                                console.log("Deleting success")
                            }
                            else {
                                console.log("Error deleting record")
                            }
                        }
                    }
                }


                Rectangle {
                        id: rect
                        color: "transparent" // Прозрачный фон
                        border.color: Theme.secondaryColor
                        border.width: 1
                        radius: 10

                        width: parent.width
                        height: txt1.height * 3 + 20

                        Rectangle {
                                color: "transparent"
                                width: parent.width - 20  // Учитываем отступы
                                 height: parent.height - 20  // Учитываем отступы
                                 anchors.centerIn: parent

                    Column {

                        anchors.left: parent.left
                        anchors.right: parent.right

                        spacing: 1


                        Label {
                            id: txt1

                            text: qsTr("Url:                 ") + url
                            font.pixelSize: Theme.fontSizeMedium
                            color: Theme.primaryColor
                        }

                        Label {
                            id: txt2

                            text: qsTr("Login:            ") + login
                            font.pixelSize: Theme.fontSizeMedium
                            color: Theme.primaryColor

                        }

                        Label {
                            id: txt3

                            text: qsTr("Password:   ") + passwordManager.getDecriptionPassword(password, passwordManager.getEncryptionKey());
                            font.pixelSize: Theme.fontSizeMedium
                            color: Theme.primaryColor

                        }
                    }
                 }
             }

            }


            Connections {
                target: passwordManager
                onModelChanged: readAll()
            }

            VerticalScrollDecorator { }

        }
        PageHeader {
            id: pheader
            title: qsTr("Всего записей: ") + count_records
        }
        SearchField {
                id: txtSearch
                anchors.top: pheader.bottom
                anchors.topMargin: 5
                placeholderText: qsTr("поиск по логину или url")

            }
        IconButton {
            id: btn1
            anchors.top: txtSearch.bottom
            anchors.left: parent.left
            anchors.topMargin: 5
            icon.source: "qrc:/image/add.png"
            icon.scale: 0.4
            onClicked: {
                var dialog = pageStack.push(Qt.resolvedUrl("CreateRecordDialog.qml"))
                dialog.onAccepted.connect(function () { passwordManager.insertRecord(dialog.url, dialog.login, dialog.password)})
            }
        }

        IconButton {
            id: btn2
            anchors.top: txtSearch.bottom
            anchors.right: parent.right
            anchors.topMargin: 5
            icon.source: "qrc:/image/set.png"
            icon.scale: 0.4
            onClicked: {
                var dialog = pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
                dialog.onAccepted.connect(function () { passwordManager.insertRecord(dialog.url, dialog.login, dialog.password)})
            }
        }

    function readAll() {
        var record = passwordManager.getRecords()
        count_records = String(record.length)
        console.log("length: " + record.length)
        listmodel.clear()
        for(var i = 0; i < record.length; ++i) {
            listmodel.append({"rowid": record[i][0], "url": record[i][1], "login": record[i][2], "password": record[i][3] });
        }
    }

    Component.onCompleted: {
        readAll()
    }

}

//passwordManager.getDecriptionPassword(password, temp_passw);
