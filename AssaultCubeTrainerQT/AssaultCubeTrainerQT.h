#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include "ui_AssaultCubeTrainerQT.h"
#include <qtimer.h>
#include "Trainer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AssaultCubeTrainerQTClass; };
QT_END_NAMESPACE

class AssaultCubeTrainerQT : public QWidget
{
    Q_OBJECT

public:
    AssaultCubeTrainerQT(QWidget *parent = nullptr);
    ~AssaultCubeTrainerQT();

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

    QTimer* m_health_hack_timer  = new QTimer(this);
    QTimer* m_armor_hack_timer = new QTimer(this);
    QTimer* m_grenade_hack_timer = new QTimer(this);
    QTimer* m_rifle_ammo_hack_timer = new QTimer(this);
    QTimer* m_pistal_ammo_hack_timer = new QTimer(this);
    QTimer* m_sniper_ammo_hack_timer = new QTimer(this);
    QTimer* m_shotgun_ammo_hack_timer = new QTimer(this);

    PVOID modulebase_address = NULL;
    std::shared_ptr<Trainer::PLAYER> player = std::make_shared<Trainer::PLAYER>();
    DWORD process_id = NULL;
    const wchar_t* process_name = L"ac_client.exe";
    HANDLE hProcess;

};
#endif // WIDGET_H