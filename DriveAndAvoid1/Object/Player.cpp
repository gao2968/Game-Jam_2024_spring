#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Utility/TakePicture.h"

Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0),radius(0.0f),

barrier(nullptr)
{
	
}
Player::~Player()
{

}

//����������
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(100.0f, 360.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 6.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;
	radius = 50.0f;

	//�摜�̓ǂݍ���
	TakePicture p;
	p.SeekNum();
	std::string path;
	path = "Resource/images/img" + std::to_string(p.GetNum()) + ".png";
	//image = LoadGraph("Resource/images/car1pol.bmp");
	image = LoadGraph(path.c_str());

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmp������܂���B\n");
	}
}

//�X�V����
void Player::Update()
{
	AimLocation.x = location.x + InputControl::GetRightStick().x * 200;
	AimLocation.y = location.y + InputControl::GetRightStick().y * -200;
	
	//����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	//�R���̏���
	fuel -= speed;

	//�ړ�����
	Movement();

	//��������
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//�o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//�o���A�����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//�o���A���Ԃ��o�߂����H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//�`�揈��
void Player::Draw()
{
	DrawCircle(AimLocation.x, AimLocation.y, 3, 0xffff00, true);
	
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);

	//DrawCircle(location.x, location.y, radius, 0xffff00, false);

	//�o���A����������Ă�����A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}

//�I������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�����蔻��̑傫���̎擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}
//�����擾����
float Player::GetSpeed() const
{
	return this->speed;
}
//�R���擾����
float Player::GetFuel() const
{
	return this->fuel;
}
//�̗͎擾����
float Player::GetHp() const
{
	return this->hp;
}
//�o���A�����擾����
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}
//�o���A�͗L�����H���擾
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

Vector2D Player::GetAim() 
{
	return AimLocation - location;
}

float Player::GetRadius()
{
	return radius;
}

//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;
	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 5.0f);
		angle = -DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -5.0f);
		angle = DX_PI_F / 18;
	}
	//location += move;

	// ���X�e�B�b�N���͒l�̍X�V�i�ɔ͈͂𐧌�����j
	if (InputControl::GetLeftStick().y < -0.3f)
	{
		move += Vector2D(0.0f, 5.0f);
		angle = DX_PI_F / 18;
	}
	if (InputControl::GetLeftStick().y > 0.3f)
	{
		move += Vector2D(0.0f, -5.0f);
		angle = -DX_PI_F / 18;
	}
	location += move;

	

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1000.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 720.0f - box_size.y))
	{
		location -= move;
	}
}

//����������
void Player::Acceleration()
{
	//LB�{�^���������ꂽ��A��������
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	//{
	//	speed -= 1.0f;
	//}
	////RB�{�^���������ꂽ��A��������
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	//{
	//	speed += 1.0f;
	//}
}