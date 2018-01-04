#pragma once
//#include "Player.cpp"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;
class Player
{
public: 
	void Connect(string playerName, int playerId);
	void Disconnect();
	void SaveAccount();
	void LoadAccount(sql::ResultSet *result);
	void AddAccount();
	void Registration();
	void Authorization();
	void Clear();
	int id;
	string name;
	string password;
	int level;
	bool auth = false;
};