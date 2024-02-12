#pragma once

#include "../Utility/Vector2D.h"

class Barrier
{
private:
	int image;		// バリア画像
	float life_span;// バリア寿命
public:
	Barrier();
	~Barrier();

	void Draw(const Vector2D& location);// 画像処理
	bool IsFinished(float speed);		// 寿命が尽きたかどうか
};

