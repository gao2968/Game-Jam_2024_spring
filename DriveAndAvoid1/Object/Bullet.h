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
	int type;  //0�v���C���[�@1�G
public:
	Bullet(); //�R���X�g���N�^
	~Bullet(); //�f�X�g���N�^

	void Initialize(Vector2D vec, Vector2D loc, float s, float r, float d, int t); //����������
	void Update(); //�X�V����
	void Draw();//�`�揈��
	void Finalize();//�I������


	Vector2D GetVector() { return vector; }
	Vector2D GetLocation() { return location; }
	float GetSpeed() { return speed; }
	float GetRadius() { return radius; }
	float GetDamage() { return damage; }
	int GetType() { return type; }
};

