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
	int head_images;

	float speed;		// 速さ
	int hp;				// 体力
	float bullet_speed; // 球の速さ

	Vector2D location;	// 位置情報
	Vector2D box_size;	// 当たり判定の大きさ
	Vector2D b_vector[3];	// 飛ばす方向指定用

	Bullet** e_bullet;

private:// csvファイル読み込みで使う変数
	int E_num;
	int point;
	bool hit;
	int color;
	int WaitTime;
	int Type;
	int radius;			// 円の大きさ
	int image_num;		// 敵画像の番号を認識する為の変数
private:

	int LateTime;		// 球の発射速度を管理する為の変数
	int bullet_Timing;	// 弾の感覚時間（レートの設定.後々エクセルで管理する） 
	bool hanten;		// 移動方向が反転するタイミングを見る変数
	bool End;			// ボスを倒した判定

	float y_speed;		// ボスがY座標移動するスピード
public:

	// １.x座標　２.Y座標　３.半径　４.スピード　５.弾のスピード　６.倒した時のスコア数　７.HP　８.何番目の敵か見る用　９.画像ハンドル
	Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int hp, int E_num, int type, int handle,int hed_handle,int img_num);
	~Enemy();

	void Initialize();			// 初期化処理用
	void Update(float speed, GameMainScene* game, Vector2D player);// 更新処理
	void Draw()const;			// 描画処理
	void Finalize();			// 終了時の処理

	int GetType()const;			// タイプの取得
	Vector2D GetLocation();		// 位置情報の取得
	Vector2D GetBoxSize();		// 当たり判定の大きさを取得

	int Get_Radius();
	float Get_HP();
	bool Get_BossDown();		// ボスの死亡判定を取る
	int Get_Score();			// スコアを取得する

	void Set_HP(float damege);				// HPセット

private:
	void Boss_System(GameMainScene* game, Vector2D player);		// ボスの行動パターン
};