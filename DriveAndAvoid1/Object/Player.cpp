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

//初期化処理
void Player::Initialize()
{
    yuusya = LoadGraph("Resource/images/6 (1).png");
	is_active = true;
	location = Vector2D(100.0f, 360.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 6.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;
	radius = 50.0f;

	//画像の読み込み
	TakePicture p;
	p.SeekNum();
	std::string path;
	path = "Resource/images/img" + std::to_string(p.GetNum()) + ".png";
	//image = LoadGraph("Resource/images/car1pol.bmp");
	image = LoadGraph(path.c_str());
	aimingImg = LoadGraph("Resource/images/aiming.png");
	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/car1pol.bmpがありません。\n");
	}
}

//更新処理
void Player::Update()
{
	AimLocation.x = location.x + InputControl::GetRightStick().x * 200;
	AimLocation.y = location.y + InputControl::GetRightStick().y * -200;
	
	//操作不可状態であれば、自身を回転させる
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 6.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	//燃料の消費
	//fuel -= speed;

	//移動処理
	Movement();

	//加速処理
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//バリア処理
	/*if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}*/

	//バリアが生成ささていたら、更新を行う
	if (barrier != nullptr)
	{
		//バリア時間が経過した？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//描画処理
void Player::Draw()
{
	DrawCircle(AimLocation.x, AimLocation.y, 3, 0xff0000, true);
	DrawRotaGraph(AimLocation.x, AimLocation.y, 0.1, DX_PI / 2.0, aimingImg, TRUE);
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	DrawRotaGraphF(location.x, location.y+57, 2.0f, angle, yuusya, TRUE);


	//DrawCircle(location.x, location.y, radius, 0xffff00, false);

	//バリアが生成されていたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}

//終了処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp -= value;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//当たり判定の大きさの取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}
//速さ取得処理
float Player::GetSpeed() const
{
	return this->speed;
}
//燃料取得処理
float Player::GetFuel() const
{
	return this->fuel;
}
//体力取得処理
float Player::GetHp() const
{
	return this->hp;
}
//バリア枚数取得処理
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}
//バリアは有効か？を取得
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

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;
	//十字移動処理
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

	// 左スティック入力値の更新（に範囲を制限する）
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

	

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 1000.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 720.0f - box_size.y))
	{
		location -= move;
	}
}

//加減速処理
void Player::Acceleration()
{
	//LBボタンが押されたら、減速する
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	//{
	//	speed -= 1.0f;
	//}
	////RBボタンが押されたら、加速する
	//if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	//{
	//	speed += 1.0f;
	//}
}