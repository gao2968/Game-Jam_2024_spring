#pragma once
#include "Vector2D.h"
#include <math.h>

//円形同士の当たり判定
//引数:判定したい2つの円形の座標と半径
//戻り値:true 当たっている　false 当たっていない
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
