#pragma once
#include "Vector2D.h"
#include <math.h>

//‰~Œ`“¯Žm‚Ì“–‚½‚è”»’è
//ˆø”:”»’è‚µ‚½‚¢2‚Â‚Ì‰~Œ`‚ÌÀ•W‚Æ”¼Œa
//–ß‚è’l:true “–‚½‚Á‚Ä‚¢‚é@false “–‚½‚Á‚Ä‚¢‚È‚¢
bool CheckCollision(Vector2D loc0, float r0, Vector2D loc1, float r1)
{
	Vector2D vec;
	vec = r1 - r0;

	float distance;
	distance = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));

	if (distance > r0 + r1) {
		return true;
	}

	return false;
}
