#include "EndScene.h"
#include "DxLib.h"
#include "../Resource/FontManager.h"

EndScene::EndScene()
{
	img = LoadGraph("Resource/images/background.jpg");
	fps = 0;
}

EndScene::~EndScene()
{
}

void EndScene::Initialize()
{
}

eSceneType EndScene::Update()
{
	if (fps++ > 300) {
		return eSceneType::E_END;
	}
	return GetNowScene();
}

void EndScene::Draw() const
{
	DrawGraph(0, 0, img, TRUE);

	DrawStringToHandle(100, 100, "THANK YOU FOR PLAYING", 0x0000aa, FontManager::GetFont(5));
	//‘fŞŠm’è‚µ‚½‚ç‚±‚Ì‰º‚É‘‚«‚Ş
}

void EndScene::Finalize()
{
}

eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END1;
}
