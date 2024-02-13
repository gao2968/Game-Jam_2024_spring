#include "Enemy.h"
#include"DxLib.h"
// �w�b�_�[�ł͂Ȃ�cpp�ŃC���N���[�h����
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

// ����������
void Enemy::Initialize() 
{
	// �����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	b_vector.x = 0;
}

void Enemy::Update(float speed,GameMainScene* game)// �|�C���^�Ȃ̂�GameMainScene�̃A�h���X�ɃA�N�Z�X�ł���
{
	// E_num���C�ӂ̐��Ȃ�{�X�̏���
	if (E_num == 11) 
	{
		if (location.x <= 1000) 
		{
			location.x = 1000;
		}

	}else {
	// �{�X�ȊO�̏���

		b_vector.y = location.y;
		LateTime++;

		if (LateTime % bullet_Timing == 0)
		{
			game->Enemy_SpawnBullet(b_vector - location, location);
		}
	}
	// �ʒu���Ɉړ��ʂ����Z���� Y�̂݃v���X���Ă�������
	 location += Vector2D(this->speed - speed - 6, 0.0f);
}

void Enemy::Draw()const
{
	// �G�摜�`��
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
