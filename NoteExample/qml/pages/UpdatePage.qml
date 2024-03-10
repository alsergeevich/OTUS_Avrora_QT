import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.LocalStorage 2.0
import "../assets/Database.js" as Db

Dialog {
    id: dialogUpdate
    objectName: "updatePage"
    allowedOrientations: Orientation.All
    property string note_u //свойство для передачи из модели и обратно в модель текста заметки
    property int note_id_u //свойство для передачи из модели и обратно в модель id записи
    Column {
        anchors.fill: parent
        DialogHeader {
            acceptText: "Сохранить"
            cancelText: "Отменить"
        }
        TextArea {
            id: noteArea
            text: note_u //устанавливаем в поле ввода старое значение текста заметки
        }
    }

    onAccepted: {
            updateRec() //если нажали Сохранить обновляем запись в БД
        }

    //функция обновления записи в БД
    function updateRec() {
        Db.dbUpdate(note_id_u, noteArea.text)

        //тут мы обновляем свойство note_u для обновления его в модели
        note_u = noteArea.text
    }

}

