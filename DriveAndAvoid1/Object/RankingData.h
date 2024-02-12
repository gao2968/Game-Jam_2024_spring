#pragma once
class RankingData
{
public:
	RankingData();
	~RankingData();

	void Initialize(); //初期処理
	void Finalize(); //終了処理

public:
	//ランキングデータの作成
	void SetRankingData(int score, const char* name);
	//スコア取得処理
	int GetScore(int value) const;
	//スコア取得処理
	int GetRank(int value) const;
	//名前取得処理
	const char* GetName(int value) const;

private:
	int score[6];
	int rank[6];
	char name[6][15];

private:
	//データ入れ替え処理
	void SortData();

};