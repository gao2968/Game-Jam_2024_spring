#include "Enemy.h"
#include"DxLib.h"
// ヘッダーではなくcppでインクルードする
#include"../Scene/GameMainScene.h"

Enemy::Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int _hp, int _E_num, int type, int handle) :type(type), image(handle)
{
	point = score;
	WaitTime = 0;
	E_num = _E_num;
	hp = _hp;
	speed = _speed;
	bullet_speed = b_speed;

	location.x = _x;
	location.y = _y;
	radius = _r;
	bullet_Timing = 120;
}

Enemy::~Enemy() 
{

}

// 処理化処理
void Enemy::Initialize() 
{
	// あたり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	b_vector.x = 0;
}

void Enemy::Update(float speed,GameMainScene* game)// ポインタなのでGameMainSceneのアドレスにアクセスできる
{
	// E_numが任意の数ならボスの処理
	if (E_num == 11) 
	{
		if (location.x <= 1000) 
		{
			location.x = 1000;
		}

	}else {
	// ボス以外の処理

		b_vector.y = location.y;
		LateTime++;

		if (LateTime % bullet_Timing == 0)
		{
			game->Enemy_SpawnBullet(b_vector - location, location);
		}
	}
	// 位置情報に移動量を加算する Yのみプラスしていく感じ
	 location += Vector2D(this->speed - speed - 6, 0.0f);
}

void Enemy::Draw()const
{
	// 敵画像描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Enemy::Finalize()
{
}

int Enemy::GetType() const
{
	return type;
}

Vector2D Enemy::GetLocation()
{
	return location;
}

Vector2D Enemy::GetBoxSize()
{
	return box_size;
}

int Enemy::Get_Radius()
{
	return radius;
}

bool Enemy::firing()
{
	return shot;
}
