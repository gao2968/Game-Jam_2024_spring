#include "Bullet.h"

Bullet::Bullet() :location(0.0f), vector(0.0f), speed(0.0f), radius(0.0f), damage(0.0f), type(0)
{
}

Bullet::~Bullet()
{

}

void Bullet::Initialize(Vector2D vec, Vector2D loc, float s, float r, float d, int t)
{
	vector = vec;
	location = loc;
	speed = s;
	damage = d;
	type = t;

}

void Bullet::Update()
{
}

void Bullet::Draw()
{
}

void Bullet::Finalize()
{
}
