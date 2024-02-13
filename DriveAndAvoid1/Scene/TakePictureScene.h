#pragma once
#include "SceneBase.h"
#include "../Utility/TakePicture.h"
class TakePictureScene : public SceneBase
{
private:
	TakePicture picture;
	int img[128];
public:
	TakePictureScene();
	~TakePictureScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

