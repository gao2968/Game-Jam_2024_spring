#include "TakePictureScene.h"
#include "../Utility/InputControl.h"
#include "../Resource/FontManager.h"
#include "../Resource/SoundManager.h"

TakePictureScene::TakePictureScene()
{
	for (int i = 0; i < 128; i++)
	{
		img[i] = 0;
	}
	//picture.Initialize();
	took_flg = false;
	state = 0;
	img_face[0] = LoadGraph("Resource/images/kao.png");
	img_face[1] = LoadGraph("Resource/images/kao1.png");
	cursor = 0;
	background_img = LoadGraph("Resource/images/background.jpg");
	aimingImg = LoadGraph("Resource/images/aiming.png");
	TakePicture::init();
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
			PlaySoundMem(SoundManager::GetSE(7), DX_PLAYTYPE_BACK, TRUE);
			state = 1;
		}
		break;

	case 1:
		if (took_flg == false) {
			//picture.Update();
			TakePicture::Update();
		}

		if (TakePicture::Take() && took_flg == false) {
			img[TakePicture::GetNum()] = LoadGraph(TakePicture::GetPath().c_str());
			took_flg = true;
			num = TakePicture::GetNum();
			state = 2;
			PlaySoundMem(SoundManager::GetSE(8), DX_PLAYTYPE_BACK, TRUE);

		}

		break;

	case 2:
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT)) {
			PlaySoundMem(SoundManager::GetSE(6), DX_PLAYTYPE_BACK, TRUE);
			cursor = 0;
		}
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT)) {
			PlaySoundMem(SoundManager::GetSE(6), DX_PLAYTYPE_BACK, TRUE);
			cursor = 1;
		}

		if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && cursor == 1) {
			PlaySoundMem(SoundManager::GetSE(7), DX_PLAYTYPE_BACK, TRUE);
			return eSceneType::E_MAIN;
		}
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && cursor == 0) {
			PlaySoundMem(SoundManager::GetSE(7), DX_PLAYTYPE_BACK, TRUE);
			state = 1;
			took_flg = false;
			remove(TakePicture::GetPath().c_str());
		}

		break;


	default:
		break;
	}

	
	if (took_flg == false) {
		TakePicture::Update();
	}

	return GetNowScene();
}

void TakePictureScene::Draw() const
{
	DrawGraph(0, 0, background_img, TRUE);
	switch (state)
	{
	case 0://�ʐ^�B��܂���[�Ƃ����̎ʐ^�̓v���C���[�摜�ɂȂ�܂���[�݂����Ȑ���������
		/*DrawString(0, 0, "�ʐ^���B��܂�", 0xffffff);
		DrawString(0, 30, "�炪�F������Ă���B�{�^���������Ă��������B", 0xffffff);
		DrawString(0, 60, "�炪�F������Ă���Ƃ��́A�炪�Ԃ��l�p�ň͂܂�Ă��܂��B", 0xffffff);*/

		//DrawStringToHandle(0, 90, "�ʐ^���B��܂�", 0xffffff, FontManager::GetFont(0));

		
		DrawRotaGraph(320, 500, 0.7f, 0.0f, img_face[0], TRUE);
		DrawRotaGraph(960, 500, 0.7f, 0.0f, img_face[1], TRUE);
		

		DrawStringToHandle(150, 50, "���ꂩ��ʐ^���B��܂�", 0xffffff,FontManager::GetFont(6));
		DrawStringToHandle(150, 150, "�炪�Ԃ��l�p�ň͂��Ă���Ƃ���", 0xffffff,FontManager::GetFont(7));
		DrawStringToHandle(150, 200, "B�{�^���������Ă�������", 0xffffff,FontManager::GetFont(7));
		DrawStringToHandle(1050, 680, "B�{�^���Ŏ���", 0x000000,FontManager::GetFont(8));
		break;

	case 1://���ɐ����Ƃ��͕K�v�Ȃ��B�ʂ̃E�B���h�E���o�邩��
		//DrawString(0, 0, "�ʐ^���B���Ă܂�", 0xffffff);
		DrawStringToHandle(380, 50, "�ʐ^���B���Ă܂�", 0xffffff, FontManager::GetFont(6));
		DrawStringToHandle(400, 650, "B�{�^���ŎB�e", 0xffffff, FontManager::GetFont(6));
		//picture.Draw();
		break;

	case 2://�ʐ^����ł����ł����H�Ƃ�����
		//DrawString(0, 0, "�ʐ^���B��܂���", 0xffffff);
		DrawStringToHandle(280, 50, "���̎ʐ^�ł����ł����H", 0xffffff, FontManager::GetFont(6));
		DrawRotaGraph(640, 360, 2.0f, 0.0f, img[num], TRUE);
		DrawStringToHandle(403, 653, "������", 0x000000, FontManager::GetFont(6));
		DrawStringToHandle(803, 653, "�͂�", 0x000000, FontManager::GetFont(6));
		DrawStringToHandle(400, 650, "������", 0xffffff, FontManager::GetFont(6));
		DrawStringToHandle(800, 650, "�͂�", 0xffffff, FontManager::GetFont(6));
		//DrawCircle(400 + cursor * 400, 650, 30 ,0xffff00, TRUE);
		DrawRotaGraph(350 + cursor * 400, 680, 0.1, DX_PI / 2.0, aimingImg, TRUE);
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
