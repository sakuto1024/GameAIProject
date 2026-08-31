#pragma once
#include "EnemystateBase.h"

class Enemy;

class PatrolState : public EnemyStateBase
{
public:
    void Update(Enemy& enemy) override;
};
