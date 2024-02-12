#pragma once
#include "../Utility/Vector2D.h"

class Enemy
{
private:
	int type;			// タイプ
	int image;			// 画像
	float speed;		// 速さ
	int hp;				// 体力
	float bullet_speed; // 球の速さ

	Vector2D location;	// 位置情報
	Vector2D box_size;	// 当たり判定の大きさ
	Vector2D a;

private:
	// csvファイル読み込みで使う変数
	int E_num;
	int point;
	bool hit;
	int color;
	int WaitTime;

	int Type;

	/*float Set_PlocationX;
	float Set_PlocationY;*/

	int radius;			// 円の大きさ
public:

	// csvから取得する用のコンストラクタ
	Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int hp, int E_num, int type, int handle);
	~Enemy();

	void Initialize();			// 初期化処理用
	void Update(float speed);	// 更新処理
	void Draw()const;			// 描画処理
	void Finalize();			// 終了時の処理

	int GetType()const;			// タイプの取得
	Vector2D GetLocation();		// 位置情報の取得
	Vector2D GetBoxSize();		// 当たり判定の大きさを取得
};

