#pragma once
#include ".\Library\GameObject.h"


class Enemy;

class EnemyStateBase : public GameObject
{
public:
    virtual ~EnemyStateBase() = default;

    virtual void Update(Enemy& enemy) = 0;
};

