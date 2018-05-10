#include "House.h"
#include "sampgdk.h"
#include "Player.h"
#include <iomanip>
#include <array>
#include "Server.h"
#include <vector>
#include <unordered_map>

extern unordered_map<int, int> pickup_Houses;

extern vector<House> houses;
extern array<Player, MAX_PLAYERS> players;
extern Server server;

House::House(int &ID, string &owner, float &enterX, float &enterY, float &enterZ, float &exitX, float &exitY, float &exitZ, int &interior, int &price, string &description, int &virtualWorld)
{
	this->ID = ID;
	this->owner = owner;
	this->enterX = enterX;
	this->enterY = enterY;
	this->enterZ = enterZ;
	this->exitX = exitX;
	this->exitY = exitY;
	this->exitZ = exitZ;
	this->interior = interior;
	this->price = price;
	this->description = description;
	this->virtualWorld = virtualWorld;
	enterPickup = CreatePickup(1273, 23, enterX, enterY, enterZ, 0);
	exitPickup = CreatePickup(1318, 23, exitX, exitY, exitZ, virtualWorld);
}

void House::SaveHouse(House &house)
{
	try
	{ 
		sql::PreparedStatement *pstmt;
		pstmt = server.con->prepareStatement("UPDATE houses SET owner = ?, enterX = ?, enterY = ?, enterZ = ?, exitX = ?, exitY = ?, exitZ = ?, interior = ?, price = ?, description = ?, virtualWorld = ? WHERE ID = ?");
		pstmt->setString(1, house.owner);
		pstmt->setDouble(2, house.enterX);
		pstmt->setDouble(3, house.enterY);
		pstmt->setDouble(4, house.enterZ);
		pstmt->setDouble(5, house.exitX);
		pstmt->setDouble(6, house.exitY);
		pstmt->setDouble(7, house.exitZ);
		pstmt->setInt(8, house.interior);
		pstmt->setInt(9, house.price);
		pstmt->setString(10, house.description);
		pstmt->setInt(11, house.virtualWorld);
		pstmt->setInt(12, house.ID);
		pstmt->executeQuery();
		delete pstmt;
	}
	catch (exception &e)
	{
		sampgdk::logprintf(" Error: %s", e.what());
	}
}

void House::UpdateHouse()
{
	
}

void House::LoadHouses()
{
	setlocale(LC_CTYPE, "rus");
	try 
	{
		sql::PreparedStatement *pstmt;
		sql::ResultSet *result;
		pstmt = server.con->prepareStatement("SELECT * FROM houses");
		result = pstmt->executeQuery();
		int ID = 1;
		while (result->next())
		{
			//int ID = result->getInt(1);
			string owner = result->getString(2);
			float enterX = result->getDouble(3);
			float enterY = result->getDouble(4);
			float enterZ = result->getDouble(5);
			float exitX = result->getDouble(6);
			float exitY = result->getDouble(7);
			float exitZ = result->getDouble(8);
			int interior = result->getInt(9);
			int price = result->getInt(10);
			string description = result->getString(11);
			int virtualWorld = result->getInt(12);
			House house(ID, owner, enterX, enterY, enterZ, exitX, exitY, exitZ, interior, price, description, virtualWorld);
			houses.push_back(house);
			pickup_Houses.emplace(move(houses[ID - 1].enterPickup), move(ID - 1));
			pickup_Houses.emplace(move(houses[ID - 1].exitPickup), move(ID - 1));
			sampgdk::logprintf("Дом номер %d загружен!", ID);	
			++ID;
		}
		delete result;
		delete pstmt;
		sampgdk::logprintf("Данные домов успешно загружены!");
	}
	catch (exception &e)
	{
		sampgdk::logprintf(" Error: %s", e.what());
	}
}

bool House::ProcessHouse(int &playerid, int &pickupid)
{
	auto House = pickup_Houses.find(pickupid);
	if (House != pickup_Houses.end())
	{
		if (IsPlayerInRangeOfPoint(playerid, 1.5, houses[House->second].enterX, houses[House->second].enterY, houses[House->second].enterZ))
		{
			if (players[playerid].pickupFreeze < time(NULL))
			{
				SetPlayerPos(playerid, houses[House->second].exitX, houses[House->second].exitY, houses[House->second].exitZ);
				SetPlayerVirtualWorld(playerid, houses[House->second].virtualWorld);
				players[playerid].pickupFreeze = time(NULL) + 5;
			}
			return true;
		}
		else
		{
			if (players[playerid].pickupFreeze < time(NULL))
			{
				SetPlayerPos(playerid, houses[House->second].enterX, houses[House->second].enterY, houses[House->second].enterZ);
				SetPlayerVirtualWorld(playerid, houses[House->second].virtualWorld);
				players[playerid].pickupFreeze = time(NULL) + 5;
			}
			return true;
		}
	}
	else return false;
}