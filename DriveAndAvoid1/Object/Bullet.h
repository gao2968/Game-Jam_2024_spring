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
	int type;  //0プレイヤー　1敵
public:
	Bullet(); //コンストラクタ
	~Bullet(); //デストラクタ

	void Initialize(Vector2D vec, Vector2D loc, float s, float r, float d, int t); //初期化処理
	void Update(); //更新処理
	void Draw();//描画処理
	void Finalize();//終了処理


	Vector2D GetVector() { return vector; }
	Vector2D GetLocation() { return location; }
	float GetSpeed() { return speed; }
	float GetRadius() { return radius; }
	float GetDamage() { return damage; }
	int GetType() { return type; }
};

