#include "AssaultCubeTrainerQT.h"

#include "Game.h"
#include "Trainer.h"

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
		if ((Trainer::write_mem(Game::hProcess, Game::player->health)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->health failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});


	connect(m_armor_hack_timer, &QTimer::timeout, [=]() {
		if ((Trainer::write_mem(Game::hProcess, Game::player->armor)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->armor failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});


	connect(m_grenade_hack_timer, &QTimer::timeout, [=]() {
		if ((Trainer::write_mem(Game::hProcess, Game::player->grenade)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->grenade failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});

	connect(m_rifle_ammo_hack_timer, &QTimer::timeout, [=]() {
		if ((Trainer::write_mem(Game::hProcess, Game::player->rifle_ammo)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->rifle_ammo failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});


	connect(m_pistal_ammo_hack_timer, &QTimer::timeout, [=]() {
		if ((Trainer::write_mem(Game::hProcess, Game::player->pistal_ammo)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->pistal_ammo failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});


	connect(m_sniper_ammo_hack_timer, &QTimer::timeout, [=]() {
		if ((Trainer::write_mem(Game::hProcess, Game::player->sniper_ammo)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->sniper_ammo failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});

	connect(m_shotgun_ammo_hack_timer, &QTimer::timeout, [=]() {
		if ((Trainer::write_mem(Game::hProcess, Game::player->shotgun_ammo)) == FALSE)
		{
			qDebug() << "[!] WriteProcessMemory player->shotgun_ammo failed with error code: " << GetLastError();
			exit(EXIT_FAILURE);
		};
	});

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string process_name_utf8 = converter.to_bytes(Game::process_name);

	Trainer::init_player_data(Game::player);

	// Get game process ID
	if (!Trainer::get_proc_id(Game::process_name, &Game::process_id))
	{
		qDebug() << "[!] GetProcId failed with error code: " << GetLastError();
		msgBox.exec();
		exit(EXIT_FAILURE);
	}
	 

	// Get ac_client.exe base address
	if (!Trainer::get_module_base_address(Game::process_id, Game::process_name, &Game::modulebase_address))
	{
		qDebug() << "[!] GetModuleBaseAddress failed with error code: " << GetLastError();
	}

	// Get process handle
	Game::hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Game::process_id);
	if (Game::hProcess == NULL)
	{
		qDebug() << "[!] OpenProcess failed with error code: " << GetLastError();
	}

	if (Trainer::init_player_dynamic_address(Game::hProcess, Game::modulebase_address, Game::player) != TRUE)
	{
		qDebug() << "[!] Cannot init_player_dynamic_address: " << GetLastError();
	}

 
}


void AssaultCubeTrainerQT::health_hack(int toggle)
{
	Game::player->health->toggle = toggle;
	if (Game::player->health->toggle) {
		Game::player->health->value = 1337;
		m_health_hack_timer->start(100);
	}
	else {
		m_health_hack_timer->stop();
	}
 
}

void AssaultCubeTrainerQT::armor_hack(int toggle)
{
	Game::player->armor->toggle = toggle;
	if (Game::player->armor->toggle) {
		Game::player->armor->value = 1337;
		m_armor_hack_timer->start(100);
	}
	else {
		m_armor_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::grenade_hack(int toggle)
{
	Game::player->grenade->toggle = toggle;
	if (Game::player->grenade->toggle) {
		Game::player->grenade->value = 1337;
		m_grenade_hack_timer->start(100);
	}
	else {
		m_grenade_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::rifle_ammo_hack(int toggle)
{
	Game::player->rifle_ammo->toggle = toggle;
	if (Game::player->rifle_ammo->toggle) {
		Game::player->rifle_ammo->value = 1337;
		m_rifle_ammo_hack_timer->start(100);
	}
	else {
		m_rifle_ammo_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::pistal_ammo_hack(int toggle)
{
	Game::player->pistal_ammo->toggle = toggle;
	if (Game::player->pistal_ammo->toggle) {
		Game::player->pistal_ammo->value = 1337;
		m_pistal_ammo_hack_timer->start(100);
	}
	else {
		m_pistal_ammo_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::sniper_ammo_hack(int toggle)
{
	Game::player->sniper_ammo->toggle = toggle;
	if (Game::player->sniper_ammo->toggle) {
		Game::player->sniper_ammo->value = 1337;
		m_sniper_ammo_hack_timer->start(100);
	}
	else {
		m_sniper_ammo_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::shotgun_ammo_hack(int toggle)
{
	Game::player->shotgun_ammo->toggle = toggle;
	if (Game::player->shotgun_ammo->toggle) {
		Game::player->shotgun_ammo->value = 1337;
		m_shotgun_ammo_hack_timer->start(100);
	}
	else {
		m_shotgun_ammo_hack_timer->stop();
	}
}

void AssaultCubeTrainerQT::rapid_fire_hack(int toggle)
{
	Game::player->rapid_fire->toggle = toggle;
	if (Game::player->rapid_fire->toggle)
	{

		if ((Trainer::nop_ex(Game::hProcess, (PBYTE)Game::player->rapid_fire->address, 2)) == FALSE)
		{
			qDebug() << "[!] NopEx player->rapid_fire failed with error code: " << GetLastError();
		};
	}
	else {
		if ((Trainer::patch_mem_ex(Game::hProcess, (PBYTE)Game::player->rapid_fire->address, (PBYTE)"\x89\x08", 2)) == FALSE)
		{
			qDebug() << "[!] PatchMemEx player->rapid_fire failed with error code: " << GetLastError();
		};
	}

}

void AssaultCubeTrainerQT::no_recoil_fire_hack(int toggle)
{
	Game::player->no_recoil->toggle = toggle;
	if (Game::player->no_recoil->toggle)
	{

		if ((Trainer::nop_ex(Game::hProcess, (PBYTE)Game::player->no_recoil->address, 5)) == FALSE)
		{
			qDebug() << "[!] NopEx player->no_recoil failed with error code: " << GetLastError();
		};
	}
	else {
		if ((Trainer::patch_mem_ex(Game::hProcess, (PBYTE)Game::player->no_recoil->address, (PBYTE)"\xF3\x0F\x11\x50\x40", 5)) == FALSE)
		{
			qDebug() << "[!] PatchMemEx player->no_recoil failed with error code: " << GetLastError();

		};
	}
}

AssaultCubeTrainerQT::~AssaultCubeTrainerQT()
{
	delete m_health_hack_timer;
	delete m_armor_hack_timer;
	delete m_grenade_hack_timer;
	delete m_rifle_ammo_hack_timer;
	delete m_pistal_ammo_hack_timer;
	delete m_sniper_ammo_hack_timer;
	delete m_shotgun_ammo_hack_timer;
	delete ui;
}
