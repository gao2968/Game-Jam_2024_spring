#pragma once
#include "SceneBase.h"
#include "../Utility/TakePicture.h"
class TakePictureScene : public SceneBase
{
private:
	TakePicture picture;
	int img[128];
	int took_flg;
	int state; //0、今から写真取りますよー　1、写真撮りまーす　2、この写真でいいですか？ 
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

