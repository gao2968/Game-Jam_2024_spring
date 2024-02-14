#pragma once
#include "SceneBase.h"

#include "../Object/Player.h" /*../Object/Player.h*/
#include "../Object/Enemy.h"  /*../Object/Enemy.h*/
#include "../Object/Bullet.h"
#include "../Object/EnemySpawn.h"

#define MAX_BULLET_NUM 256
#define SCROLL_SPEED 5

class GameMainScene:public SceneBase
{
private:
	int high_score;			// �n�C�X�R�A
	int back_ground;		// �w�i�摜
	int barrier_image;		// �o���A�摜
	int Score;			// ���s����
	int enemy_image[10];	// �G�摜
	int enemy_image_num;	// �G�̉摜����
	int enemy_count[3];		// �ʂ�߂����G�̃J�E���g
	int E_num;
	int e_spownCnt;
	int Boss_Num;
	Player* player;			// �v���C���[
	 Enemy** enemy;			// �G
	Bullet** bullet;

	E_Spawn* e_spawn;

	int backgroundX;
	int backgroundY;
	int img_Background;

	int coolTime;
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
	bool Enemy_SpawnBullet(Vector2D e_vec, Vector2D e_location,float speed, float damage);
	void BulletManager();

private:	// �G�̏����֐�
	void spawn_Enemys();			// �G�̃X�|�[������
};

