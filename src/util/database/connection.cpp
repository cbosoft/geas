#include "database.hpp"

void Database::connect()
{
    const char *path = this->_path.c_str();
    int rc = sqlite3_open(path, &this->_db);

    if (rc) {
        // TODO error
    }
}

void Database::disconnect() const
{
    sqlite3_close(this->_db);
}

DatabaseEntry *Database::get(const std::string &path)
{
    std::string command = "SELECT * FROM Resources WHERE Path=\"" + path + "\";";
    const char *cmd = command.c_str();

    sqlite3_stmt *s = nullptr;
    if (sqlite3_prepare_v2(this->_db, cmd, command.size(), &s, 0) != SQLITE_OK) {
        // TODO ERROR
    }

    int result = sqlite3_step(s);
    if (result != SQLITE_ROW) {
        // TODO error
    }

    // column 0: id
    //int id = sqlite3_column_int(s, 0);

    // column 1: path
    std::string data_path((const char *)sqlite3_column_text(s, 1));

    // column 2: data blob
    std::vector<char> data;
    if (sqlite3_column_type(s, 2) != SQLITE_NULL) {
        int data_size = sqlite3_column_bytes(s, 2);
        auto *data_raw = (char *) sqlite3_column_blob(s, 2);
        for (int i = 0; i < data_size; i++)
            data.push_back(data_raw[i]);
    }

    // column 3: metadata
    std::string meta;
    if (sqlite3_column_type(s, 3) != SQLITE_NULL) {
        auto *meta_raw = (const char *)sqlite3_column_text(s, 3);
        meta = meta_raw;
    }

    auto *ent = new DatabaseEntry(data_path, data, meta);
    return ent;
}