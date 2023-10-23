#ifndef TRAINER_H
#define TRAINER_H

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>

namespace Trainer
{

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


	void init_player_data(IN std::shared_ptr<PLAYER> player);
	BOOL init_player_dynamic_address(IN HANDLE hProcess, IN PVOID modulebase_address, IN OUT std::shared_ptr<PLAYER> player);

	BOOL get_proc_id(IN const wchar_t* process_name, OUT DWORD* pprocess_id);
	BOOL read_mem(IN HANDLE hProcess, IN std::shared_ptr<PLAYER_DATA> player_data);
	BOOL write_mem(IN HANDLE hProcess, IN std::shared_ptr<PLAYER_DATA> player_data);
	BOOL get_module_base_address(IN DWORD process_id, IN const wchar_t* module_name, OUT PVOID* pbaseAddress);
	BOOL find_dma_addy(IN HANDLE hProcess, IN PVOID init_ptr, IN std::vector<PVOID> offsets, OUT PVOID* pbaseAddress);

	BOOL patch_mem_ex(HANDLE hProcess, PBYTE dst, PBYTE src, DWORD size);
	BOOL nop_ex(HANDLE hProcess, PBYTE dst, DWORD size);




}
#endif // TRAINER_H