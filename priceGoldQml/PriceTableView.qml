import QtQuick 2.15
import QtQuick.Controls 1.4 as C14

C14.TableView {
    id: tableview
    model: myModel

    //функция в которой по метке узнаём какую иконку необходимо установить, другого решения я не нашёл, если есть решение без JS буду признателен за пример.
    function getIcon(iconRole) {
        var str = iconRole

        if (str[0] === "+") {
            return "qrc:/icons/uparrow.ico"
        }
        if (str[0] === "-") {
            return "qrc:/icons/arrowdown.ico"
        }
        if (str[0] === "*") {
            return "qrc:/icons/neutral_price.ico"
        }
    }

    //функция в которой мы удаляем первый символ-метку для иконки, тоже не придумал как это сделать по другому.
    function delFirsChar(str) {
        const s = str
        const new_str = s.substr(1)
        return new_str
    }

    C14.TableViewColumn {
        title: "Дата"
        width: 200
        delegate: Text {
            id: colDate
            text: model.date
            leftPadding: 20
            font.pointSize: 12
        }
    }

    C14.TableViewColumn {
        title: "Цена покупки"
        width: 150
        delegate: Text {
            id: colPurchase
            text: delFirsChar(model.purchase)
            leftPadding: 30
            font.pointSize: 12

            Image {
                id: image1
                anchors.top: parent.top
                anchors.right: parent.right
                source: getIcon(model.purchase)
                width: 12
                height: 12
            }
        }
    }

    C14.TableViewColumn {
        title: "Цена продажи"
        width: 150
        delegate: Text {
            id: colSell
            text: delFirsChar(model.sell)
            leftPadding: 30
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 12

            Image {
                id: image2
                anchors.top: parent.top
                anchors.right: parent.right
                source: getIcon(model.sell)
                width: 12
                height: 12
            }
        }
    }

}
