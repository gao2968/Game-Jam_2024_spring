#include "E_Spawn.h"
#include "DxLib.h"

// 配列情報を持った敵
E_NUM EnemySpawn::data[63];
int EnemySpawn::row;

// コンストラクタ
EnemySpawn::EnemySpawn()
{
	int fp;
	char buf[100];	// 文字列読み取り用
	char c;			// 文字をひとつづつたどっていくための変数
	int col = 1;	// csvファイルの列
	row = 0;		// csvファイルの行
	int count = 0;	// 文字列を作るために1文字づつずらしていく

	// 配列内のすべてを0で埋める
	memset(buf, 0, sizeof(buf));

	// ファイルのロード
	if (fp = FileRead_open("Resource/dat/Enemys_Data.csv"));


	// 1行目を無視する ファイルから１文字取得するための変数
	while (FileRead_getc(fp) != '\n');

	// データの読み込み このwhile２つは無限ループ
	while (true) {
		while (true) {

			// ファイルの1文字を取得を繰り返し、文字列にする
			c = FileRead_getc(fp);
			buf[count] = c;

			// カンマ、改行、EOFならループを抜ける
			if (c == ',' || c == '\n' || c == EOF) {
				buf[count] = '\0';
				break;
			}
			count++;
		}

		// 列の位置で数値を入れる
		// atoiは型を変更してくれる関数
		// floatならfloatに、intならintにしてくれる

		switch (col) {

			// X座標
		case 1:

			data[row].location_x = atoi(buf);
			break;

			// Y座標
		case 2:
			data[row].location_y = atoi(buf);
			break;

			// 半径
		case 3:
			data[row].radius = atoi(buf);
			break;

			// 敵スピード
		case 4:
			data[row].speed = atoi(buf);
			break;

			// 弾のスピード
		case 5:
			data[row].bullet_speed = atoi(buf);
			break;

			// スコア
		case 6:
			data[row].score = atoi(buf);
			break;

			// HP
		case 7:
			data[row].hp = atoi(buf);
			break;

			// 出現時間
		case 8:
			data[row].time = atoi(buf);
			break;
		}
		// 文字列を作る	bufをまた0で埋めておく
		memset(buf, 0, sizeof(buf));

		// EOFならoutに飛ぶ
		// EOFがない限り永遠にループする
		if (c == EOF) {
			goto out;
		}

		// EOF通らなかったなら読み込む位置を初期化して次の列を読む
		count = 0;
		col++;

		// 改行なら次の行に行く
		if (c == '\n') {
			col = 1;
			++row;
		}
		// またループの一番初めに戻る
	}
	// 唯一のループ出口はここ
out:
	FileRead_close(fp);
}


EnemySpawn::~EnemySpawn()
{

}

// 敵情報の読み込み
E_NUM EnemySpawn::LoadEnemy(int i)
{
	return data[i];
}

// 読み込まれた敵の量の取得
int EnemySpawn::GetMaxEnemy()
{
	// 行数を返すことで判断できる
	return row;
}

