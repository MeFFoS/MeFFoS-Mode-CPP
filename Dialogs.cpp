#include "sampgdk.h"
#include <array>
#include "Dialogs.h"
#include "Player.h"
#include "sha384.h"
#include "sha384.cpp"
#include "Server.h"

extern Server server;
extern array <Player, MAX_PLAYERS> players;

bool dialog_Auth(int &playerid, int &response, int &listitem, const char *inputtext)
{
	if (response)
	{
		if (players[playerid].password == sha384(server.salt + inputtext))
		{
			players[playerid].auth = true;
			SendClientMessage(playerid, -1, "Успешная авторизация");
		}
		else
		{
			SendClientMessage(playerid, -1, "Пароль неверный");
			Kick(playerid);
		}
	}
	return true;
}

bool dialog_Register(int &playerid, int &response, int &listitem, const char *inputtext)
{
	if (response)
	{
		players[playerid].password = sha384(server.salt + inputtext);
		players[playerid].AddAccount();
	}
	else
	{
		Kick(playerid);
	}
	return true;
}