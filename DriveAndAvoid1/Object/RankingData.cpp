#include "RankingData.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>

int RankingData::score[];
int RankingData::rank[];
std::string RankingData::name[];

//初期化処理
void RankingData::Initialize()
{
	for (int i = 0; i < 6; i++)
	{
		score[i] = NULL;
		rank[i] = NULL;
		for (int j = 0; j < 15; j++)
		{
			name[i] = '\0';
		}
	}

	std::ifstream ifs("Resource/dat/ranking_data.csv");
	std::string line;
	//ランキングテキストの一行を取得
	for (int i = 0; std::getline(ifs, line); i++) {
		std::istringstream stream(line);
		std::string str;
		//no name scoreに分けて格納
		for (int j = 0; std::getline(stream, str, ','); j++) {
			if (j == 0) {
				score[i] = std::stoi(str);
			}
			else if (j == 1) {
				rank[i] = std::stoi(str);
			}
			else {
				name[i] = str;
			}
		}
	}

	ifs.close();
	//末尾データの設定
	score[5] = 0;
	rank[5] = 0;
	name[5] = '\0';

}

//終了処理
void RankingData::Finalize()
{
	
}

//データ設定処理
void RankingData::SetRankingData(int s, const char* n)
{
	score[5] = s;
	std::string tmp(n);
	name[5] = tmp;

	SortData();
}

//スコア処理取得
int RankingData::GetScore(int value)
{
	return score[value];
}

//ランク取得処理
int RankingData::GetRank(int value)
{
	return rank[value];
}

//名前取得処理
const char* RankingData::GetName(int value)
{
	return name[value].c_str();
}

//データ入れ替え処理
void RankingData::SortData()
{
	//選択法ソートを使用し、降順で入れ替える
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (score[i] <= score[j])
			{
				int tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;

				/*char buf[15] = {};
				strcpy_s(buf, name[i]);
				strcpy_s(name[i], name[j]);
				strcpy_s(name[j],buf);*/

				std::string buf1;
				buf1 = name[i];
				name[i] = name[j];
				name[j] = buf1;

			}
		}
	}
	//順位を整列させる
	for (int i = 0; i < 5; i++)
	{
		rank[i] = 1;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (score[i] > score[j])
			{
				rank[j]++;
			}
		}
	}
	//ランキングデータの読み込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.csvが開けませんでした\n");
	}

	//対象ファイルに書き込み
	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%d,%d,%s,\n", score[i], rank[i], name[i].c_str());
	}

	//ファイルクローズ
	fclose(fp);
}
//#include "RankingData.h"
//#include <fstream>
//#include <iostream>
//#include <sstream>
//
//RankingData::RANKING RankingData::rankingData[];
//
//void RankingData::ReadRanking()
//{
//	//ランキングテキストの読込
//	std::ifstream ifs("text/Ranking.txt");
//
//	std::string line;
//	//ランキングテキストの一行を取得
//	for (int i = 0; std::getline(ifs, line); i++) {
//		std::istringstream stream(line);
//		std::string str;
//		//no name scoreに分けて格納
//		for (int j = 0; std::getline(stream, str, ','); j++) {
//			if (j == 0) {
//				rankingData[i].no = std::stoi(str);
//			}
//			else if (j == 1) {
//				rankingData[i].name = str;
//			}
//			else {
//				rankingData[i].score = std::stoi(str);
//			}
//		}
//	}
//}
//
//void RankingData::WriteRanking(std::string n, int s)
//{
//	RANKING tmp;		//入れ替えの時に使う
//	std::ofstream ofs("text/Ranking.txt");		//ランキングテキストの読込
//
//	//ランキングデータの最下位に引数を代入
//	rankingData[4].name = n;
//	rankingData[4].score = s;
//	//並べ替え
//	for (int i = 0; i < 4; i++) {
//		for (int j = i + 1; j < 5; j++) {
//			if (rankingData[i].score < rankingData[j].score) {
//				tmp = rankingData[i];
//				rankingData[i] = rankingData[j];
//				rankingData[j] = tmp;
//			}
//		}
//	}
//
//	//順位の再振り分け
//	rankingData[0].no = 1;
//	for (int i = 1; i < 5; i++) {
//		//同じ点数だったら同じ順位
//		if (rankingData[i].score == rankingData[i - 1].score) {
//			rankingData[i].no = rankingData[i - 1].no;
//		}
//		//同じ順位じゃなければ一つ多い順位
//		else {
//			rankingData[i].no = i + 1;
//		}
//	}
//
//	//ランキングテキストに書き込み
//	for (int i = 0; i < 5; i++) {
//		ofs << rankingData[i].no << "," << rankingData[i].name << "," << rankingData[i].score << std::endl;
//	}
//
//}
