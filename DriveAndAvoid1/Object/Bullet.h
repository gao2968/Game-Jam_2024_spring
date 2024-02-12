#pragma once
#include "../Utility/Vector2D.h"

class Bullet
{
private:
	Vector2D location;
	Vector2D vector;
	float speed;
	float radius;
	float damage;
	int type;
private:
	Bullet(); //コンストラクタ
	~Bullet(); //デストラクタ

	void Initialize(Vector2D vec,Vector2D loc,); //初期化処理
	void Update(); //更新処理
	void Draw();//描画処理
	void Finalize();//終了処理

};

