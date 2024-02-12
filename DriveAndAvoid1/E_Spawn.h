#pragma once

#pragma once

struct E_NUM
{
	float location_x;
	float location_y;
	float radius;
	float speed;
	float bullet_speed;
	int score;
	int hp;
	int time;
};

class EnemySpawn
{
private:

	static E_NUM data[63];			// 敵の数の最大数
	static int row;						// csvファイルの列の数(読み込まれる敵の量)

public:
	EnemySpawn();						// コンストラクタ
	~EnemySpawn();						// デストラクタ
	static E_NUM LoadEnemy(int i);		// 敵情報の読み込み
	static int GetMaxEnemy();			// 読み込まれた敵の量の取得
};


