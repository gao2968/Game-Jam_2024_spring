#include "RuleScene.h"
#include "DxLib.h"
#include "../Resource/FontManager.h"
#include "../Utility/TakePicture.h"
#include "../Utility/InputControl.h"

RuleScene::RuleScene()
{
	background_img = LoadGraph("Resource/images/background.jpg");
	aiming_img = LoadGraph("Resource/images/aiming.png");
	cursor = 0;
}

RuleScene::~RuleScene()
{
}

void RuleScene::Initialize()
{
}

eSceneType RuleScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT)) {
		cursor = 0;
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT)) {
		cursor = 1;
	}

	TakePicture p;
	p.SeekNum();
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && cursor == 1) {
		return eSceneType::E_RESULT;
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && cursor == 0) {
		remove(p.GetPath().c_str());
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

void RuleScene::Draw() const
{
	DrawGraph(0, 0, background_img, TRUE);

	DrawStringToHandle(200, 100, "QUESTION", 0xffffff, FontManager::GetFont(4));
	
	DrawStringToHandle(150, 300, "今回使用したあなたの顔面を", 0xffffff, FontManager::GetFont(7));
	DrawStringToHandle(150, 400, "この先敵として出現させていいですか？", 0xffffff, FontManager::GetFont(7));

	DrawStringToHandle(400, 650, "いいえ", 0xffffff, FontManager::GetFont(6));
	DrawStringToHandle(800, 650, "はい", 0xffffff, FontManager::GetFont(6));
	DrawRotaGraph(350 + cursor * 400, 680, 0.1, DX_PI / 2.0, aiming_img, TRUE);
}

void RuleScene::Finalize()
{
	DeleteGraph(background_img);
	DeleteGraph(aiming_img);
}

eSceneType RuleScene::GetNowScene() const
{
	return eSceneType::E_RULE;
}
