#pragma once
#include "SceneBase.h"
#include "../Object/Player.h" /*../Object/Player.h*/
#include "../Object/Enemy.h"  /*../Object/Enemy.h*/

class GameMainScene:public SceneBase
{
private:
	int high_score;			// ハイスコア
	int back_ground;		// 背景画像
	int barrier_image;		// バリア画像
	int mileage;			// 走行距離
	int enemy_image[3];		// 敵画像
	int enemy_count[3];		// 通り過ぎた敵のカウント
	Player* player;			// プレイヤー
	Enemy** enemy;			// 敵
public:
	GameMainScene();
	~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// ハイスコア読込処理
	void ReadHighScore();
	// あたり判定
	bool IsHitCheck(Player* p, Enemy* e);
};

