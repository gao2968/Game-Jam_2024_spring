#pragma once

#include "SceneBase.h"
#include "../Utility/Vector2D.h"


class TitleScene : public SceneBase
{
private:

private:
	int background_image;		//背景画像
	int menu_image;					//メニュー画像
	int cursor_image;				//カーソル画像
	int menu_cursor;			//メニューカーソル番号

	//ここから背景の人関連
	int back_img[32];
	int back_img_num;
	int back_img_num_all;
	Vector2D vector;
	Vector2D location;
	float angle;
	float rote;
	int fps;
	int type;
	int head_img[2];
	int head_type;

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

