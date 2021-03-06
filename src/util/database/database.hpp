#pragma once

#include <string>

#include <sqlite3.h>

#include "database_entry/database_entry.hpp"

class Database {
public:
    Database(const std::string &path);
    ~Database();

    DatabaseEntry *get(const std::string &path);
    std::vector<DatabaseEntry *> get_matching(const std::string &pattern);

private:

    void connect();
    void disconnect() const;

    std::string _path;
    sqlite3 *_db;
};