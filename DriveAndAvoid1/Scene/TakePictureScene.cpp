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
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B)) {
			return eSceneType::E_MAIN;
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
	DrawGraph(100, 0, img[num], TRUE);
	switch (state)
	{
	case 0://写真撮りますよーとかこの写真はプレイヤー画像になりますよーみたいな説明を書く
		DrawString(0, 0, "写真を撮ります", 0xffffff);
		DrawString(0, 30, "顔が認識されてからBボタンを押してください。", 0xffffff);
		DrawString(0, 60, "顔が認識されているときは、顔が赤い四角で囲まれています。", 0xffffff);

		DrawStringToHandle(0, 90, "写真を撮ります", 0xffffff, FontManager::GetFont0());
		break;

	case 1://特に説明とかは必要ない。別のウィンドウが出るから
		DrawString(0, 0, "写真を撮ってます", 0xffffff);
		//picture.Draw();
		break;

	case 2://写真これでいいですか？とか聞く
		DrawString(0, 0, "写真を撮りました", 0xffffff);
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
