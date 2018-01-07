#pragma once
enum Dialogs
{
	Auth,
	Register
};

bool dialog_Auth(int &playerid, int &response, int &listitem, const char *inputtext);

bool dialog_Register(int &playerid, int &response, int &listitem, const char *inputtext);