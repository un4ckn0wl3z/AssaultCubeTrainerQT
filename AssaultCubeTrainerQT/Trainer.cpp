#include "Trainer.h"

BOOL Trainer::get_proc_id(IN const wchar_t* process_name, OUT DWORD* pprocess_id)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	PROCESSENTRY32 process_entity;
	process_entity.dwSize = sizeof(process_entity);

	if (Process32First(hSnapshot, &process_entity))
	{
		do {

			if (!_wcsicmp(process_entity.szExeFile, process_name))
			{
				*pprocess_id = process_entity.th32ProcessID;
				return TRUE;
			}

		} while (Process32Next(hSnapshot, &process_entity));
	}

	CloseHandle(hSnapshot);

	return FALSE;
}


BOOL Trainer::read_mem(IN HANDLE hProcess, IN std::shared_ptr<Game::PLAYER_DATA> player_data)
{
	return ReadProcessMemory(hProcess, player_data->address, &player_data->value, sizeof(player_data->value), NULL);
}


BOOL Trainer::write_mem(IN HANDLE hProcess, IN std::shared_ptr<Game::PLAYER_DATA> player_data)
{
	return WriteProcessMemory(hProcess, player_data->address, &player_data->value, sizeof(player_data->value), NULL);
}

BOOL Trainer::get_module_base_address(IN DWORD process_id, IN const wchar_t* module_name, OUT PVOID* pbaseAddress)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	MODULEENTRY32 module_entity;
	module_entity.dwSize = sizeof(module_entity);

	if (Module32First(hSnapshot, &module_entity))
	{
		do {

			if (!_wcsicmp(module_entity.szModule, module_name))
			{
				*pbaseAddress = module_entity.modBaseAddr;
				return TRUE;
			}

		} while (Module32Next(hSnapshot, &module_entity));
	}
	CloseHandle(hSnapshot);
	return FALSE;
}

BOOL Trainer::find_dma_addy(IN HANDLE hProcess, IN PVOID init_ptr, IN std::vector<PVOID> offsets, OUT PVOID* pbaseAddress)
{
	PVOID address = init_ptr;

	for (int i = 0; i < offsets.size(); ++i)
	{
		if ((ReadProcessMemory(hProcess, address, &address, sizeof(address), NULL)) == FALSE)
		{
			return FALSE;
		}

		address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(address) + (uintptr_t)offsets[i]);

	}

	*pbaseAddress = address;
	return TRUE;

}


BOOL Trainer::patch_mem_ex(HANDLE hProcess, PBYTE dst, PBYTE src, DWORD size)
{
	DWORD oldProtect;

	if ((VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldProtect)) == FALSE)
	{
		return FALSE;
	}

	if ((WriteProcessMemory(hProcess, dst, src, size, NULL)) == FALSE)
	{
		return FALSE;
	}

	if ((VirtualProtectEx(hProcess, dst, size, oldProtect, &oldProtect)) == FALSE)
	{
		return FALSE;
	}

}


BOOL Trainer::nop_ex(HANDLE hProcess, PBYTE dst, DWORD size)
{
	PBYTE nops = new BYTE[size];
	memset(nops, 0x90, size);
	BOOL result = patch_mem_ex(hProcess, dst, nops, size);
	delete[] nops;
	return result;

}


