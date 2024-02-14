#include "Enemy.h"
#include"DxLib.h"
// �w�b�_�[�ł͂Ȃ�cpp�ŃC���N���[�h����
#include"../Scene/GameMainScene.h"

Enemy::Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int _hp, int _E_num, int type, int handle/*, int hed_handle*/) :type(type), image(handle)/*h_image(hed_handle)*/
{
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

	End = false;
}

Enemy::~Enemy()
{

}

// ����������
void Enemy::Initialize()
{
	// �����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	for (int i = 0; i < 3; i++) {
		b_vector[i].x = 0;
	}
}

void Enemy::Update(float _speed, GameMainScene* game, Vector2D player)// �|�C���^�Ȃ̂�GameMainScene�̃A�h���X�ɃA�N�Z�X�ł���
{
	LateTime++;
	b_vector[0].y = location.y;				// �^������
	b_vector[1].y = location.y - 300.0f;		// �X����
	b_vector[2].y = location.y + 300.0f;		// �X����
	// E_num���C�ӂ̐��Ȃ�{�X�̏���
	if (E_num == 11)
	{
		Boss_System(game, player);
	}
	else {
		// �{�X�ȊO�̏���


		if (LateTime % bullet_Timing == 0)
		{
			game->Enemy_SpawnBullet(b_vector[0] - location, location, bullet_speed, 10.0f);
		}
	}
	// �ʒu���Ɉړ��ʂ����Z����
	location.x -= speed;
}

void Enemy::Draw()const
{

	// �G�摜�`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);

	//DrawBox(location.x-30, location.y-30, location.x + 50, location.y + 50, 0xff0000, true);
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
			y_speed = y_speed * -1.0f;		// �ړ������̔��]
			game->Enemy_SpawnBullet(player - location, location, bullet_speed, 50.0f);
		}
		if (LateTime % 30 == 0)
		{
			//// ���ˎ��Ƀv���C���[��ǔ�����e

			game->Enemy_SpawnBullet(b_vector[0] - location, location, bullet_speed / 2, 50.0f);
			game->Enemy_SpawnBullet(b_vector[1] - location, location, bullet_speed / 2, 50.0f);
			game->Enemy_SpawnBullet(b_vector[2] - location, location, bullet_speed / 2, 50.0f);

		}
		location.y += y_speed;
	}
	// �{�X��HP��0�Ȃ�
	if (hp <= 0) {
		End = true;
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

void Enemy::Set_HP(float damege)
{
	hp -= damege;
}