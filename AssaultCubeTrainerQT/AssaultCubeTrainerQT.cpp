#include "AssaultCubeTrainerQT.h"

#include <locale>
#include <codecvt>
#include <conio.h>

#include <QMessageBox>
#include <QDebug>
 

AssaultCubeTrainerQT::AssaultCubeTrainerQT(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AssaultCubeTrainerQTClass())
{
    ui->setupUi(this);

	QMessageBox msgBox;
	msgBox.setWindowIcon(QIcon(":/icons/25207.png"));
	msgBox.setText("Game process not found.");
	msgBox.setInformativeText("Please start game before execute a trainer!");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);


	connect(ui->healthCheckbox, &QCheckBox::toggled, this ,&AssaultCubeTrainerQT::health_hack);
	connect(ui->armorCheckbox, &QCheckBox::toggled, this, &AssaultCubeTrainerQT::armor_hack);
	connect(ui->grenadeCheckbox, &QCheckBox::toggled, this, &AssaultCubeTrainerQT::grenade_hack);
	connect(ui->rifleAmmoCheckbox, &QCheckBox::toggled, this, &AssaultCubeTrainerQT::rifle_ammo_hack);
	connect(ui->pistalAmmoCheckbox, &QCheckBox::toggled, this, &AssaultCubeTrainerQT::pistal_ammo_hack);
	connect(ui->sniperAmmoCheckbox, &QCheckBox::toggled, this, &AssaultCubeTrainerQT::sniper_ammo_hack);
	connect(ui->shotgunAmmoCheckbox, &QCheckBox::toggled, this, &AssaultCubeTrainerQT::shotgun_ammo_hack);
	connect(ui->rapidFireCheckbox, &QCheckBox::toggled, this, &AssaultCubeTrainerQT::rapid_fire_hack);
	connect(ui->noRecoilCheckbox, &QCheckBox::toggled, this, &AssaultCubeTrainerQT::no_recoil_fire_hack);

	connect(m_health_hack_timer, &QTimer::timeout, [=]() {
		if ((WriteMem(m_hProcess, m_player->health)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->health failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});


	connect(m_armor_hack_timer, &QTimer::timeout, [=]() {
		if ((WriteMem(m_hProcess, m_player->armor)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->armor failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});


	connect(m_grenade_hack_timer, &QTimer::timeout, [=]() {
		if ((WriteMem(m_hProcess, m_player->grenade)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->grenade failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});

	connect(m_rifle_ammo_hack_timer, &QTimer::timeout, [=]() {
		if ((WriteMem(m_hProcess, m_player->rifle_ammo)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->rifle_ammo failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});


	connect(m_pistal_ammo_hack_timer, &QTimer::timeout, [=]() {
		if ((WriteMem(m_hProcess, m_player->pistal_ammo)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->pistal_ammo failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});


	connect(m_sniper_ammo_hack_timer, &QTimer::timeout, [=]() {
		if ((WriteMem(m_hProcess, m_player->sniper_ammo)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->sniper_ammo failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});

	connect(m_shotgun_ammo_hack_timer, &QTimer::timeout, [=]() {
		if ((WriteMem(m_hProcess, m_player->shotgun_ammo)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->shotgun_ammo failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string process_name_utf8 = converter.to_bytes(m_process_name);

	init_player_data(m_player);

	// Get game process ID
	if (!GetProcId(m_process_name, &m_process_id))
	{
		qDebug() << "[!] GetProcId failed with error code: " << GetLastError();
		msgBox.exec();
		exit(EXIT_FAILURE);
	}
	 

	// Get ac_client.exe base address
	if (!GetModuleBaseAddress(m_process_id, m_process_name, &m_modulebase_address))
	{
		qDebug() << "[!] GetModuleBaseAddress failed with error code: " << GetLastError();
	}

	// Get process handle
	m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_process_id);
	if (m_hProcess == NULL)
	{
		qDebug() << "[!] OpenProcess failed with error code: " << GetLastError();
	}

	if (init_player_dynamic_address(m_hProcess, m_modulebase_address, m_player) != TRUE)
	{
		qDebug() << "[!] Cannot init_player_dynamic_address: " << GetLastError();
	}

 
}


void AssaultCubeTrainerQT::health_hack(int toggle)
{
	m_player->health->toggle = toggle;
	if (m_player->health->toggle) {
		m_player->health->value = 1337;
		m_health_hack_timer->start(100);
	}
	else {
		m_health_hack_timer->stop();
	}
 
}

void AssaultCubeTrainerQT::armor_hack(int toggle)
{
	m_player->armor->toggle = toggle;
	if (m_player->armor->toggle) {
		m_player->armor->value = 1337;
		m_armor_hack_timer->start(100);
	}
	else {
		m_armor_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::grenade_hack(int toggle)
{
	m_player->grenade->toggle = toggle;
	if (m_player->grenade->toggle) {
		m_player->grenade->value = 1337;
		m_grenade_hack_timer->start(100);
	}
	else {
		m_grenade_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::rifle_ammo_hack(int toggle)
{
	m_player->rifle_ammo->toggle = toggle;
	if (m_player->rifle_ammo->toggle) {
		m_player->rifle_ammo->value = 1337;
		m_rifle_ammo_hack_timer->start(100);
	}
	else {
		m_rifle_ammo_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::pistal_ammo_hack(int toggle)
{
	m_player->pistal_ammo->toggle = toggle;
	if (m_player->pistal_ammo->toggle) {
		m_player->pistal_ammo->value = 1337;
		m_pistal_ammo_hack_timer->start(100);
	}
	else {
		m_pistal_ammo_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::sniper_ammo_hack(int toggle)
{
	m_player->sniper_ammo->toggle = toggle;
	if (m_player->sniper_ammo->toggle) {
		m_player->sniper_ammo->value = 1337;
		m_sniper_ammo_hack_timer->start(100);
	}
	else {
		m_sniper_ammo_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::shotgun_ammo_hack(int toggle)
{
	m_player->shotgun_ammo->toggle = toggle;
	if (m_player->shotgun_ammo->toggle) {
		m_player->shotgun_ammo->value = 1337;
		m_shotgun_ammo_hack_timer->start(100);
	}
	else {
		m_shotgun_ammo_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::rapid_fire_hack(int toggle)
{
	m_player->rapid_fire->toggle = toggle;
	if (m_player->rapid_fire->toggle)
	{

		if ((NopEx(m_hProcess, (PBYTE)m_player->rapid_fire->address, 2)) == FALSE)
		{
			qDebug() << "[!] NopEx player->rapid_fire failed with error code: " << GetLastError();
		};
	}
	else {
		if ((PatchMemEx(m_hProcess, (PBYTE)m_player->rapid_fire->address, (PBYTE)"\x89\x08", 2)) == FALSE)
		{
			qDebug() << "[!] PatchMemEx player->rapid_fire failed with error code: " << GetLastError();
		};
	}

}

void AssaultCubeTrainerQT::no_recoil_fire_hack(int toggle)
{
	m_player->no_recoil->toggle = toggle;
	if (m_player->no_recoil->toggle)
	{

		if ((NopEx(m_hProcess, (PBYTE)m_player->no_recoil->address, 5)) == FALSE)
		{
			qDebug() << "[!] NopEx player->no_recoil failed with error code: " << GetLastError();
		};
	}
	else {
		if ((PatchMemEx(m_hProcess, (PBYTE)m_player->no_recoil->address, (PBYTE)"\xF3\x0F\x11\x50\x40", 5)) == FALSE)
		{
			qDebug() << "[!] PatchMemEx player->no_recoil failed with error code: " << GetLastError();

		};
	}
}

void AssaultCubeTrainerQT::init_player_data(IN std::shared_ptr<PLAYER> player)
{
	// ----------------- LOCAL PLAYER SETUP
	player->local_player = std::make_shared<PLAYER_DATA>();

	// ----------------- LOCAL RAPID FIRE SETUP
	player->rapid_fire = std::make_shared<PLAYER_DATA>();

	// ----------------- no_recoil SETUP
	player->no_recoil = std::make_shared<PLAYER_DATA>();

	// ----------------- health SETUP
	player->health = std::make_shared<PLAYER_DATA>();
	player->health->offsets = std::make_shared<std::vector<PVOID>>();
	player->health->offsets->push_back(reinterpret_cast<PVOID>(0xEC));

	// ----------------- armor SETUP
	player->armor = std::make_shared<PLAYER_DATA>();
	player->armor->offsets = std::make_shared<std::vector<PVOID>>();
	player->armor->offsets->push_back(reinterpret_cast<PVOID>(0xF0));

	// ----------------- grenade SETUP
	player->grenade = std::make_shared<PLAYER_DATA>();
	player->grenade->offsets = std::make_shared<std::vector<PVOID>>();
	player->grenade->offsets->push_back(reinterpret_cast<PVOID>(0x144));

	// ----------------- rifle_ammo SETUP
	player->rifle_ammo = std::make_shared<PLAYER_DATA>();
	player->rifle_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->rifle_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x140));

	// ----------------- rifle_mag SETUP
	player->rifle_mag = std::make_shared<PLAYER_DATA>();
	player->rifle_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->rifle_mag->offsets->push_back(reinterpret_cast<PVOID>(0x11C));

	// ----------------- pistal_ammo SETUP
	player->pistal_ammo = std::make_shared<PLAYER_DATA>();
	player->pistal_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->pistal_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x12C));

	// ----------------- pistal_mag SETUP
	player->pistal_mag = std::make_shared<PLAYER_DATA>();
	player->pistal_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->pistal_mag->offsets->push_back(reinterpret_cast<PVOID>(0x108));

	// ----------------- sniper_ammo SETUP
	player->sniper_ammo = std::make_shared<PLAYER_DATA>();
	player->sniper_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->sniper_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x13C));

	// ----------------- sniper_mag SETUP
	player->sniper_mag = std::make_shared<PLAYER_DATA>();
	player->sniper_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->sniper_mag->offsets->push_back(reinterpret_cast<PVOID>(0x118));

	// ----------------- shotgun_ammo SETUP
	player->shotgun_ammo = std::make_shared<PLAYER_DATA>();
	player->shotgun_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->shotgun_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x134));

	// ----------------- shotgun_mag SETUP
	player->shotgun_mag = std::make_shared<PLAYER_DATA>();
	player->shotgun_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->shotgun_mag->offsets->push_back(reinterpret_cast<PVOID>(0x110));
}


BOOL AssaultCubeTrainerQT::init_player_dynamic_address(IN HANDLE hProcess, IN PVOID modulebase_address, IN OUT std::shared_ptr<PLAYER> player)
{

	// Get dynamic local player address
	player->local_player->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0x0017E0A8);
	qDebug() << "[+] Dynamic LocalPlayer address: " << player->local_player->address;

	// Get dynamic rapid_fire address
	player->rapid_fire->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0xC73EA);
	qDebug() << "[+] Dynamic rapid_fire address: " << player->rapid_fire->address;

	// Get dynamic rapid_fire address
	player->no_recoil->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0xC8E52);
	qDebug() << "[+] Dynamic no_recoil address: " << player->no_recoil->address;


	// Find dynamic health address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->health->offsets, &player->health->address))
	{
		qDebug() << "[!] FindDMAAddy with health failed with error code: " << GetLastError();
		return FALSE;
	}

	// Find dynamic armor address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->armor->offsets, &player->armor->address))
	{
		qDebug() << "[!] FindDMAAddy with armor failed with error code: " << GetLastError();
		return FALSE;
	}

	// Find dynamic grenade address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->grenade->offsets, &player->grenade->address))
	{
		qDebug() << "[!] FindDMAAddy with grenade failed with error code: " << GetLastError();
		return FALSE;
	}

	// Find dynamic rifle_ammo address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->rifle_ammo->offsets, &player->rifle_ammo->address))
	{
		qDebug() << "[!] FindDMAAddy with rifle_ammo failed with error code: " << GetLastError();
		return FALSE;
	}


	// Find dynamic rifle_mag address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->rifle_mag->offsets, &player->rifle_mag->address))
	{
		qDebug() << "[!] FindDMAAddy with rifle_mag failed with error code: " << GetLastError();
		return FALSE;
	}

	// Find dynamic pistal_ammo address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->pistal_ammo->offsets, &player->pistal_ammo->address))
	{
		qDebug() << "[!] FindDMAAddy with pistal_ammo failed with error code: " << GetLastError();
		return FALSE;
	}

	// Find dynamic pistal_mag address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->pistal_mag->offsets, &player->pistal_mag->address))
	{
		qDebug() << "[!] FindDMAAddy with pistal_mag failed with error code: " << GetLastError();
		return FALSE;
	}

	// Find dynamic sniper_ammo address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->sniper_ammo->offsets, &player->sniper_ammo->address))
	{
		qDebug() << "[!] FindDMAAddy with sniper_ammo failed with error code: " << GetLastError();
		return FALSE;
	}


	// Find dynamic sniper_mag address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->sniper_mag->offsets, &player->sniper_mag->address))
	{
		qDebug() << "[!] FindDMAAddy with sniper_mag failed with error code: " << GetLastError();
		return FALSE;
	}

	// Find dynamic shotgun_ammo address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->shotgun_ammo->offsets, &player->shotgun_ammo->address))
	{
		qDebug() << "[!] FindDMAAddy with shotgun_ammo failed with error code: " << GetLastError();
		return FALSE;
	}


	// Find dynamic shotgun_mag address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->shotgun_mag->offsets, &player->shotgun_mag->address))
	{
		qDebug() << "[!] FindDMAAddy with shotgun_mag failed with error code: " << GetLastError();
		return FALSE;
	}

	return TRUE;
}

AssaultCubeTrainerQT::~AssaultCubeTrainerQT()
{
    delete ui;
}
