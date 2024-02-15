#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Resource/FontManager.h"
#include "../Resource/SoundManager.h"
#include "../Utility/TakePicture.h"

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

	/*menu_image = LoadGraph("Resource/images/menu.bmp");*/

	cursor_image = LoadGraph("Resource/images/aiming.png");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	/*if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}*/
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}

	if (CheckSoundMem(SoundManager::GetBGM(1)) == 0) {
		if (CheckSoundMem(SoundManager::GetBGM(0)) == 1 || CheckSoundMem(SoundManager::GetBGM(3)) == 1) {
			StopSoundMem(SoundManager::GetBGM(0));
			StopSoundMem(SoundManager::GetBGM(3));
			PlaySoundMem(SoundManager::GetBGM(1), DX_PLAYTYPE_LOOP, TRUE);
		}
		else {
			PlaySoundMem(SoundManager::GetBGM(1), DX_PLAYTYPE_LOOP, FALSE);
		}
	}

	back_img_num_all = 0;
	TakePicture tmp;
	std::string path;
	tmp.SeekNum();
	for (int i = 0; i < tmp.GetNum(); i++)
	{
		path = "Resource/images/img" + std::to_string(i) + ".png";
		back_img[i] = LoadGraph(path.c_str());
		if (back_img[i] != -1) {
			back_img_num_all++;
		}
	}
	back_img_num = 0;
	fps = 500;
	location = { -100,-100 };
	vector = { 0,0 };
	angle = 0;
	rote = 1;
	head_img[0] = LoadGraph("Resource/images/mob.png");
	head_img[1] = LoadGraph("Resource/images/mob2.png");
	head_type = 0;
	type = 0;
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
		PlaySoundMem(SoundManager::GetSE(6), DX_PLAYTYPE_BACK, TRUE);
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

		if(PlaySoundMem(SoundManager::GetSE(6), DX_PLAYTYPE_BACK, TRUE) == -1){
			throw("カーソル移動音が再生されませんでした");
		}
		
	
	}

	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(SoundManager::GetSE(7), DX_PLAYTYPE_BACK, TRUE);
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

	if (fps++ > 540 && (location.x < 0 || location.x > 1280 ||location.y < 0 || location.y > 720)) {
		switch (GetRand(3))
		{
		case 0:
			location = { -100,100 };
			vector = { 5,0 };
			type = 0;
			break;

		case 1:
			location = { 1300,600 };
			vector = { -5,0 };
			type = 1;
			break;

		case 2:
			location = { 1200,800 };
			vector = { -5,-10 };
			type = 2;
			break;

		case 3:
			location = { 30,800 };
			vector = { 5,-10 };
			type = 3;
			break;

		default:
			break;
		}
		head_type = GetRand(1);
		back_img_num = GetRand(back_img_num_all - 1);
		fps = 0;
	}
	location += vector;
	if (type == 2) {
		angle += 0.3;
	}
	else if (type == 3) {
		angle += 0.1;
	}
	else {
		angle = 0;
	}
	if (type == 3) {
		vector.y += 0.1;
	}

	
	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	////タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	DrawRotaGraph(location.x, location.y, rote, angle , back_img[back_img_num], TRUE);
	switch (head_type)
	{
	case 0:
		DrawRotaGraphF(location.x + 3, location.y + 58, 1.80 * rote, 0.0 + angle, head_img[0], TRUE);	// 鬼
		break;

	case 1:
		DrawRotaGraphF(location.x - 10, location.y - 20, 1.2 * rote, 0.3 + angle, head_img[1], TRUE);	// 鹿
		break;

	default:
		break;
	}

	////メニュー画像の描画
	//DrawGraph(120, 200, menu_image, TRUE);

	////カーソル画像の描画
	DrawRotaGraph(450, 280 + menu_cursor * 100, 0.1, DX_PI / 2.0, cursor_image, TRUE);

	//DrawCircle(450, 280 + menu_cursor * 100, 3, 0x00ff00, TRUE);

	DrawStringToHandle(406, 56, "KAO-", 0x000000, FontManager::GetFont(4));
	DrawStringToHandle(503, 253, "START", 0x000000, FontManager::GetFont(5));
	DrawStringToHandle(503, 353, "RANKING", 0x000000, FontManager::GetFont(5));
	DrawStringToHandle(503, 453, "HELP", 0x000000, FontManager::GetFont(5));
	DrawStringToHandle(503, 553, "END", 0x000000, FontManager::GetFont(5));

	DrawStringToHandle(400, 50, "KAO-", 0xffffff, FontManager::GetFont(4));
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
	for (int i = 0; i < 32; i++){
		DeleteGraph(back_img[i]);
		if (i < 2) {
			DeleteGraph(head_img[i]);
		}
	}
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}