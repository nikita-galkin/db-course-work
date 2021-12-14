#include <mysql.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class DB {
public:
	static bool start();
	static MYSQL_RES* sendReq(std::string req);
	static void PrintAnswer(MYSQL_RES* res);
	static std::string GetColumnType(std::string Table, std::string Column);
	static std::string mysqlError();
	static void stop();
private:
	static void printLine(std::vector<int> hederlengths);
	static MYSQL* connection;
	static std::string host;
	static unsigned int port;
	static std::string user;
	static std::string password;
	static std::string dbname;
};