#pragma once
#include "SceneBase.h"

class EndScene : public SceneBase
{
private:
	int img;
	int fps;

public:
	EndScene();
	~EndScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

