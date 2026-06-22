#pragma once
#include "Enemy.h"
class EnemyStateBase :
    public Enemy
{
public:
    EnemyStateBase();
    virtual ~EnemyStateBase() = default;

    virtual void Update(Enemy& enemy) = 0;
};

