#pragma once
#include "SceneBase.h"
#include "../Utility/TakePicture.h"

class KH_TestScene : public SceneBase
{
private:
	//TakePicture test;

public:
	KH_TestScene();
	~KH_TestScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

