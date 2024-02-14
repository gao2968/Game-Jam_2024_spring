#pragma once
#include "SceneBase.h"
#include "../Utility/TakePicture.h"
class TakePictureScene : public SceneBase
{
private:
	TakePicture picture;
	int img[128];
	int took_flg;
	int state; //0�A������ʐ^���܂���[�@1�A�ʐ^�B��܁[���@2�A���̎ʐ^�ł����ł����H 
	int num;
	int img_face[2];
	int cursor;
	int background_img;
	int aimingImg;
public:
	TakePictureScene();
	~TakePictureScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

