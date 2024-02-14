#pragma once
#include "SceneBase.h"

class RuleScene : public SceneBase
{
private:
	int background_img;
	int aiming_img;
	int cursor;
public:
	RuleScene();
	~RuleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

