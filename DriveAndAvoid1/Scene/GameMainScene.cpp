#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>
#include "../Utility/Collision.h"
#include"../Utility/InputControl.h"
#include "../Utility/TakePicture.h"
#include "../Resource/FontManager.h"
#include "../Object/RankingData.h"

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), barrier_image(NULL), Score(0), player(nullptr),
enemy(nullptr) {
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}

	enemy_image_num = 0;
	backgroundX = 0;
	backgroundY = 0;
	coolTime = 0;
	fps = 0;
	stopFlg = false;
	state = 0;
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
	img_Background = LoadGraph("Resource/images/background.jpg");


	TakePicture tmp;
	std::string path;
	tmp.SeekNum();
	for (int i = 0; i < tmp.GetNum(); i++)
	{
		path = "Resource/images/img" + std::to_string(i) + ".png";
		enemy_image[i] = LoadGraph(path.c_str());
		if (enemy_image[i] != -1) {
			enemy_image_num++;
		}
	}

	enemy_headImages[0] = LoadGraph("Resource/images/mob.png");
	enemy_headImages[1] = LoadGraph("Resource/images/mob2.png");
	boss_headimage = LoadGraph("Resource/images/ボス.png");

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
	Boss_Num = e_spawn->GetMaxEnemy();

	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet[i] = nullptr;
	}
}

eSceneType GameMainScene::Update()
{
	if (stopFlg == false) {
		// プレイヤーの更新
		player->Update();
		// 敵生成処理
		spawn_Enemys();

		// 敵の更新と当たり判定チェック
		for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++)
		{
			// 値がnullでないなら
			if (enemy[i] != nullptr)
			{
				enemy[i]->Update(player->GetSpeed(), this, player->GetLocation());

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
					player->DecreaseHp(50.0f);
					enemy[i]->Finalize();
					delete enemy[i];
					enemy[i] = nullptr;
				}
			}
			// HPが0なら
			if (enemy[i] != nullptr)
			{
				if (enemy[i]->Get_HP() <= 0)
				{
					enemy[i]->Voic();
					Score += enemy[i]->Get_Score();
					enemy[i]->Finalize();
					delete enemy[i];
					enemy[i] = nullptr;
				}
			}
		}

		if (InputControl::GetButton(XINPUT_BUTTON_RIGHT_SHOULDER) && coolTime > 10) {
			SpawnBullet();
			coolTime = 0;
		}

		// Enemy_SpawnBullet();

		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			if (bullet[i] != nullptr) {
				bullet[i]->Update();
			}

		}
		BulletManager();
	}
			// 任意の敵を倒したならリザルトへ（今は最後に出てくる敵）
	if (enemy[Boss_Num] != nullptr) {
		if (enemy[Boss_Num]->Get_HP() <= 0) {
			// ↓何故かここに書かないとボスの処理が反映されない

			static int a = 0;	// stop中のループで処理が連続するのを防ぐ用
			if (a == 0) { 
			enemy[Boss_Num]->Voic(); 
			Score += enemy[Boss_Num]->Get_Score();
			a++;
			}
			stopFlg = true;
			state = 2;
			if (fps++ > 240) {
				return eSceneType::E_RULE;
			}
		}
	}

	if (player->GetHp() < 0.0f)
	{
		stopFlg = true;
		state = 1;
		if (fps++ > 240) {
			return eSceneType::E_RULE;
		}
	}
	
	//背景
	backgroundX -= SCROLL_SPEED;
	if (backgroundX <= -2048) {
		backgroundX = 0;
	}

	
	if (coolTime++ > 10) {
		coolTime = 10;
	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	// 背景画像の描画
	//DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	//DrawGraph(0, mileage % 480, back_ground, TRUE);
	DrawGraph(backgroundX, backgroundY, img_Background, FALSE);
	DrawGraph(backgroundX + 2048, backgroundY, img_Background, FALSE);
	
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

	//DrawBox(1000, 0, 1280, 720, GetColor(0, 153, 0), TRUE);
	float fx = 30.0f;
	float fy = 30.0f;
	//DrawFormatStringF(fx, fy, GetColor(255, 255, 255), "PLAYER HP");
	//DrawOval(230, 95 , 230, 25, GetColor(255, 255, 255), TRUE);
	DrawStringToHandle(fx, fy, "PLAYER HP", GetColor(255, 255, 255), FontManager::GetFont(1));
	int tmp;
	tmp = player->GetHp();
	if (tmp < 0) {
		tmp = 0;
	}
	DrawBoxAA(fx, fy + 50.0f, fx + (tmp * 400 / 1000), fy +
		80.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 50.0f, fx + 400.0f, fy + 80.0f, GetColor(255, 255, 255), FALSE);

	// ボスの体力表示
	if (enemy[Boss_Num] != nullptr) {
		float Efx = 850.0f;
		float Efy = 600.0f;
		DrawStringToHandle(Efx, Efy, "BOSS_HP", GetColor(255, 255, 255), FontManager::GetFont(1));
		DrawBoxAA(Efx, Efy + 50.0f, Efx + (enemy[Boss_Num]->Get_HP() * 400 / e_spawn->LoadEnemy(Boss_Num).hp), Efy +
			80.0f, GetColor(255, 0, 0), TRUE);
		DrawBoxAA(Efx, Efy + 50.0f, Efx + 400.0f, Efy + 80.0f, GetColor(255, 255, 255), FALSE);
	}


	//DrawFormatString(510, 30, GetColor(255, 255, 255), "SCORE (仮)");
	DrawStringToHandle(550, 30, "SCORE", GetColor(255, 255, 255), FontManager::GetFont(1));
	//DrawFormatString(555, 60, GetColor(255, 255, 255), "%08d", mileage / 10);
	DrawFormatStringToHandle(550, 90, GetColor(255, 255, 255), FontManager::GetFont(2), "%d", Score);

	DrawStringToHandle(1000, 30, "1ST SCORE", GetColor(255, 255, 255), FontManager::GetFont(1));
	DrawFormatStringToHandle(1000, 90, GetColor(255, 255, 255), FontManager::GetFont(2), "%d", RankingData::GetScore(0));


	if (state == 1) {
		DrawStringToHandle(150, 300, "GAME OVER", GetColor(255, 255, 255), FontManager::GetFont(4));
	}
	else if (state == 2) {
		DrawStringToHandle(140, 300, "GAME CLEAR", GetColor(255, 255, 255), FontManager::GetFont(4));
	}
}

