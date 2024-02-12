#pragma once
#include "../Utility/Vector2D.h"

class Bullet
{
private:
	Vector2D vec;
	float radius;

private:
	Bullet(); //�R���X�g���N�^
	~Bullet(); //�f�X�g���N�^

	void Initialize(); //����������
	void Update(); //�X�V����
	void Draw();//�`�揈��
	void Finalize();//�I������

};

