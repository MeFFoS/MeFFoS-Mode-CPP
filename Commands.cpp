#include <string>
#include "sampgdk.h"

using namespace std;

bool cmd_weapon(int &playerid, string &params)
{
	GivePlayerWeapon(playerid, 24, 100);
	SendClientMessage(playerid, -1, params.c_str());
	return true;
}

bool cmd_hello(int &playerid, string &params)
{
	return true;
}

bool cmd_buy(int &playerid, string &params)
{
	return true;
}