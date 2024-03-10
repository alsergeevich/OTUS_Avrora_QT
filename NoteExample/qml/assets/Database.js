function dbInit()
{
    var db = LocalStorage.openDatabaseSync("Note_DB", "", "Notebook", 1000000)
    try {
        db.transaction(function (tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS note_list (note text)')

        })
    } catch (err) {
        console.log("Error creating table in database: " + err)
    };
}

function dbGetHandle()
{
    try {
        var db = LocalStorage.openDatabaseSync("Note_DB", "",
                                               "Notebook", 1000000)
    } catch (err) {
        console.log("Error opening database: " + err)
    }
    return db
}

function dbInsert(Pnote)
{
    var db = dbGetHandle()
    var rowid = 0;
    db.transaction(function (tx) {
        tx.executeSql('INSERT INTO note_list VALUES(?)',
                      [Pnote])
        var result = tx.executeSql('SELECT last_insert_rowid()')
        rowid = result.insertId
    })
    return rowid;
}

function dbReadAll()
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql(
                    'SELECT rowid, note FROM note_list order by rowid desc')
        noteModel.clear()
        for (var i = 0; i < results.rows.length; i++) {
            noteModel.append({
                                 note_id:results.rows.item(i).rowid,
                                 note: results.rows.item(i).note,

                             })
        }
    })
}

function dbUpdate(Prowid, Pnote)
{
//    console.log("id " + Prowid + " Note " + Pnote)
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql(
                    'update note_list set note=? where rowid = ?', [Pnote, Prowid])
    })
}

function dbDelete(Prowid)
{
//    console.log("Удаляем строку " + Prowid)
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql(
                    'delete from note_list where rowid = ?', [Prowid])
    })
}
