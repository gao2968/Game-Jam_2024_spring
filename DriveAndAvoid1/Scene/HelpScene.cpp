#include "HelpScene.h"
#include "../utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL),help_img(NULL)
{

}

HelpScene::~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/background.jpg");
	help_img = LoadGraph("Resource/images/help.png");
	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
}
//更新処理
eSceneType HelpScene::Update()
{
	//Bボタンが押されたらタイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//描画処理
void HelpScene::Draw() const
{
	//背景の描画処理
	DrawGraph(0, 0, background_image, FALSE);
	DrawRotaGraph(200, 100, 2.0, 0,help_img,TRUE);

	//ゲームの説明
	SetFontSize(16);
	DrawString(20, 120, "ヘルプ画面", 0xffffff, 0);

	DrawString(20, 160, "これは障害物を避けながら", 0xffffff, 0);
	DrawString(20, 180, "走り続けるゲームです", 0xffffff, 0);
	DrawString(20, 200, "燃料が尽きるか障害物に", 0xffffff, 0);
	DrawString(20, 220, "数回当たるとゲームオーバーです", 0xffffff, 0);

	DrawString(150, 450, "---Bボタンを押してタイトルへ戻る---", 0xffffff, 0);
}

//終了処理
void HelpScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}