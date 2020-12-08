#include "database.hpp"
#include "../exception.hpp"

void Database::connect()
{
    const char *path = this->_path.c_str();
    int rc = sqlite3_open(path, &this->_db);

    if (rc) {
        throw SQLiteError(Formatter() << "Could not connect to database \"" << this->_path << "\".");
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
        throw SQLiteError(Formatter() << "Error preparing SQLite statement \"" << command << "\" (" << sqlite3_errmsg(this->_db) << ").");
    }

    int result = sqlite3_step(s);
    if (result != SQLITE_ROW) {
        throw SQLiteError(Formatter() << "Error reading SQLite query result: result not a row. The specified entry does not exist in the database.");
    }

    auto *ent = new DatabaseEntry(s);
    return ent;
}


std::vector<DatabaseEntry *> Database::get_matching(const std::string &pattern)
{
    std::string command = "SELECT * FROM Resources WHERE Path LIKE \"" + pattern + "\";";
    const char *cmd = command.c_str();

    sqlite3_stmt *s = nullptr;
    if (sqlite3_prepare_v2(this->_db, cmd, command.size(), &s, nullptr) != SQLITE_OK) {
        throw SQLiteError(Formatter() << "Error preparing SQLite statement \"" << command << "\" (" << sqlite3_errmsg(this->_db) << ").");
    }

    int result = sqlite3_step(s);
    if (result != SQLITE_ROW) {
        throw SQLiteError(Formatter() << "Error reading SQLite query result: result not a row. The specified entry does not exist in the database.");
    }

    std::vector<DatabaseEntry *> rv;
    while (result == SQLITE_ROW) {
        auto *ent = new DatabaseEntry(s);
        rv.push_back(ent);
        result = sqlite3_step(s);
    }

    return rv;
}
