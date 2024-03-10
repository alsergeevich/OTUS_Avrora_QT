import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.LocalStorage 2.0
import "../assets/Database.js" as Db

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent
        model: ListModel {id: noteModel}
        delegate: ListItem {
            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Изменить")
                    onClicked: {
                        var dialog = pageStack.push(Qt.resolvedUrl("UpdatePage.qml")) //переход на страницу редактирования записи
                        dialog.note_u = note //передаём в свойство страницы редактирования значения из записи
                        dialog.note_id_u = note_id
                        dialog.onAccepted.connect(function () {
                            //два способа обновления модели
                            //второй как мне кажется эффективнее так как не читается вся база.

                            //1.производим обновление модели через чтение записей из базы
//                            Db.dbReadAll()

                            //2.сначала удаляем старую запись
                            noteModel.remove(index)
                            //затем добавляем обновлённую запись
                            noteModel.append({"note": dialog.note_u, "note_id": dialog.note_id_u})

                        });
                    }
                }
                MenuItem {
                    text: qsTr("Удалить")
                    onClicked: {
                        //получаем rowid из модели
                        var rowid = parseInt(note_id)
//                        console.log("rowid = " + rowid)

                        //удаляем запись из базы
                        Db.dbDelete(rowid)
                        //удаляем запись из модели
                        noteModel.remove(index)

                    }
                }
            }

            Label {
                text: note
            }
        }
        header: PageHeader {
            objectName: "pageHeader"
            title: qsTr("Список заметок")
        }

        PullDownMenu {
            quickSelect: true
            MenuItem {
                text: "Добавить заметку"
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("CreateNoteDialog.qml")) //переход на страницу создания записи
                    dialog.onAccepted.connect(function () {
                        noteModel.append({"note": dialog.note, "note_id": dialog.note_id}) //добавляем в модель созданную запись
                    });
                }
            }
        }
    }

    Component.onCompleted: {
        Db.dbInit()
        Db.dbReadAll()

    }
}
