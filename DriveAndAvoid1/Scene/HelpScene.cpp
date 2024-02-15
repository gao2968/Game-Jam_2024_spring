#include "HelpScene.h"
#include "../utility/InputControl.h"
#include "DxLib.h"
#include"../Resource/FontManager.h"

HelpScene::HelpScene() : background_image(NULL),controller_img(NULL)
{

}

HelpScene::~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/background.jpg");
	controller_img = LoadGraph("Resource/images/help.png");
	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
}
//�X�V����
eSceneType HelpScene::Update()
{
	//B�{�^���������ꂽ��^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//�`�揈��
void HelpScene::Draw() const
{
	
	//�w�i�̕`�揈��
	DrawGraph(0, 0, background_image, FALSE);
	DrawRotaGraph(700, 410, 1.4, 0,controller_img,TRUE);

	// �Q�[���̐���

	DrawStringToHandle(520,71, "������@", 0xffffff, FontManager::GetFont(6));
	DrawStringToHandle(98 ,240, "�y�㉺�̈ړ��z", 0x393A52, FontManager::GetFont(7));
	DrawStringToHandle(176,315, "�\���L�[", 0x393A52, FontManager::GetFont(7));

	DrawStringToHandle(135,480, "�y�㉺�̈ړ��z", 0x393A52, FontManager::GetFont(7));
	DrawStringToHandle(195,549, "���J�[�\��", 0x393A52, FontManager::GetFont(7));

	DrawStringToHandle(780, 165, "�y�e�̔��ˁz", 0x523B3C, FontManager::GetFont(7));
	DrawStringToHandle(770, 228, " RB�{�^��", 0x523B3C, FontManager::GetFont(7));

	DrawStringToHandle(900,412, "�y�Ə��̈ړ��z", 0x4F3B20, FontManager::GetFont(7));
	DrawStringToHandle(920,487, " �E�J�[�\��", 0x4F3B20, FontManager::GetFont(7));

}

//�I������
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�����擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}