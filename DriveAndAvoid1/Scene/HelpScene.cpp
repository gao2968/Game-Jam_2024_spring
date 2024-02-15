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

//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/background.jpg");
	controller_img = LoadGraph("Resource/images/help.png");
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
	DrawRotaGraph(700, 410, 1.4, 0,controller_img,TRUE);

	// ゲームの説明

	DrawStringToHandle(520,71, "操作方法", 0xffffff, FontManager::GetFont(6));
	DrawStringToHandle(98 ,240, "【上下の移動】", 0x393A52, FontManager::GetFont(7));
	DrawStringToHandle(176,315, "十字キー", 0x393A52, FontManager::GetFont(7));

	DrawStringToHandle(135,480, "【上下の移動】", 0x393A52, FontManager::GetFont(7));
	DrawStringToHandle(195,549, "左カーソル", 0x393A52, FontManager::GetFont(7));

	DrawStringToHandle(780, 165, "【弾の発射】", 0x523B3C, FontManager::GetFont(7));
	DrawStringToHandle(770, 228, " RBボタン", 0x523B3C, FontManager::GetFont(7));

	DrawStringToHandle(900,412, "【照準の移動】", 0x4F3B20, FontManager::GetFont(7));
	DrawStringToHandle(920,487, " 右カーソル", 0x4F3B20, FontManager::GetFont(7));

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