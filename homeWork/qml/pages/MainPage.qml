import QtQuick 2.0
import Sailfish.Silica 1.0
import myClass 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    MyClass {
        id: myclass
    }

    Button {
        id: btn
        anchors.centerIn: parent
        text: "Click Me!"
        preferredWidth: Theme.buttonWidthMedium

        onClicked: {
            myclass.notification()
        }

    }
}
