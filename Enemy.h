#pragma once
#include ".\Library\GameObject.h"
#include "global.h"

class EnemyStateBase;

class Enemy :
    public GameObject
{
private:
	

	int hImage_;//‰æ‘œID
	Point pos_;//ˆÊ’u
	DIR dir_;//ˆÚ“®•ûŒü

public:
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;

	enum STATE_PATTERN
	{
		PATROL,
		CHASE,
		ATTACK,
		SEARCH
	};

	struct View
	{
		float x1, y1;
		float x2, y2;
	};


private:
	float vecRad;
	VECTOR eVec;

	int state_;

	

	View eView;

	//EnemyStateBase* state = nullptr;
	//EnemyStateBase* nextState = nullptr;
};

