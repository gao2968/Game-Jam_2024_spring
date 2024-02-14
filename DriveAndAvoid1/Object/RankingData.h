#pragma once
#include <string>
class RankingData
{
public:
	static void Initialize(); //初期処理
	static void Finalize(); //終了処理

public:
	//ランキングデータの作成
	static void SetRankingData(int s, const char* n);
	//スコア取得処理
	static int GetScore(int value);
	//スコア取得処理
	static int GetRank(int value);
	//名前取得処理
	static const char* GetName(int value);

private:
	static int score[6];
	static int rank[6];
	static std::string name[6];

private:
	//データ入れ替え処理
	static void SortData();

};
//#pragma once
//#include <string>
//class RankingData
//{
//public:
//	ランキング構造体
//	struct RANKING
//	{
//		int no;					//順位
//		std::string name;		//名前
//		int score;				//スコア
//	};
//
//private:
//	static RANKING rankingData[5];		//ランキングデータ格納用
//
//public:
//	ランキングの読込
//	static void ReadRanking();
//	ランキングの書き込み用
//	引数：n 名前　s スコア
//	static void WriteRanking(std::string n, int s);
//
//	ランキングデータの取得
//	引数：num　取得したいデータの番号
//	戻り値：numで指定された番号のrankingDataを返却
//	static RANKING GetRankingData(int num)
//	{
//		return rankingData[num];
//	}
//};

