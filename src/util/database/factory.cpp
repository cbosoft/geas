#include "database.hpp"

int Database::entry_factory_callback(void *data, int argc, char **argv, char **col)
{
    auto **dbent_ptrptr = (DatabaseEntry**)data;
    (*dbent_ptrptr) = new DatabaseEntry(argc, argv, col);

    // this is only called once per SELECT statement
    // guaranteed as the only SELECT statement provided
    // selects based on the path, which is UNIQUE.

    return 0;
}