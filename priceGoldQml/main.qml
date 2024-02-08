import QtQuick 2.15
import QtQuick.Controls 1.4 as C14
import QtQuick.Controls 2.15




ApplicationWindow {
    width: 520
    height: 700
    visible: true
    title: qsTr("History Price Gold")

        PriceTableView {
            anchors.fill: parent
        }

}
