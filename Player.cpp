#include <string>
#include <fstream>
#include "sampgdk.h"
#include <set>
#include "Server.h"
#include "Player.h"
#include "Dialogs.h"

extern set<int> playersOnline;
extern Server server;

void Player::Connect(string playerName, int playerId)
{
	name = playerName;
	id = playerId;
	playersOnline.insert(id);
	sql::PreparedStatement *pstmt;
	sql::ResultSet *result;
	pstmt = server.con->prepareStatement("SELECT * FROM accounts WHERE name = ?");
	pstmt->setString(1, name);
	result = pstmt->executeQuery();
	if (result->next())//!result->wasNull()
	{
		SendClientMessage(id, -1, "Аккаунт зарегистрирован");
		LoadAccount(result);
		Authorization();
	}
	else
	{
		SendClientMessage(id, -1, "Аккаунт не зарегистрирован"); // сообщить об этом
		Registration();
	}
	delete result;
	delete pstmt;
}
void Player::Authorization()
{
	ShowPlayerDialog(id, Dialogs::Auth, DIALOG_STYLE_INPUT, "Авторизация", "Добро пожаловать на сервер, ебашьте пароль", "Ввод", "Отмена");
}
void Player::Disconnect()
{
	SaveAccount();
	Clear();
	playersOnline.erase(id);
}
void Player::Clear()
{
	id = NULL;
	name.clear();
	password.clear();
	level = NULL;
}
void Player::SaveAccount()
{
	sql::PreparedStatement *pstmt;
	pstmt = server.con->prepareStatement("UPDATE accounts SET password = ?, level = ? WHERE name = ?");
	pstmt->setString(1, password);
	pstmt->setInt(2, level);
	pstmt->setString(3, name);
	pstmt->executeQuery();
	delete pstmt;
}
void Player::AddAccount()
{
	try
	{
		sql::PreparedStatement *pstmt;
		pstmt = server.con->prepareStatement("INSERT INTO accounts(name, password, level) VALUES(?,?,?)");
		pstmt->setString(1, name);
		pstmt->setString(2, password);
		pstmt->setInt(3, level);
		pstmt->execute();
		delete pstmt;
	}
	catch (sql::SQLException &e)
	{
		sampgdk::logprintf("# ERR: SQLException in %s", __FILE__);
		sampgdk::logprintf("(%s) on line %s", __FUNCTION__, __LINE__);
		sampgdk::logprintf("# ERR: %s", e.what());
		sampgdk::logprintf(" (MySQL error code: %s", e.getErrorCode());
		sampgdk::logprintf(", SQLState: %s)", e.getSQLState());
	}
}

void Player::LoadAccount(sql::ResultSet *result)
{
	password = result->getString(3);
	level = result->getInt(4);
}
void Player::Registration()
{
	level = 1;
	ShowPlayerDialog(id, Dialogs::Register, DIALOG_STYLE_INPUT, "Авторизация", "Добро пожаловать на сервер, ебашьте регу", "Рега", "Отмена");
}