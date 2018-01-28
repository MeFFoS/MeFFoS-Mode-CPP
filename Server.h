#pragma once
#include <string>
#include "sampgdk.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class Server
{
public:
	Server();
	~Server();
	bool LoadInform();
	void ConnectMySQL();
	string name,
		mysqlIp,
		mysqlLogin,
		mysqlPassword,
		mysqlBd;
	string  salt = "ASVsaB13C";
	sql::Driver *driver;
	sql::Connection *con;
	//sql::Statement *stmt;
	//sql::ResultSet *res;
	
	sql::ConnectOptionsMap connection_properties;
};