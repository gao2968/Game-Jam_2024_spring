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
	int head_images;

	float speed;		// ����
	int hp;				// �̗�
	float bullet_speed; // ���̑���

	Vector2D location;	// �ʒu���
	Vector2D box_size;	// �����蔻��̑傫��
	Vector2D b_vector[3];	// ��΂������w��p

	Bullet** e_bullet;

private:// csv�t�@�C���ǂݍ��݂Ŏg���ϐ�
	int E_num;
	int point;
	bool hit;
	int color;
	int WaitTime;
	int Type;
	int radius;			// �~�̑傫��
	int image_num;		// �G�摜�̔ԍ���F������ׂ̕ϐ�
private:

	int LateTime;		// ���̔��ˑ��x���Ǘ�����ׂ̕ϐ�
	int bullet_Timing;	// �e�̊��o���ԁi���[�g�̐ݒ�.��X�G�N�Z���ŊǗ�����j 
	bool hanten;		// �ړ����������]����^�C�~���O������ϐ�
	bool End;			// �{�X��|��������

	float y_speed;		// �{�X��Y���W�ړ�����X�s�[�h
public:

	// �P.x���W�@�Q.Y���W�@�R.���a�@�S.�X�s�[�h�@�T.�e�̃X�s�[�h�@�U.�|�������̃X�R�A���@�V.HP�@�W.���Ԗڂ̓G������p�@�X.�摜�n���h��
	Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int hp, int E_num, int type, int handle,int hed_handle,int img_num);
	~Enemy();

	void Initialize();			// �����������p
	void Update(float speed, GameMainScene* game, Vector2D player);// �X�V����
	void Draw()const;			// �`�揈��
	void Finalize();			// �I�����̏���

	int GetType()const;			// �^�C�v�̎擾
	Vector2D GetLocation();		// �ʒu���̎擾
	Vector2D GetBoxSize();		// �����蔻��̑傫�����擾

	int Get_Radius();
	float Get_HP();
	bool Get_BossDown();		// �{�X�̎��S��������
	int Get_Score();			// �X�R�A���擾����

	void Set_HP(float damege);				// HP�Z�b�g

private:
	void Boss_System(GameMainScene* game, Vector2D player);		// �{�X�̍s���p�^�[��
};