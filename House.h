#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class House
{
public:
	int ID;
	string owner;
	float enterX, enterY, enterZ;
	float exitX, exitY, exitZ;
	int interior;
	int price;
	int enterPickup;
	int exitPickup;
	string description;
	int virtualWorld;
	House(int &ID, string &owner, float &enterX, float &enterY, float &enterZ, float &exitX, float &exitY, float &exitZ, int &interior, int &price, string &description, int &virtualWorld);
	static void SaveHouse(House &house);
	void UpdateHouse();
	static void LoadHouses();
	static bool ProcessHouse(int &playerid, int &pickupid);
};