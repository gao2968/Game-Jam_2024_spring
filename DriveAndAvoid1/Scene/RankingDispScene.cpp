#include "RankingDispScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Resource/FontManager.h"
#include "../Resource/SoundManager.h"

RankingDispScene::RankingDispScene() : background_image(NULL)
{

}

RankingDispScene::~RankingDispScene()
{

}
//初期化処理
void RankingDispScene::Initialize()
{
    //画像の読み込み
    background_image = LoadGraph("Resource/images/background.jpg");

    //エラーチェック
    if (background_image == -1)
    {
        throw("Resource/images/Ranking.bmpがありません\n");
    }

    //ランキング情報を取得
    /*ranking = new RankingData;
    ranking->Initialize();*/
}

eSceneType RankingDispScene::Update()
{
    //Bボタンが押されたら、タイトルに戻る
    if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
    {
        PlaySoundMem(SoundManager::GetSE(7), DX_PLAYTYPE_BACK, TRUE);
        return eSceneType::E_TITLE;
    }

    return GetNowScene();
}

void RankingDispScene::Draw() const
{
    //背景画像の描画
    DrawGraph(0, 0, background_image, FALSE);

    //取得したランキングデータを描画する
    for (int i = 0; i < 5; i++)
    {
       /* DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %-15s %6d",
            ranking->GetRank(i), ranking->GetName(i), ranking->GetScore(i));*/
        //DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %-15s %6d",RankingData::GetRank(i), RankingData::GetName(i), RankingData::GetScore(i));
       

        DrawFormatStringToHandle(300, 300 + i * 70, GetColor(0, 0, 0), FontManager::GetFont(3), "%2d %-15s", RankingData::GetRank(i), RankingData::GetName(i));
        DrawFormatStringToHandle(303, 303 + i * 70, GetColor(255, 255, 255), FontManager::GetFont(3), "%2d %-15s", RankingData::GetRank(i), RankingData::GetName(i));

        DrawFormatStringToHandle(800, 300 + i * 70, GetColor(0, 0, 0), FontManager::GetFont(3), "%6d", RankingData::GetScore(i));
        DrawFormatStringToHandle(803, 303 + i * 70, GetColor(255, 255, 255), FontManager::GetFont(3), "%6d", RankingData::GetScore(i));
    }
    DrawStringToHandle(300, 100, "RANKING", 0x0000aa, FontManager::GetFont(4));

    DrawStringToHandle(500, 680, "Bボタンでタイトルへ", 0x000000, FontManager::GetFont(8));

}

void RankingDispScene::Finalize()
{
    //読み込んだ画像の削除
    DeleteGraph(background_image);

    //動的メモリの解放
    //ranking->Finalize();

    //delete ranking;
}

eSceneType RankingDispScene::GetNowScene() const
{
    return eSceneType::E_RANKING_DISP;
}
