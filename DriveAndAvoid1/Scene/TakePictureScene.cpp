#include "TakePictureScene.h"
#include "../Utility/InputControl.h"
#include "../Resource/FontManager.h"

TakePictureScene::TakePictureScene()
{
	for (int i = 0; i < 128; i++)
	{
		img[i] = 0;
	}
	picture.Initialize();
	took_flg = false;
	state = 0;
	img_face[0] = LoadGraph("Resource/images/kao.png");
	img_face[1] = LoadGraph("Resource/images/kao1.png");
	cursor = 0;
	background_img = LoadGraph("Resource/images/background.jpg");
}

TakePictureScene::~TakePictureScene()
{
}

void TakePictureScene::Initialize()
{
}

eSceneType TakePictureScene::Update()
{
	switch (state)
	{
	case 0:
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B)) {
			state = 1;
		}
		break;

	case 1:
		if (took_flg == false) {
			picture.Update();
		}

		if (picture.Take() && took_flg == false) {
			img[picture.GetNum()] = LoadGraph(picture.GetPath().c_str());
			took_flg = true;
			num = picture.GetNum();
			state = 2;
		}

		break;

	case 2:
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT)) {
			cursor = 0;
		}
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT)) {
			cursor = 1;
		}

		if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && cursor == 1) {
			return eSceneType::E_MAIN;
		}
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && cursor == 0) {
			state = 1;
			took_flg = false;
			remove(picture.GetPath().c_str());
		}

		break;


	default:
		break;
	}

	
	if (took_flg == false) {
		picture.Update();
	}
	
	



	return GetNowScene();
}

void TakePictureScene::Draw() const
{
	DrawGraph(0, 0, background_img, TRUE);
	switch (state)
	{
	case 0://写真撮りますよーとかこの写真はプレイヤー画像になりますよーみたいな説明を書く
		/*DrawString(0, 0, "写真を撮ります", 0xffffff);
		DrawString(0, 30, "顔が認識されてからBボタンを押してください。", 0xffffff);
		DrawString(0, 60, "顔が認識されているときは、顔が赤い四角で囲まれています。", 0xffffff);*/

		//DrawStringToHandle(0, 90, "写真を撮ります", 0xffffff, FontManager::GetFont(0));

		
		DrawRotaGraph(320, 500, 0.7f, 0.0f, img_face[0], TRUE);
		DrawRotaGraph(960, 500, 0.7f, 0.0f, img_face[1], TRUE);
		

		DrawStringToHandle(150, 50, "これから写真を撮ります", 0xffffff,FontManager::GetFont(6));
		DrawStringToHandle(150, 150, "顔が赤い四角で囲われているときに", 0xffffff,FontManager::GetFont(7));
		DrawStringToHandle(150, 200, "Bボタンを押してください", 0xffffff,FontManager::GetFont(7));
		DrawStringToHandle(1050, 680, "Bボタンで次へ", 0x000000,FontManager::GetFont(8));
		break;

	case 1://特に説明とかは必要ない。別のウィンドウが出るから
		//DrawString(0, 0, "写真を撮ってます", 0xffffff);
		DrawStringToHandle(380, 50, "写真を撮ってます", 0xffffff, FontManager::GetFont(6));
		DrawStringToHandle(400, 650, "Bボタンで撮影", 0xffffff, FontManager::GetFont(6));
		//picture.Draw();
		break;

	case 2://写真これでいいですか？とか聞く
		//DrawString(0, 0, "写真を撮りました", 0xffffff);
		DrawStringToHandle(380, 50, "この写真でいいですか？", 0xffffff, FontManager::GetFont(6));
		DrawRotaGraph(640, 360, 2.0f, 0.0f, img[num], TRUE);
		DrawStringToHandle(400, 650, "いいえ", 0xffffff, FontManager::GetFont(6));
		DrawStringToHandle(800, 650, "はい", 0xffffff, FontManager::GetFont(6));
		DrawCircle(400 + cursor * 400, 650, 30 ,0xffff00, TRUE);
		break;


	default:
		break;
	}

	if (state == 1) {
		picture.Draw();
	}
	

}

void TakePictureScene::Finalize()
{
}

eSceneType TakePictureScene::GetNowScene() const
{
	return eSceneType::E_TAKE_PICTURE;
}
