#include "Enemy.h"
#include"DxLib.h"
// ヘッダーではなくcppでインクルードする
#include"../Scene/GameMainScene.h"
#include "../Resource/SoundManager.h"

Enemy::Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int _hp, int _E_num, int type, int handle, int hed_handle,int img_num,int max) :type(type), image(handle)/*h_image(hed_handle)*/
{
	head_images = hed_handle;
	image_num = img_num;
	point = score;
	WaitTime = 0;
	E_num = _E_num;
	hp = _hp;
	speed = _speed;
	bullet_speed = 6.0f;

	location.x = _x;
	location.y = _y;
	radius = _r;
	bullet_Timing = 120;
	y_speed = 3.0f;
	enemy_num = max;
	End = false;
}

Enemy::~Enemy()
{

}

// 処理化処理
void Enemy::Initialize()
{
	// あたり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	for (int i = 0; i < 3; i++) {
		b_vector[i].x = 0;
	}
}

void Enemy::Update(float _speed, GameMainScene* game, Vector2D player)// ポインタなのでGameMainSceneのアドレスにアクセスできる
{
	LateTime++;

	b_vector[0].y = location.y;				// 真っ直ぐ
	b_vector[1].y = location.y - 300.0f;		// 傾ける
	b_vector[2].y = location.y + 300.0f;		// 傾ける
	// E_numが任意の数ならボスの処理
	if (E_num == enemy_num)
	{
		Boss_System(game, player);
	}
	else {
		// ボス以外の処理


		if (LateTime % bullet_Timing == 0)
		{
			game->Enemy_SpawnBullet(b_vector[0] - location, location, bullet_speed, 50.0f);
		}
	}
	// 位置情報に移動量を加算する
	location.x -= speed;

	// ダメージ時の管理
	if (hit == true) {
		hit_reset_count++;
	}
	if (hit_reset_count >=5) {
		hit = false;
		hit_reset_count = 0;
	}
}

void Enemy::Draw()const
{

	// 敵画像描画

	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	// hit時に赤くする
	if (hit) {
		DrawBox(location.x - 50, location.y - 50, location.x + 50, location.y + 50, 0xff0000, TRUE);
	}
	switch (image_num)
	{
	case(0):
		DrawRotaGraphF(location.x+3, location.y + 58, 1.80, 0.0, head_images, TRUE);	// 鬼
	break;
	case(1):
		DrawRotaGraphF(location.x-10, location.y - 20, 1.2, 0.3, head_images, TRUE);	// 鹿
	break;
	case(2):
		DrawRotaGraphF(location.x, location.y + 300, 4.5, 0.0, head_images, TRUE);	// ボス
	break;
	}


}

void Enemy::Finalize()
{
}


void Enemy::Boss_System(GameMainScene* game, Vector2D player)
{
	if (location.x <= 1000)
	{
		location.x = 1000;
		if (location.y >= 600 || location.y <= 100)
		{
			y_speed = y_speed * -1.0f;		// 移動方向の反転
			game->Enemy_SpawnBullet(player - location, location, bullet_speed, 60.0f);
		}
		if (LateTime % 30 == 0)
		{
			//// 発射時にプレイヤーを追尾する弾

			game->Enemy_SpawnBullet(b_vector[0] - location, location, bullet_speed / 2, 50.0f);
			game->Enemy_SpawnBullet(b_vector[1] - location, location, bullet_speed / 2, 50.0f);
			game->Enemy_SpawnBullet(b_vector[2] - location, location, bullet_speed / 2, 50.0f);
		}
		location.y += y_speed;
	}
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

float Enemy::Get_HP()
{
	return hp;
}

bool Enemy::Get_BossDown()
{
	return End;
}

int Enemy::Get_Score()
{
	return point;
}

void Enemy::Voic()
{
	PlaySoundMem(SoundManager::GetSE(GetRand(4) + 1), DX_PLAYTYPE_BACK);
}

void Enemy::Set_HP(float damege)
{
	hit = true;
	hp -= damege;
}