#include "ResultScene.h"
#include "../Object/RankingData.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Resource/FontManager.h"

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
	//画像の読み込み
	back_ground = LoadGraph("Resource/images/background.jpg");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);

	//エラーチェック
	if (back_ground == -1) 
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (result == -1) 
	{
		throw("Resource/images/car.bmpがありません\n");
	}

	//ゲーム結果の読み込み
	ReadResultData();
}

eSceneType ResultScene::Update()
{
	//	Bボタンでランキングに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_RANKING_INPUT;
	}

	return GetNowScene();
}

void ResultScene::Draw() const
{
	//背景画像を描画
	DrawGraph(0, 0, back_ground, TRUE);

	//スコア等表示領域
	//DrawBox(150, 150, 490, 330, GetColor(0, 153, 0), TRUE);
	//DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), TRUE);

	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), FALSE);

	//SetFontSize(20);
	//DrawString(220, 170, "ゲームオーバー", GetColor(204, 0, 0));
	//SetFontSize(16);
	//DrawString(180, 200, "走行処理		", GetColor(0, 0, 0));
	//for (int i = 0; i < 3; i++) 
	//{
	//	DrawRotaGraph(230, 230 + (i * 20), 0.3f, DX_PI_F / 2, enemy_image[i], TRUE);
	//	DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x %4d = %6d", enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);
	//}
	//DrawString(180, 290, "スコア", GetColor(0, 0, 0));
	//DrawFormatString(180, 290, 0xffffff, "		=%6d", score);


	DrawStringToHandle(320, 170, "SCORE", GetColor(255, 255, 255), FontManager::GetFont(4));
	DrawFormatStringToHandle(320, 350, GetColor(255, 255, 255), FontManager::GetFont(4), "%d", score);
	DrawStringToHandle(280, 550, "PRESS TO [B]BUTTON", GetColor(255, 255, 255), FontManager::GetFont(3));
}

void ResultScene::Finalize()
{
	//読み込んだ画像を削除
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
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("resource/dat/result_data.csvが読み込めません\n");
	}

	//結果を読み込む
	fscanf_s(fp, "%6d,\n", &score);

	//よけた数と得点を取得
	for (int i = 0; i < 3; i++) 
	{
		fscanf_s(fp, "6d,\n", &enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);
}
