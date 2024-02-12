#pragma once
#include "SceneBase.h"

#include "../Object/Player.h" /*../Object/Player.h*/
#include "../Object/Enemy.h"  /*../Object/Enemy.h*/
#include "../Object/Bullet.h"
#include "../Enemy_Spawn.h"

#define MAX_BULLET_NUM 256

class GameMainScene:public SceneBase
{
private:
	int high_score;			// �n�C�X�R�A
	int back_ground;		// �w�i�摜
	int barrier_image;		// �o���A�摜
	int mileage;			// ���s����
	int enemy_image[3];		// �G�摜
	int enemy_count[3];		// �ʂ�߂����G�̃J�E���g
	int E_num;
	int e_spownCnt;

	Player* player;			// �v���C���[
	 Enemy** enemy;			// �G
	Bullet** bullet;

	E_Spawn* e_spawn;
public:
	GameMainScene();
	~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	// �n�C�X�R�A�Ǎ�����
	void ReadHighScore();
	// �����蔻��
	bool IsHitCheck(Player* p, Enemy* e);

public:	//�e�֌W����
	bool SpawnBullet();
	void BulletManager();
};

