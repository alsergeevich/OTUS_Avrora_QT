import QtQuick 2.0
import Sailfish.Silica 1.0
import passwordmanager 1.0

Page {
    id: mainPage
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    backNavigation: false    

    PasswordManager {
        id: passwordManager
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        spacing: Theme.paddingLarge
        PageHeader {
            id: pheader
            title: qsTr("Вход в хранилище")
        }

        TextField {
            id: txtfield

            placeholderText: qsTr("введите ключ пароль")
        }

        Label {
            id: lblError
            anchors.horizontalCenter: parent.horizontalCenter
            height: txtfield.height
            font.pixelSize: Theme.fontSizeLarge
            color: "red"
            text: ""
        }
        Button {
            id: btn
            anchors.horizontalCenter: parent.horizontalCenter
            preferredWidth: Theme.buttonWidthMedium
            text: qsTr("Расшифровать")

            onClicked: {

                if(passwordManager.comparePasswords(txtfield.text)) {
                    lblError.text = ""
                    pageStack.push(Qt.resolvedUrl("ListNotesPage.qml"), {"temp_passw": txtfield.text})
                }
                else {
                    lblError.text = qsTr("неверный пароль")
                }
            }
        }


//        Button {
//            id: btn1

//            preferredWidth: Theme.buttonWidthMedium
//            text: qsTr("Удалить табл")

//            onClicked: {
//                passwordManager.dropTable()
//            }
//        }
    }



//    Component.onCompleted: {
//        console.log("Load_M")
//    }

}
