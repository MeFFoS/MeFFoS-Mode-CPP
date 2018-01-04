#pragma once
#include <ios>
#include <string>
#include <string.h>
#include <vector>
#include <array>
#include <set>
#include "sampgdk.h"
#include "Player.h"
#include "Server.h"
#include <unordered_map>
set<int> playersOnline;
array <Player, MAX_PLAYERS> players;
Server server;

#include "Commands.h"
unordered_map<string, bool(*)(int&, string&)> CommandMap;
struct Commands
{
	string names;
	bool(*ptr)(int&, string&);
};
const Commands commands[] = { {"/weapon", cmd_weapon}, {"/hello", cmd_hello}, {"/buy", cmd_buy}, {"/hellno", cmd_buy} };