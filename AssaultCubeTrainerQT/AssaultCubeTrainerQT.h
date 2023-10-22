#pragma once

#include <QtWidgets/QWidget>
#include "ui_AssaultCubeTrainerQT.h"
#include "Common.hpp"
#include <qtimer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class AssaultCubeTrainerQTClass; };
QT_END_NAMESPACE

class AssaultCubeTrainerQT : public QWidget
{
    Q_OBJECT

public:
    AssaultCubeTrainerQT(QWidget *parent = nullptr);
    ~AssaultCubeTrainerQT();

    void init_player_data(IN std::shared_ptr<PLAYER> player);
    BOOL init_player_dynamic_address(IN HANDLE hProcess, IN PVOID modulebase_address, IN OUT std::shared_ptr<PLAYER> player);


private slots:
    void health_hack(int toggle);
    void armor_hack(int toggle);
    void grenade_hack(int toggle);
    void rifle_ammo_hack(int toggle);
    void pistal_ammo_hack(int toggle);
    void sniper_ammo_hack(int toggle);
    void shotgun_ammo_hack(int toggle);

    void rapid_fire_hack(int toggle);
    void no_recoil_fire_hack(int toggle);

    
    
private:
    Ui::AssaultCubeTrainerQTClass *ui;
    DWORD m_dwExitCode = 0;
    PVOID m_modulebase_address = NULL;
    std::shared_ptr<PLAYER> m_player = std::make_shared<PLAYER>();
    DWORD m_process_id = NULL;
    const wchar_t* m_process_name = L"ac_client.exe";
    HANDLE m_hProcess;
    QTimer* m_health_hack_timer  = new QTimer(this);
    QTimer* m_armor_hack_timer = new QTimer(this);
    QTimer* m_grenade_hack_timer = new QTimer(this);
    QTimer* m_rifle_ammo_hack_timer = new QTimer(this);
    QTimer* m_pistal_ammo_hack_timer = new QTimer(this);
    QTimer* m_sniper_ammo_hack_timer = new QTimer(this);
    QTimer* m_shotgun_ammo_hack_timer = new QTimer(this);

};
