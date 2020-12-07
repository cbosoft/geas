#pragma once

#include <string>

#include <sqlite3.h>

#include "database_entry/database_entry.hpp"

class Database {
public:
    Database(const std::string &path);
    ~Database();

    DatabaseEntry *get(const std::string &path);

private:

    void connect();
    void disconnect() const;

    static int entry_factory_callback(void *data, int argc, char **argv, char **col);

    std::string _path;
    sqlite3 *_db;
};