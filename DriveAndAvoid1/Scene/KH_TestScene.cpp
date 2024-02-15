#include "KH_TestScene.h"

KH_TestScene::KH_TestScene()
{
	//test.Initialize();
}

KH_TestScene::~KH_TestScene()
{
}

void KH_TestScene::Initialize()
{
}

eSceneType KH_TestScene::Update()
{
	//test.Update();
	return GetNowScene();
}

void KH_TestScene::Draw() const
{
	//test.Draw();
}

void KH_TestScene::Finalize()
{
}

eSceneType KH_TestScene::GetNowScene() const
{
	return eSceneType::E_TEST;
}
