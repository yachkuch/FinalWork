#ifndef __DATA_BASE_WORKER_H_PI4UISGSM1VT__
#define __DATA_BASE_WORKER_H_PI4UISGSM1VT__
#include <boost/signals2.hpp>
#include <sqlite3.h>
#include <vector>
#include <string>
///////////////////////////////////////////////////////////
/// @brief DataBaseWorker
///
class DataBaseWorker  final
{
public:
    DataBaseWorker();
    virtual ~DataBaseWorker();

    void start_db();
    std::string operator()(std::string str);

    
private:
    /// @brief Указатель на бд 
    sqlite3* db = nullptr;
    
    sqlite3_stmt* create_table_stmt = nullptr;
    sqlite3_stmt* create_table_stmt2 = nullptr;

    std::string add_mes( sqlite3_stmt  *stmt, std::string db_name, const std::vector<std::string>&mes );

    int sqlite_check(int code, const char* msg = "", int expected = SQLITE_OK);
    void sqlite_throw(int code, const char* msg = "");
    void sqlite_check_with_mes(int code, const char* msg = "", int expected = SQLITE_OK);

};

#endif  // __DATA_BASE_WORKER_H_PI4UISGSM1VT__
