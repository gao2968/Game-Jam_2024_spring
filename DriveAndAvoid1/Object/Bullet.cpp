#include "Bullet.h"
#include "DxLib.h"
#include <math.h>

int Bullet::tama;

Bullet::Bullet() :location(0.0f), vector(0.0f), speed(0.0f), radius(0.0f), damage(0.0f), type(0)
{
}

Bullet::~Bullet()
{

}

void Bullet::Initialize(Vector2D vec, Vector2D loc, float s, float r, float d, int t)
{
	if (t == 0) {
		tama = LoadGraph("Resource/images/yuusyanotama.png");
	}
	else
	{
		tama= LoadGraph("Resource/images/tekinotama.png");
	}

	vector = vec;
	location = loc;
	speed = s;
	radius = r;
	damage = d;
	type = t;

}

void Bullet::Update()
{
	Vector2D unitVector;
	float distance;

	distance = sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
	unitVector = vector / distance;

	location += unitVector * speed;
}

void Bullet::Draw()
{
	//DrawCircle(location.x, location.y, radius, 0xff0000, TRUE);
	DrawRotaGraphF(location.x, location.y, 1.8, 0, 0, tama, TRUE); 
}

void Bullet::Finalize()
{
}
