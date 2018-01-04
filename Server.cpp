#pragma once
#include <iostream>
#include <fstream>
#include "Server.h"

Server::Server()
{
	setlocale(LC_CTYPE, "rus");
	if (LoadInform()) sampgdk::logprintf(" Данные успешно загружены");
	else {
		sampgdk::logprintf(" Данные не загружены");
		SendRconCommand("exit");
	}
	ConnectMySQL();
}
Server::~Server()
{
	setlocale(LC_CTYPE, "rus");
	con->close();
	sampgdk::logprintf(" Сервер выключен");
}
void Server::ConnectMySQL()
{
	connection_properties["hostName"] = mysqlIp;
	connection_properties["userName"] = mysqlLogin;
	connection_properties["password"] = mysqlPassword;
	connection_properties["schema"] = mysqlBd;
	connection_properties["port"] = 3306;
	connection_properties["OPT_RECONNECT"] = true;
	driver = get_driver_instance();
	try 
	{
		setlocale(LC_CTYPE, "rus");
		con = driver->connect(connection_properties);
		sampgdk::logprintf(" Подключение к базе данных удачно");
	}
	catch(exception &e)
	{
		sampgdk::logprintf(" MySQL error: %s", e.what());
	}
}

bool Server::LoadInform()
{
	setlocale(LC_CTYPE, "rus");
	ifstream inFile;
	string temp;
	inFile.open("scriptfiles/config.ini", ios_base::in);
	if (!inFile.is_open()) 		// если файл не открыт
	{
		sampgdk::logprintf("Файл не может быть открыт!"); // сообщить об этом
		return false;
	}
	else 
	{
		inFile >> temp >> temp;
		getline(inFile,name);
		inFile >> temp >> temp >> mysqlIp;
		inFile >> temp >> temp >> mysqlLogin;
		inFile >> temp >> temp >> mysqlPassword;
		inFile >> temp >> temp >> mysqlBd;
		inFile.close();
		return true;
	}
}