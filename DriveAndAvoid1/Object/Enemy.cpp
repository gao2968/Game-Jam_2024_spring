#include "Enemy.h"
#include"DxLib.h"

Enemy::Enemy(int type, int handle):type(type),image(handle),speed(0.0f),location(0.0f),box_size(0.0f)
{

}

Enemy::Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int _hp, int _E_num)
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
	color = 0xff0000;
}

// new Enemy(e_spawn->LoadEnemy(E_num).location_x
//			,e_spawn->LoadEnemy(E_num).location_y
//			,e_spawn->LoadEnemy(E_num).radius
//			,e_spawn->LoadEnemy(E_num).speed
//			,e_spawn->LoadEnemy(E_num).bullet_speed
//			,e_spawn->LoadEnemy(E_num).score, e_spawn->LoadEnemy(E_num).hp, E_num);
Enemy::~Enemy() 
{

}

// ����������
void Enemy::Initialize() 
{
	// �o�肳����X���W�p�^�[���擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	// �����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	// �����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	// �����̐ݒ�
	speed = (float)(this->type * 2);
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