void Trainer::init_player_data(IN std::shared_ptr<Game::PLAYER> player)
{
	// ----------------- LOCAL PLAYER SETUP
	player->local_player = std::make_shared<Game::PLAYER_DATA>();

	// ----------------- LOCAL RAPID FIRE SETUP
	player->rapid_fire = std::make_shared<Game::PLAYER_DATA>();

	// ----------------- no_recoil SETUP
	player->no_recoil = std::make_shared<Game::PLAYER_DATA>();

	// ----------------- health SETUP
	player->health = std::make_shared<Game::PLAYER_DATA>();
	player->health->offsets = std::make_shared<std::vector<PVOID>>();
	player->health->offsets->push_back(reinterpret_cast<PVOID>(0xEC));

	// ----------------- armor SETUP
	player->armor = std::make_shared<Game::PLAYER_DATA>();
	player->armor->offsets = std::make_shared<std::vector<PVOID>>();
	player->armor->offsets->push_back(reinterpret_cast<PVOID>(0xF0));

	// ----------------- grenade SETUP
	player->grenade = std::make_shared<Game::PLAYER_DATA>();
	player->grenade->offsets = std::make_shared<std::vector<PVOID>>();
	player->grenade->offsets->push_back(reinterpret_cast<PVOID>(0x144));

	// ----------------- rifle_ammo SETUP
	player->rifle_ammo = std::make_shared<Game::PLAYER_DATA>();
	player->rifle_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->rifle_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x140));

	// ----------------- rifle_mag SETUP
	player->rifle_mag = std::make_shared<Game::PLAYER_DATA>();
	player->rifle_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->rifle_mag->offsets->push_back(reinterpret_cast<PVOID>(0x11C));

	// ----------------- pistal_ammo SETUP
	player->pistal_ammo = std::make_shared<Game::PLAYER_DATA>();
	player->pistal_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->pistal_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x12C));

	// ----------------- pistal_mag SETUP
	player->pistal_mag = std::make_shared<Game::PLAYER_DATA>();
	player->pistal_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->pistal_mag->offsets->push_back(reinterpret_cast<PVOID>(0x108));

	// ----------------- sniper_ammo SETUP
	player->sniper_ammo = std::make_shared<Game::PLAYER_DATA>();
	player->sniper_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->sniper_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x13C));

	// ----------------- sniper_mag SETUP
	player->sniper_mag = std::make_shared<Game::PLAYER_DATA>();
	player->sniper_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->sniper_mag->offsets->push_back(reinterpret_cast<PVOID>(0x118));

	// ----------------- shotgun_ammo SETUP
	player->shotgun_ammo = std::make_shared<Game::PLAYER_DATA>();
	player->shotgun_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->shotgun_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x134));

	// ----------------- shotgun_mag SETUP
	player->shotgun_mag = std::make_shared<Game::PLAYER_DATA>();
	player->shotgun_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->shotgun_mag->offsets->push_back(reinterpret_cast<PVOID>(0x110));
}


BOOL Trainer::init_player_dynamic_address(IN HANDLE hProcess, IN PVOID modulebase_address, IN OUT std::shared_ptr<Game::PLAYER> player)
{

	// Get dynamic local player address
	player->local_player->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0x0017E0A8);

	// Get dynamic rapid_fire address
	player->rapid_fire->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0xC73EA);
 
	// Get dynamic rapid_fire address
	player->no_recoil->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0xC8E52);
 

	// Find dynamic health address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->health->offsets, &player->health->address))
	{
 		return FALSE;
	}

	// Find dynamic armor address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->armor->offsets, &player->armor->address))
	{
 		return FALSE;
	}

	// Find dynamic grenade address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->grenade->offsets, &player->grenade->address))
	{
 		return FALSE;
	}

	// Find dynamic rifle_ammo address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->rifle_ammo->offsets, &player->rifle_ammo->address))
	{
 		return FALSE;
	}


	// Find dynamic rifle_mag address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->rifle_mag->offsets, &player->rifle_mag->address))
	{
 		return FALSE;
	}

	// Find dynamic pistal_ammo address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->pistal_ammo->offsets, &player->pistal_ammo->address))
	{
 		return FALSE;
	}

	// Find dynamic pistal_mag address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->pistal_mag->offsets, &player->pistal_mag->address))
	{
 		return FALSE;
	}

	// Find dynamic sniper_ammo address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->sniper_ammo->offsets, &player->sniper_ammo->address))
	{
 		return FALSE;
	}


	// Find dynamic sniper_mag address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->sniper_mag->offsets, &player->sniper_mag->address))
	{
 		return FALSE;
	}

	// Find dynamic shotgun_ammo address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->shotgun_ammo->offsets, &player->shotgun_ammo->address))
	{
 		return FALSE;
	}


	// Find dynamic shotgun_mag address
	if (!find_dma_addy(hProcess, player->local_player->address, *player->shotgun_mag->offsets, &player->shotgun_mag->address))
	{
 		return FALSE;
	}

	return TRUE;
}