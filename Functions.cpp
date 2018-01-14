#include "Functions.h"

void SAMPGDK_CALL TestTimer(int timerid, void *params)
{
	int playerid = reinterpret_cast<int>(params);
	SendClientMessage(playerid, -1, "Сработал таймер");
}