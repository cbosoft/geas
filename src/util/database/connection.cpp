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

    char *err = nullptr;
    DatabaseEntry *ent = nullptr;
    const char *cmd = command.c_str();
    int rc = sqlite3_exec(this->_db, cmd, &Database::entry_factory_callback, (void *)&ent, &err);

    if (rc) {
        // TODO error
        sqlite3_free(err);
    }

    return ent;
}