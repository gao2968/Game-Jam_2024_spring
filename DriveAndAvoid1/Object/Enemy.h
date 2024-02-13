#pragma once

class GameMainScene;// 名前だけ書いておく

#include "../Utility/Vector2D.h"
#include"../Object/Bullet.h"
#define E_BULLET_MAX 256

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

	Bullet** e_bullet;

private:
	// csvファイル読み込みで使う変数
	int E_num;
	int point;
	bool hit;
	int color;
	int WaitTime;
	int Type;
	int radius;			// 円の大きさ

private:
	int LateTime;		// 球の発射速度を管理する為の変数
	int bullet_Timing;	// 弾の感覚時間（レートの設定.後々エクセルで管理する） 
	bool shot;
public:

	// csvから取得する用のコンストラクタ
	Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int hp, int E_num, int type, int handle);
	~Enemy();

	void Initialize();			// 初期化処理用
	void Update(float speed,GameMainScene *game);	// 更新処理
	void Draw()const;			// 描画処理
	void Finalize();			// 終了時の処理

	int GetType()const;			// タイプの取得
	Vector2D GetLocation();		// 位置情報の取得
	Vector2D GetBoxSize();		// 当たり判定の大きさを取得

	int Get_Radius();
	bool firing();				// レートが割り切れたタイミングでtrueを返す
};

