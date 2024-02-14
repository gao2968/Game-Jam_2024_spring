#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Resource/FontManager.h"

TitleScene::TitleScene() : background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/background.jpg");

	menu_image = LoadGraph("Resource/images/menu.bmp");

	cursor_image = LoadGraph("Resource/images/aiming.png");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
}

eSceneType TitleScene::Update()
{
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//一番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}


	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//一番下に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	//カーソル決定（決定した画面に遷移する）
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
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	////タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	////メニュー画像の描画
	//DrawGraph(120, 200, menu_image, TRUE);

	////カーソル画像の描画
	DrawRotaGraph(450, 280 + menu_cursor * 100, 0.1, DX_PI / 2.0, cursor_image, TRUE);

	//DrawCircle(450, 280 + menu_cursor * 100, 3, 0x00ff00, TRUE);

	DrawStringToHandle(200, 50, "kokonititle", 0xffffff, FontManager::GetFont(4));
	DrawStringToHandle(500, 250, "START", 0xffffff, FontManager::GetFont(5));
	DrawStringToHandle(500, 350, "RANKING", 0xffffff, FontManager::GetFont(5));
	DrawStringToHandle(500, 450, "HELP", 0xffffff, FontManager::GetFont(5));
	DrawStringToHandle(500, 550, "END", 0xffffff, FontManager::GetFont(5));
	//DrawStringToHandle(320, 170, "", GetColor(255, 255, 255), FontManager::GetFont(4));

}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}