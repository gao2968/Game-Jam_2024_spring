#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Resource/FontManager.h"
#include "../Resource/SoundManager.h"

TitleScene::TitleScene() : background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/background.jpg");

	menu_image = LoadGraph("Resource/images/menu.bmp");

	cursor_image = LoadGraph("Resource/images/aiming.png");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}

	if (CheckSoundMem(SoundManager::GetBGM(1)) == 0) {
		if (CheckSoundMem(SoundManager::GetBGM(0)) == 1 || CheckSoundMem(SoundManager::GetBGM(3)) == 1) {
			StopSoundMem(SoundManager::GetBGM(0));
			StopSoundMem(SoundManager::GetBGM(3));
		}
		//PlaySoundMem(SoundManager::GetBGM(1), DX_PLAYTYPE_LOOP, FALSE);
	}
}

eSceneType TitleScene::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//��ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
		PlaySoundMem(SoundManager::GetBGM(6), DX_PLAYTYPE_LOOP, TRUE);
	}


	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//��ԉ��ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
		PlaySoundMem(SoundManager::GetBGM(6), DX_PLAYTYPE_BACK, TRUE);
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			return eSceneType::E_TAKE_PICTURE;
		case 1:
			return eSceneType::E_RANKING_DISP;
		case 2:
			return eSceneType::E_HELP;
		default:
			return eSceneType::E_END1;
		}
		PlaySoundMem(SoundManager::GetBGM(7), DX_PLAYTYPE_BACK, TRUE);
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{
	////�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	////���j���[�摜�̕`��
	//DrawGraph(120, 200, menu_image, TRUE);

	////�J�[�\���摜�̕`��
	DrawRotaGraph(450, 280 + menu_cursor * 100, 0.1, DX_PI / 2.0, cursor_image, TRUE);

	//DrawCircle(450, 280 + menu_cursor * 100, 3, 0x00ff00, TRUE);

	DrawStringToHandle(206, 56, "kokonititle", 0x000000, FontManager::GetFont(4));
	DrawStringToHandle(503, 253, "START", 0x000000, FontManager::GetFont(5));
	DrawStringToHandle(503, 353, "RANKING", 0x000000, FontManager::GetFont(5));
	DrawStringToHandle(503, 453, "HELP", 0x000000, FontManager::GetFont(5));
	DrawStringToHandle(503, 553, "END", 0x000000, FontManager::GetFont(5));

	DrawStringToHandle(200, 50, "kokonititle", 0xffffff, FontManager::GetFont(4));
	DrawStringToHandle(500, 250, "START", 0xffffff, FontManager::GetFont(5));
	DrawStringToHandle(500, 350, "RANKING", 0xffffff, FontManager::GetFont(5));
	DrawStringToHandle(500, 450, "HELP", 0xffffff, FontManager::GetFont(5));
	DrawStringToHandle(500, 550, "END", 0xffffff, FontManager::GetFont(5));
	//DrawStringToHandle(320, 170, "", GetColor(255, 255, 255), FontManager::GetFont(4));

}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}