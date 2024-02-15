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
	DrawStringToHandle(100, 200, "�g�p�����f�ރT�C�g", 0x0000aa, FontManager::GetFont(7));
	DrawStringToHandle(100, 250, "LovePik    https://jp.lovepik.com/", 0x0000aa, FontManager::GetFont(8));
	DrawStringToHandle(100, 300, "FREE BGM DOVA-SYNDROME   https://dova-s.jp/", 0x0000aa, FontManager::GetFont(8));
	DrawStringToHandle(100, 350, "pixabay   https://pixabay.com/ja/", 0x0000aa, FontManager::GetFont(8));
	DrawStringToHandle(100, 400, "�C���X�gAC   https://www.ac-illust.com/", 0x0000aa, FontManager::GetFont(8));
	DrawStringToHandle(100, 450, "���ʉ����{   https://soundeffect-lab.info/", 0x0000aa, FontManager::GetFont(8));

	//�f�ފm�肵���炱�̉��ɏ�������
}

void EndScene::Finalize()
{
}

eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END1;
}
