/*
	This file is just an example, you have to define all these callbacks in any .cpp file of your project as shown here,
	otherwise you will get some linking errors because they are called without being defined.
*/

#include "streamer.hpp"
#include "Functions.h"
#include <unordered_map>
extern std::unordered_map <std::string, int> Timers[MAX_PLAYERS];

PLUGIN_EXPORT bool PLUGIN_CALL OnPublicCall(AMX * amx, const char * name, cell * params, cell * retval)
{
	std::string lName = std::string(name);
	if (lName == "OnDynamicObjectMoved") { return OnDynamicObjectMoved(static_cast< int >(params[1])); } // ( int objectid )
	else if (lName == "OnPlayerEditDynamicObject") { return OnPlayerEditDynamicObject(static_cast< int >(params[1]), static_cast< int >(params[2]), static_cast< int >(params[3]), amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]), amx_ctof(params[8]), amx_ctof(params[9])); } // ( int playerid, int objectid, int response, float x, float y, float z, float rx, float ry, float rz )
	else if (lName == "OnPlayerSelectDynamicObject") { return OnPlayerSelectDynamicObject(static_cast< int >(params[1]), static_cast< int >(params[2]), static_cast< int >(params[3]), amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])); } // ( int playerid, int objectid, int modelid, float x, float y, float z )
	else if (lName == "OnPlayerShootDynamicObject") { return OnPlayerShootDynamicObject(static_cast< int >(params[1]), static_cast< int >(params[2]), static_cast< int >(params[3]), amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])); } // ( int playerid, int weaponid, int objectid, float x, float y, float z )
	else if (lName == "OnPlayerPickUpDynamicPickup") { return OnPlayerPickUpDynamicPickup(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int playerid, int pickupid )
	else if (lName == "OnPlayerEnterDynamicCP") { return OnPlayerEnterDynamicCP(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int playerid, int checkpointid )
	else if (lName == "OnPlayerLeaveDynamicCP") { return OnPlayerLeaveDynamicCP(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int playerid, int checkpointid )
	else if (lName == "OnPlayerEnterDynamicRaceCP") { return OnPlayerEnterDynamicRaceCP(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int playerid, int checkpointid )
	else if (lName == "OnPlayerLeaveDynamicRaceCP") { return OnPlayerLeaveDynamicRaceCP(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int playerid, int checkpointid )
	else if (lName == "OnPlayerEnterDynamicArea") { return OnPlayerEnterDynamicArea(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int playerid, int areaid )
	else if (lName == "OnPlayerLeaveDynamicArea") { return OnPlayerLeaveDynamicArea(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int playerid, int areaid )
	else if (lName == "OnPlayerGiveDamageDynamicActor") { return OnPlayerGiveDamageDynamicActor(static_cast< int >(params[1]), static_cast< int >(params[2]), amx_ctof(params[3]), static_cast< int >(params[4]), static_cast< int >(params[5])); } // ( playerid, int actorid, float amount, int weaponid, int bodypart );
	else if (lName == "OnDynamicActorStreamIn") { return OnDynamicActorStreamIn(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int actorid, int forplayerid );
	else if (lName == "OnDynamicActorStreamOut") { return OnDynamicActorStreamOut(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int actorid, int forplayerid );
	else if (lName == "Streamer_OnItemStreamIn") { return Streamer_OnItemStreamIn(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int type, int id );
	else if (lName == "Streamer_OnItemStreamOut") { return Streamer_OnItemStreamOut(static_cast< int >(params[1]), static_cast< int >(params[2])); } // ( int type, int id );
																																					 //else if( lName == "Streamer_OnPluginError" ) { } // ( const char error[ ] ) - can't be made afaik because I would need a length parameter to know error's size before I retrieve it with amx
	return 1;
}

bool OnDynamicObjectMoved( int objectid )
{
	// your plugin's code
	return 1;
}

bool OnPlayerEditDynamicObject( int playerid, int objectid, int response, float x, float y, float z, float rx, float ry, float rz )
{
	// your plugin's code
	return 1;
}

bool OnPlayerSelectDynamicObject( int playerid, int objectid, int modelid, float x, float y, float z )
{
	// your plugin's code
	return 1;
}

bool OnPlayerShootDynamicObject( int playerid, int weaponid, int objectid, float x, float y, float z )
{
	// your plugin's code
	return 1;
}

bool OnPlayerPickUpDynamicPickup( int playerid, int pickupid )
{
	// your plugin's code
	return 1;
}

bool OnPlayerEnterDynamicCP( int playerid, int checkpointid )
{
	// your plugin's code
	return 1;
}

bool OnPlayerLeaveDynamicCP( int playerid, int checkpointid )
{
	// your plugin's code
	return 1;
}

bool OnPlayerEnterDynamicRaceCP( int playerid, int checkpointid )
{
	// your plugin's code
	return 1;
}

bool OnPlayerLeaveDynamicRaceCP( int playerid, int checkpointid )
{
	// your plugin's code
	return 1;
}

extern int zone;

bool OnPlayerEnterDynamicArea( int playerid, int areaid )
{
	if (areaid == zone)
	{
		std::string name = "dynamictimer";
		Timers[playerid].emplace(name, SetTimer(1000, true, TestTimer, (void *)playerid));
	}
	return 1;
}

bool OnPlayerLeaveDynamicArea( int playerid, int areaid )
{
	if (areaid == zone)
	{
		std::string name = "dynamictimer";
		std::unordered_map<std::string, int>::const_iterator iter = Timers[playerid].find(name);
		if (iter != Timers[playerid].end())
		{
			KillTimer(iter->second);
			Timers[playerid].erase(iter);
		}
	}
	return 1;
}

bool OnPlayerGiveDamageDynamicActor( int playerid, int actorid, float amount, int weaponid, int bodypart )
{
	// your plugin's code
	return 1;
}

bool OnDynamicActorStreamIn( int actorid, int forplayerid )
{
	// your plugin's code
	return 1;
}

bool OnDynamicActorStreamOut( int actorid, int forplayerid )
{
	// your plugin's code
	return 1;
}

bool Streamer_OnItemStreamIn( int type, int id )
{
	// your plugin's code
	return 1;
}

bool Streamer_OnItemStreamOut( int type, int id )
{
	// your plugin's code
	return 1;
}

bool Streamer_OnPluginError( char error[ ] ) // unused
{
	// your plugin's code
	return 1;
}