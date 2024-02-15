#include "ResultScene.h"
#include "../Object/RankingData.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Resource/FontManager.h"
#include "../Resource/SoundManager.h"


ResultScene::ResultScene() : back_ground(NULL), score(0)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/background.jpg");
	/*int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);*/

	//�G���[�`�F�b�N
	if (back_ground == -1) 
	{
		throw("Resource/images/back.bmp������܂���\n");
	}
	/*if (result == -1) 
	{
		throw("Resource/images/car.bmp������܂���\n");
	}*/

	//�Q�[�����ʂ̓ǂݍ���
	ReadResultData();
}

eSceneType ResultScene::Update()
{
	//	B�{�^���Ń����L���O�ɑJ�ڂ���
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(SoundManager::GetSE(7), DX_PLAYTYPE_BACK, TRUE);
		if (score >= RankingData::GetScore(4)) {
			return eSceneType::E_RANKING_INPUT;
		}
		else {
			return eSceneType::E_RANKING_DISP;
		}
	}

	return GetNowScene();
}

void ResultScene::Draw() const
{
	//�w�i�摜��`��
	DrawGraph(0, 0, back_ground, TRUE);

	DrawStringToHandle(320, 170, "SCORE", GetColor(0, 0, 0), FontManager::GetFont(4));
	DrawFormatStringToHandle(320, 350, GetColor(0, 0, 0), FontManager::GetFont(4), "%d", score);
	DrawStringToHandle(280, 550, "PRESS TO [B]BUTTON", GetColor(0, 0, 0), FontManager::GetFont(3));

	DrawStringToHandle(328, 178, "SCORE", GetColor(255, 255, 255), FontManager::GetFont(4));
	DrawFormatStringToHandle(328, 358, GetColor(255, 255, 255), FontManager::GetFont(4), "%d", score);
	DrawStringToHandle(284, 554, "PRESS TO [B]BUTTON", GetColor(255, 255, 255), FontManager::GetFont(3));
}

void ResultScene::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++) 
	{
		DeleteGraph(enemy_image[i]);
	}
}

eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

void ResultScene::ReadResultData()
{
	//�t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("resource/dat/result_data.csv���ǂݍ��߂܂���\n");
	}

	//���ʂ�ǂݍ���
	fscanf_s(fp, "%6d,\n", &score);

	//�悯�����Ɠ��_���擾
	for (int i = 0; i < 3; i++) 
	{
		fscanf_s(fp, "6d,\n", &enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);
}
