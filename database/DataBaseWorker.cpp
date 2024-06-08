#include "DataBaseWorker.h"
//#include <format>
#include <iostream>
#include <boost/algorithm/string.hpp>

DataBaseWorker::DataBaseWorker(): db_name("Cars") {}

DataBaseWorker::~DataBaseWorker()
{
  std::string sql{"DROP TABLE IF EXISTS user;"};
  sql.append(db_name);
  sql.append(";");
  sqlite3_exec(db, sql.data(), nullptr, nullptr, nullptr);
  sqlite_check(sqlite3_close(db));
}

std::string DataBaseWorker::operator()(std::string data) 
{
  std::vector<std::string> lines;
  boost::split(lines, data, boost::algorithm::is_space());
  std::string result;
  if(!lines.empty() && (lines.size() == 4))
  {
      result = add_mes(lines);
  }
  return result;
}

std::string DataBaseWorker::add_mes(const std::vector<std::string>&mes)
{
  if(create_table_stmt == nullptr) return "Table is not created";
  sqlite_check(sqlite3_open("db", &db));
  char* errmsg{};
  std::string sql{mes.at(0)};
  sql.append(" INTO ");
  sql.append(db_name);
  sql.append(" VALUES (");
  sql.append(mes[2]);
  sql.append(", '");
  sql.append(mes[3]);
  sql.append("');");
  int res = sqlite3_exec(db, sql.data(),
                     nullptr, nullptr, &errmsg);
  if(res != SQLITE_OK)
  {
    return std::string(errmsg);
  }
  return "OK";
}

int DataBaseWorker::sqlite_check(int code, const char *msg, int expected)
{
  if (code != expected)
  {
    sqlite_throw(code, msg);
  }
  return code;
}

void DataBaseWorker::sqlite_throw(int code, const char *msg)
{
  std::cout<<"SQL Method failed"<< sqlite3_errstr(code)<< msg;
  std::abort();
}

void DataBaseWorker::sqlite_check_with_mes(int code, const char* msg, int expected)
{
  std::string result_str(msg);
  if (code == expected)
  {
    result_str.clear();
    result_str.append("OK");
  }
}

void DataBaseWorker::start_db()
{
  sqlite_check(sqlite3_open("db", &db));
  {
    std::string sql{"CREATE TABLE IF NOT EXISTS "};
    sql.append(db_name);
    sql.append("(id INTEGER PRIMARY KEY,name VARCHAR(255) NOT NULL);");
    const char *stmt_tail;
    if (sqlite3_prepare_v2(db, sql.data(), sql.size(), &create_table_stmt,
                           &stmt_tail) != SQLITE_OK)
    {
      std::cerr << "Error preparing statement: "<<
                               sqlite3_errmsg(db)
                << "\n";
    }

    int res = 0;
    do
    {
      res = sqlite3_step(create_table_stmt);
      if (res == SQLITE_ROW)
      {
      }
      else if (res == SQLITE_DONE)
      {
        // ok
      }
      else
      {
        sqlite_throw(res);
      }
    } while (res != SQLITE_DONE);

    sqlite_check(sqlite3_finalize(create_table_stmt));
  }
  std::cout<<"Data Base Open \n";
}