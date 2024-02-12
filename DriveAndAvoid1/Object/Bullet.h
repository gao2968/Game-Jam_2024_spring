#pragma once
#include "../Utility/Vector2D.h"

class Bullet
{
private:
	Vector2D location;
	Vector2D vector;
	float speed;
	float radius;
	float damage;
	int type;
private:
	Bullet(); //�R���X�g���N�^
	~Bullet(); //�f�X�g���N�^

	void Initialize(Vector2D vec,Vector2D loc,); //����������
	void Update(); //�X�V����
	void Draw();//�`�揈��
	void Finalize();//�I������

};

