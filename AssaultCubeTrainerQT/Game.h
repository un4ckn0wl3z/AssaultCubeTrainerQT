#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <iostream>
#include <vector>

namespace Game {
	typedef struct _PLAYER_DATA {

		PVOID address;
		DWORD value;
		std::shared_ptr<std::vector<PVOID>> offsets;
		bool toggle = false;

	} PLAYER_DATA, * PPLAYER_DATA;

	typedef struct _PLAYER
	{
		std::shared_ptr<PLAYER_DATA> local_player;
		std::shared_ptr<PLAYER_DATA> health;
		std::shared_ptr<PLAYER_DATA> rifle_ammo;
		std::shared_ptr<PLAYER_DATA> rifle_mag;
		std::shared_ptr<PLAYER_DATA> pistal_ammo;
		std::shared_ptr<PLAYER_DATA> pistal_mag;
		std::shared_ptr<PLAYER_DATA> sniper_ammo;
		std::shared_ptr<PLAYER_DATA> sniper_mag;
		std::shared_ptr<PLAYER_DATA> shotgun_ammo;
		std::shared_ptr<PLAYER_DATA> shotgun_mag;
		std::shared_ptr<PLAYER_DATA> armor;
		std::shared_ptr<PLAYER_DATA> grenade;
		std::shared_ptr<PLAYER_DATA> rapid_fire;
		std::shared_ptr<PLAYER_DATA> no_recoil;

	} PLAYER, * PPLAYER;


	PVOID modulebase_address = NULL;
	std::shared_ptr<PLAYER> player = std::make_shared<PLAYER>();
	DWORD process_id = NULL;
	const wchar_t* process_name = L"ac_client.exe";
	HANDLE hProcess;

}

#endif // GAME_H