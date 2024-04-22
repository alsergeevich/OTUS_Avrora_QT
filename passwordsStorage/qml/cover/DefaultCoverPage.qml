import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    objectName: "defaultCover"

    CoverPlaceholder {
        objectName: "placeholder"
        text: qsTr("Passwords Storage")
        icon {
            source: Qt.resolvedUrl("../icons/passwordsStorage.svg")
            sourceSize { width: icon.width; height: icon.height }
        }
        forceFit: true
    }
}
