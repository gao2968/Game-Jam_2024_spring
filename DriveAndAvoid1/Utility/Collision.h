#pragma once
#include "Vector2D.h"
#include <math.h>

//�~�`���m�̓����蔻��
//����:���肵����2�̉~�`�̍��W�Ɣ��a
//�߂�l:true �������Ă���@false �������Ă��Ȃ�
bool CheckCollision(Vector2D loc0, float r0, Vector2D loc1, float r1)
{
	Vector2D vec;
	vec = loc1 - loc0;

	float distance;
	distance = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));

	if (distance < r0 + r1) {
		return true;
	}

	return false;
}
