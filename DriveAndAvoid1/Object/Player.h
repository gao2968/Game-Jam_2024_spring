#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize(); //初期化処理
	void Update(); //更新処理
	void Draw();//描画処理
	void Finalize();//終了処理

public:
	void SetActive(bool flg);//有効フラグ
	void DecreaseHp(float value);//体力減少処理
	Vector2D GetLocation() const;//位置座標の取得
	Vector2D GetBoxSize() const;//当たり判定の大きさの取得
	float GetSpeed() const;//速さ取得処理
	float GetFuel() const;//燃料取得処理
	float GetHp() const;//体力取得処理
	int GetBarriarCount() const;//バリアの枚数取得
	bool IsBarrier() const;//バリアは有効か？を取得

private:
	bool is_active; //有効常態か？
	int image;		//画像データ

	Vector2D location;//位置座標
	Vector2D box_size;//当たり判定の大きさ
	
	float angle;//角度
	float speed;//速さ
	float hp;//体力
	float fuel;//燃料
	int barrier_count;//バリアの枚数
	Barrier* barrier;//バリア

private:
	void Movement();//移動処理
	void Acceleration();//加速処理

private:
	static Vector2D stick[2];  // 左右スティック入力値

public:// 後で消す
	Vector2D Aim;

	Vector2D Get_AimLocation();
};