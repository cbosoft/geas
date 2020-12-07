#include "database.hpp"

Database::Database(const std::string &path)
    :   _path(path)
    ,   _db(nullptr)
{
    this->connect();
}

Database::~Database()
{
    this->disconnect();
}

