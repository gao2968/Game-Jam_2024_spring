#include "Enemy.h"
#include"DxLib.h"

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
}

Enemy::~Enemy() 
{

}

// ����������
void Enemy::Initialize() 
{
	// �����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
}

void Enemy::Update(float speed) 
{
	// �ʒu���Ɉړ��ʂ����Z���� Y�̂݃v���X���Ă�������
	location += Vector2D(0.0f, this->speed + speed - 6);
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
