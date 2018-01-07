#pragma once
#include "sampgdk.h"
#include <array>
#include "Player.h"

extern std::array <Player, MAX_PLAYERS> players;

bool dialog_Auth(int &playerid, int &response, int &listitem, const char *inputtext)
{
	if (response)
	{
		if (players[playerid].password == inputtext)
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
		players[playerid].password = inputtext;
		players[playerid].AddAccount();
	}
	return true;
}