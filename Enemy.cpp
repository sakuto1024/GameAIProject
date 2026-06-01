#include "Enemy.h"
#include "time.h"
#include "Stage.h"
#include "Player.h"

namespace
{
	const int ENEMY_SIZE = 48; //敵のサイズ 32*32
	const Point ENEMY_START_POS = { 20 * ENEMY_SIZE, 10 * ENEMY_SIZE }; //敵の初期位置
	const DIR INIT_ENEMY_DIR = { DOWN };
	const int ENEMY_DRAW_SIZE = 32; //敵の描画サイズ
	const int animFrame[4]{ 0, 1, 2, 1 };
	const float ANIM_INTERVAL = 0.2f;

	int mapData[];
}


Enemy::Enemy()
	: GameObject() 
{
	hImage_ = LoadGraph("Assets/panda_R.png");
	pos_ = ENEMY_START_POS; //32はブロックの位置pos_
	dir_ = INIT_ENEMY_DIR;

	vecRad = 5.0f;
	eVec = { 0.0f, 0.0f, 0.0f };

	dir_ = UP;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//GetRand(数値)
	//3秒に1回向きをランダムに変える
	static float dir_timer = 3.0f;
	static float prog_timer = 0.5f;
	float dt = Time::DeltaTime();
	dir_timer = dir_timer - dt;
	prog_timer = prog_timer - dt;
	/*if (dir_timer < 0.0f)
	{
		dir_ = (DIR)(GetRand(3));
		dir_timer = 3.0f + dir_timer;
	}*/

	Point newPos = pos_;
	if (prog_timer < 0.0f)
	{
		switch (dir_)
		{
		case UP:
			newPos.y -= ENEMY_DRAW_SIZE;
			eVec = { 0.0f, -1.0f, 0.0f };
			break;
		case DOWN:
			newPos.y += ENEMY_DRAW_SIZE;
			eVec = { 0.0f, 1.0f, 0.0f };
			break;
		case LEFT:
			newPos.x -= ENEMY_DRAW_SIZE;
			eVec = { -1.0f, 0.0f, 0.0f };
			break;
		case RIGHT:
			newPos.x += ENEMY_DRAW_SIZE;
			eVec = { 1.0f, 0.0f, 0.0f };
			break;
		default:
			break;
		}

		//int mapValue = FindGameObject<Stage>()->GetMap(newPos.x / CHA_SIZE, newPos.y / CHA_SIZE);
		Stage* stage = FindGameObject<Stage>();
		 int mapValue = stage->GetMap(newPos.x / CHA_SIZE, newPos.y / CHA_SIZE);
		//移動先がステージの外に出ないようにする
		if (mapValue != 1)
		{
			pos_ = newPos;
		}

		else if (mapValue == 1)
		{
			if (dir_ == UP || dir_ == DOWN)
			{
				dir_ = (DIR)(GetRand(1) * 2 + 1); 
			}
			else if (dir_ == LEFT || dir_ == RIGHT)
			{
				dir_ = (DIR)(GetRand(1) * 2); 
			}
		}

		Player* player = FindGameObject<Player>();
		Point pPos = player->GetPlayerPos();

		float distanceX = (pPos.x - pos_.x) * (pPos.x - pos_.x);
		float distanceY = (pPos.y - pos_.y) * (pPos.y - pos_.y);
		float distance = distanceX + distanceY;

		float radius = (128.0f + 128.0f) * (128.0f + 128.0f);

		if (distance < radius)
		{
			DrawString(10, 700, "検知", GetColor(0, 0, 0));

			if (distanceX < distanceY)
			{
				if ((pPos.y - pos_.y) > 0)
				{
					dir_ = DOWN;
				}
				else
				{
					dir_ = UP;
				}
			}

			else
			{
				if ((pPos.x - pos_.x) > 0)
				{
					dir_ = RIGHT;
				}
				else
				{
					dir_ = LEFT;
				}
			}
		}
		

		//DrawCircle(pos_.x + 16, pos_.y, 32 + 16, GetColor(0, 255, 0), TRUE);



		/*if (!(newPos.x < 1 || newPos.x >(STAGE_WIDTH - 2) * ENEMY_DRAW_SIZE
			|| newPos.y < 1 || newPos.y >(STAGE_HEIGHT - 2) * ENEMY_DRAW_SIZE))
		{
			pos_ = newPos;
		}*/
		prog_timer = 0.5f + prog_timer;
	}

}

void Enemy::Draw()
{
	static float animTimer = ANIM_INTERVAL;
	static int frame = 0;
	int nowFrame = animFrame[frame];

	Rect iRect[4] = {
		{  nowFrame * ENEMY_SIZE, 3 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE},
		{  nowFrame * ENEMY_SIZE, 0 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE},
		{  nowFrame * ENEMY_SIZE, 1 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE},
		{  nowFrame * ENEMY_SIZE, 2 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}
	};
	DrawBox(pos_.x, pos_.y, pos_.x + ENEMY_DRAW_SIZE, pos_.y + ENEMY_DRAW_SIZE,
		GetColor(255, 255, 0), FALSE,2);
	DrawRectExtendGraph(pos_.x, pos_.y,pos_.x + ENEMY_DRAW_SIZE, pos_.y + ENEMY_DRAW_SIZE,
		               iRect[dir_].x, iRect[dir_].y, iRect[dir_].w, iRect[dir_].h, hImage_, TRUE);
	if (animTimer < 0) {
		frame = (++frame) % 4;
		animTimer = ANIM_INTERVAL + animTimer;
	}
	animTimer = animTimer - Time::DeltaTime();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(pos_.x - CHA_SIZE * vecRad, pos_.y - CHA_SIZE * vecRad, pos_.x + CHA_SIZE * (vecRad + 1), pos_.y + CHA_SIZE * (vecRad + 1), GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBox(pos_.x - (CHA_SIZE * eVec.x) * vecRad, pos_.y - (CHA_SIZE * eVec.y) * vecRad, 
		pos_.x + (CHA_SIZE * eVec.x) * vecRad + 1, pos_.y + (CHA_SIZE * eVec.y) * vecRad, 
		GetColor(0, 0, 255), TRUE);

	DrawFormatString(50, 700, GetColor(0, 0, 0), "VEC.x : %f, VEC.y : %f", eVec.x, eVec.y);
}
