#pragma once
#include "../Utility/Vector2D.h"

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

private:
	// csv�t�@�C���ǂݍ��݂Ŏg���ϐ�
	int E_num;
	int point;
	bool hit;
	int color;
	int WaitTime;

	int Type;

	/*float Set_PlocationX;
	float Set_PlocationY;*/

	int radius;			// �~�̑傫��
public:

	// csv����擾����p�̃R���X�g���N�^
	Enemy(float _x, float _y, float _r, float _speed, float b_speed, int score, int hp, int E_num, int type, int handle);
	~Enemy();

	void Initialize();			// �����������p
	void Update(float speed);	// �X�V����
	void Draw()const;			// �`�揈��
	void Finalize();			// �I�����̏���

	int GetType()const;			// �^�C�v�̎擾
	Vector2D GetLocation();		// �ʒu���̎擾
	Vector2D GetBoxSize();		// �����蔻��̑傫�����擾
};

