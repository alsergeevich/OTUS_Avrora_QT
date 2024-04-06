import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.LocalStorage 2.0
import "../assets/Database.js" as Db

Dialog {
    id: dialogCreate
    objectName: "createPage"
    allowedOrientations: Orientation.All
    property string note //свойство для передачи текста заметки
    property int note_id //свойство для передачи значения id заметки
    Column {
        anchors.fill: parent
        DialogHeader {
            acceptText: qsTr("Save")
            cancelText: qsTr("Cancel")
        }
        TextArea { //поле для написания заметки
            id: noteArea
            placeholderText: qsTr("Enter note")
        }
    }

    onAccepted: {
        var id = dialogCreate.insertRecord()
        //если запись создана возвращаем номер записи
        if(id) {
            note = noteArea.text //присваиваем свойству note текст из текстового поля
            note_id = id //присваиваем полю note_id номер записи в БД
        } else {
            statustext.text = qsTr("Failed to insert row")
        }



    }

    //функция в которой вызываем функцию dbInsert из Database.js для добавления записи в БД
    function insertRecord() {
        var rowid = parseInt(Db.dbInsert(noteArea.text), 10)
//        console.log("номер записи в базе" + " " + rowid)
        return rowid;
    }
}