void GameMainScene::Finalize()
{
	// スコア加算する
	int score = (Score / 10 * 10);
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
		/*if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}*/
		delete enemy[i];
	}
	//delete[] enemy;
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
	//RankingData data;
	//data.Initialize();

	//high_score = data.GetScore(0);

	//data.Finalize();

	high_score = RankingData::GetScore(0);
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
			bullet[i]->Initialize(player->GetAim(), player->GetLocation(), 5.0f, 10, 10, 0);

			return true;
		}
	}
	return false;
}


// ゲームメインにあるが、処理として使っているのはエネミー側
bool GameMainScene::Enemy_SpawnBullet(Vector2D e_vec,Vector2D e_location,float speed,float damage)
{
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] == nullptr)
		{
			bullet[i] = new Bullet();
			//弾のベクトルとか座標とかを引数として渡す
			bullet[i]->Initialize(e_vec, e_location, speed, 10,damage, 1);

			return true;
		}
	}
	return false;
}

void GameMainScene::BulletManager()
{
	
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bool hit = false;
		if (bullet[i] != nullptr)
		{
			//弾を発射したのがプレイヤーだったら
			if (bullet[i]->GetType() == 0)	
			{
				for (int j = 0; j <= e_spawn->GetMaxEnemy(); j++)//敵の最大数
				{
					if (enemy[j] != nullptr) {
						//敵と弾の当たり判定　弾の座標、半径と敵の座標、半径を引数とする
						if (CheckCollision(bullet[i]->GetLocation(), bullet[i]->GetRadius(), enemy[j]->GetLocation(),enemy[j]->Get_Radius()))
						{
							hit = true;
							enemy[j]->Set_HP(bullet[i]->GetDamage());
						}
					}
				}
			}
			//弾を発射したのがエネミーだったら
			else if (bullet[i]->GetType() == 1)	
			{
				//プレイヤーと弾の当たり判定　弾の座標、半径とプレイヤーの座標、半径を引数とする
				if(CheckCollision(bullet[i]->GetLocation(), bullet[i]->GetRadius(), player->GetLocation(), player->GetRadius()))
				{
					hit = true;
					player->DecreaseHp(bullet[i]->GetDamage());
				}
			}

			//弾が範囲外に行った時の処理
			if (bullet[i]->GetLocation().x < 0 || bullet[i]->GetLocation().x > 1280 ||
				bullet[i]->GetLocation().y < 0 || bullet[i]->GetLocation().y > 720)
			{
				bullet[i] = nullptr;
			}
			if (hit == true) {
				bullet[i] = nullptr;
			}
		}
	}
}

void GameMainScene::spawn_Enemys()
{
	int image = 0;
	int img_num = 0;	

	if (E_num != Boss_Num) {
		img_num = GetRand(1);
		image = enemy_headImages[img_num];
	}else {
		image = boss_headimage;
		img_num = 2;
	}

	if (enemy[E_num] == nullptr) {
		// エネミーの出現時間に到達したら
		if (++e_spownCnt > e_spawn->LoadEnemy(E_num).time * 60) {

			//出現したエネミーの情報を全て送信
			enemy[E_num] = new Enemy(
				e_spawn->LoadEnemy(E_num).location_x		// X座標取得
				, e_spawn->LoadEnemy(E_num).location_y		// Y座標取得
				, e_spawn->LoadEnemy(E_num).radius			// 半径取得
				, e_spawn->LoadEnemy(E_num).speed			// スピード取得
				, e_spawn->LoadEnemy(E_num).bullet_speed		// 球のスピード取得
				, e_spawn->LoadEnemy(E_num).score			// 撃破時のスコア数取得
				, e_spawn->LoadEnemy(E_num).hp				// HP取得
				, E_num										// 今何体目なのか
				, 1											// エネミーのタイプ（消すかも）
				, enemy_image[GetRand(enemy_image_num - 1)]								// エネミーの画像
				,image
				,img_num
			);
			// エネミーの数がマックス値を超えていないなら
			if (E_num <= e_spawn->GetMaxEnemy()) {
				E_num = E_num + 1;
			}
		}
	}
}
