#pragma once
#include "../Utility/Vector2D.h"

class Bullet
{
private:
	Vector2D vec;
	float radius;

private:
	Bullet(); //コンストラクタ
	~Bullet(); //デストラクタ

	void Initialize(); //初期化処理
	void Update(); //更新処理
	void Draw();//描画処理
	void Finalize();//終了処理

};

