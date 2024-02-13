#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>
#include "../Utility/Collision.h"
#include"../Utility/InputControl.h"

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), barrier_image(NULL), mileage(0), player(nullptr),
enemy(nullptr) {
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Initialize()
{
	// 最高点を読み込む
	ReadHighScore();

	// 画像の読み込み
	back_ground = LoadGraph("Resource/images/back.bmp");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);
	// エラーチェック
	if (back_ground == -1) {
		throw("画像back.bmpがありません\n");
	}
	if (result == -1) {
		throw("画像car.bmpがありません\n");
	}
	if (barrier_image == -1) {
		throw("画像barrier_imageがありません\n");
	}

	// オブジェクトの生成
	player = new Player;

	// コンストラクタでcsv読込も行う
	e_spawn = new E_Spawn();
	enemy = new Enemy * [e_spawn->GetMaxEnemy()]; E_num = 0;
	bullet = new Bullet * [MAX_BULLET_NUM];

	// オブジェクトの初期化
	player->Initialize();

	for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++) {
		enemy[i] = nullptr;
	}
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet[i] = nullptr;
	}
}

eSceneType GameMainScene::Update()
{
	if (InputControl::GetButton(XINPUT_BUTTON_RIGHT_SHOULDER)) {
		SpawnBullet();
	}
	
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] != nullptr) {
			bullet[i]->Update();
		}
		
	}
	BulletManager();
	
	// プレイヤーの更新
	player->Update();

	// 移動量距離の更新 playerスピードを取得して+５した値をmileageに+する（毎フレーム）
	mileage += (int)player->GetSpeed() + 5;

	// 敵生成処理

	if (enemy[E_num] == nullptr) {
		// エネミーの出現時間に到達したら
		if (++e_spownCnt > e_spawn->LoadEnemy(E_num).time * 60) {

			//出現したエネミーの情報を全て送信
		 enemy[E_num] = new Enemy(
			 e_spawn->LoadEnemy(E_num).location_x		// X座標取得
			,e_spawn->LoadEnemy(E_num).location_y		// Y座標取得
			,e_spawn->LoadEnemy(E_num).radius			// 半径取得
			,e_spawn->LoadEnemy(E_num).speed			// スピード取得
			,e_spawn->LoadEnemy(E_num).bullet_speed		// 球のスピード取得
			,e_spawn->LoadEnemy(E_num).score			// 撃破時のスコア数取得
			, e_spawn->LoadEnemy(E_num).hp				// HP取得
			, E_num										// 今何体目なのか
			,1											// エネミーのタイプ（消すかも）
			,enemy_image[1]								// エネミーの画像
		 );
			// エネミーの数がマックス値を超えていないなら
			if (E_num <= e_spawn->GetMaxEnemy()) {
				E_num = E_num + 1;
			}
		}
	}

	// 敵の更新と当たり判定チェック
	for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++)
	{
		// 値がnullでないなら
		if (enemy[i] != nullptr) 
		{
			enemy[i]->Update(player->GetSpeed());

			// 画面外に行ったら、敵を消去してスコア加算
			if (enemy[i]->GetLocation().y >= 640.0f) 
			{
				enemy_count[enemy[i]->GetType()]++;
				enemy[i]->Finalize();
				delete enemy[i];	// メモリ開放
				enemy[i] = nullptr;// nullにする
			}

			//当たり判定の確認
			if (IsHitCheck(player, enemy[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}
	
	// プレイヤーの燃料か体力が０未満なら、リザルトに遷移する
	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	// 背景画像の描画
	//DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	//DrawGraph(0, mileage % 480, back_ground, TRUE);
	
	// 敵の描画 csvにある敵の数以下なら
	for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] != nullptr) {
			bullet[i]->Draw();
		}

	}

	// プレイヤーの描画
	player->Draw();

	// UIの描画
	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(16);
	DrawFormatString(510, 20, GetColor(0, 0, 0), "ハイスコア");
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
	DrawFormatString(510, 80, GetColor(0, 0, 0), "避けた数");

	for (int i = 0; i < 3; i++) 
	{
		DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
		DrawFormatString(510 + (i*50),140,GetColor(255, 255, 255), "%03d",enemy_count[i]);
	}

	DrawFormatString(510, 200, GetColor(0, 0, 0), "走行距離");
	DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d", mileage / 10);
	DrawFormatString(510, 240, GetColor(0, 0, 0), "スピード");
	DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f",player->GetSpeed());

	// バリア枚数描画
	for (int i = 0; i < player->GetBarriarCount(); i++)
	{
		DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	}

	// 燃料ゲージの描画
	float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy +
		40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
	// 体力ゲージの描画
	fx = 510.0f;
	fy = 430.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy +
		40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}

void GameMainScene::Finalize()
{
	// スコア加算する
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	// リザルトデータの書き込み
	FILE* fp = nullptr;
	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが開けません\n");
	}
	// スコアを保存
	fprintf(fp, "%d,\n", score);

	// 避けた数と得点を保存
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	// ファイルクローズ
	fclose(fp);

	// 動的確保したオブジェクトを消去する
	player->Finalize();
	delete player;

	for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
	delete[] enemy;
	//弾の消去
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Finalize();
			delete bullet[i];
			bullet[i] = nullptr;
		}
	}
	delete[] bullet;
}

// 現在のシーン情報取得
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

// ハイスコア読込
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}

// あたり判定処理（プレイヤーと敵）
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	// プレイヤーがバリアを張っていたら当たり判定無し
	if (p->IsBarrier()) {
		return false;
	}

	// 敵情報がなければ、当たり判定を無視する
	if (e == nullptr) {
		return false;
	}

	// 位置情報の差分取得
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	// 当たり判定サイズの大きさを取得
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
	// コリジョンデータより位置情報の差分が小さいなら、ヒット判定
	return ((fabs(diff_location.x)<box_ex.x)&&(fabsf(diff_location.y)<box_ex.y));
}

bool GameMainScene::SpawnBullet()
{
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] == nullptr)
		{
			bullet[i] = new Bullet();
			//弾のベクトルとか座標とかを引数として渡す
			bullet[i]->Initialize(player->GetAim(), player->GetLocation(), 5.0f, 10, 1, 1);

			return true;
		}
	}
	return false;
}

void GameMainScene::BulletManager()
{
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] != nullptr)
		{
			//弾を発射したのがプレイヤーだったら
			if (bullet[i]->GetType() == 0)	
			{
				for (int j = 0; j < 10; j++)//敵の最大数
				{
					//敵と弾の当たり判定　弾の座標、半径と敵の座標、半径を引数とする
					//CheckCollision(bullet[i]->GetLocation(),bullet[i]->GetRadius(),)
				}
			}
			//弾を発射したのがエネミーだったら
			else if (bullet[i]->GetType() == 1)	
			{
				//プレイヤーと弾の当たり判定　弾の座標、半径とプレイヤーの座標、半径を引数とする
				//CheckCollision(bullet[i]->GetLocation(),bullet[i]->GetRadius(),)	
			}

			//弾が範囲外に行った時の処理
			if (bullet[i]->GetLocation().x < 0 || bullet[i]->GetLocation().x > 1280 ||
				bullet[i]->GetLocation().y < 0 || bullet[i]->GetLocation().y > 720)
			{
				bullet[i] = nullptr;
			}
		}
	}
}
