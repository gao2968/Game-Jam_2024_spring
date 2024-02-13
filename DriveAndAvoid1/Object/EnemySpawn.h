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

class E_Spawn
{
private:

	static E_NUM data[63];			// �G�̐��̍ő吔
	static int row;						// csv�t�@�C���̗�̐�(�ǂݍ��܂��G�̗�)

public:
	E_Spawn();						// �R���X�g���N�^
	~E_Spawn();						// �f�X�g���N�^
	static E_NUM LoadEnemy(int i);		// �G���̓ǂݍ���
	static int GetMaxEnemy();			// �ǂݍ��܂ꂽ�G�̗ʂ̎擾
};
