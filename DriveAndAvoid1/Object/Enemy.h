#pragma once

class GameMainScene;// ���O���������Ă���

#include "../Utility/Vector2D.h"
#include"../Object/Bullet.h"
#define E_BULLET_MAX 256

class Enemy
{
private:
	int type;			// �^�C�v
	int image;			// �摜
	float speed;		// ����
	int hp;				// �̗�
	float bullet_speed; // ���̑���

	Vector2D location;	// �ʒu���
	Vector2D box_size;	// �����蔻��̑傫��
	Vector2D a;

	Bullet** e_bullet;

private:
	// csv�t�@�C���ǂݍ��݂Ŏg���ϐ�
	int E_num;
	int point;
	bool hit;
	int color;
	int WaitTime;
	int Type;
	int radius;			// �~�̑傫��

private:
	int LateTime;		// ���̔��ˑ��x���Ǘ�����ׂ̕ϐ�
	int bullet_Timing;	// �e�̊��o���ԁi���[�g�̐ݒ�.��X�G�N�Z���ŊǗ�����j 
	bool shot;
public:

	// csv����擾����p�̃R���X�g���N�^
	Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int hp, int E_num, int type, int handle);
	~Enemy();

	void Initialize();			// �����������p
	void Update(float speed,GameMainScene *game);	// �X�V����
	void Draw()const;			// �`�揈��
	void Finalize();			// �I�����̏���

	int GetType()const;			// �^�C�v�̎擾
	Vector2D GetLocation();		// �ʒu���̎擾
	Vector2D GetBoxSize();		// �����蔻��̑傫�����擾

	int Get_Radius();
	bool firing();				// ���[�g������؂ꂽ�^�C�~���O��true��Ԃ�
};

