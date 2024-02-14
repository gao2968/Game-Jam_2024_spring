#include "GameMainScene.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>
#include "../Utility/Collision.h"
#include"../Utility/InputControl.h"
#include "../Utility/TakePicture.h"
#include "../Resource/FontManager.h"

GameMainScene::GameMainScene() :high_score(0), back_ground(NULL), barrier_image(NULL), mileage(0), player(nullptr),
enemy(nullptr) {
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}

	enemy_image_num = 0;
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Initialize()
{
	// �ō��_��ǂݍ���
	ReadHighScore();

	// �摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back.bmp");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, enemy_image);

	TakePicture tmp;
	std::string path;
	tmp.SeekNum();
	for (int i = 0; i < tmp.GetNum(); i++)
	{
		path = "Resource/images/img" + std::to_string(i) + ".png";
		enemy_image[i] = LoadGraph(path.c_str());
		if (enemy_image[i] != -1) {
			enemy_image_num++;
		}
	}

	// �G���[�`�F�b�N
	if (back_ground == -1) {
		throw("�摜back.bmp������܂���\n");
	}
	if (result == -1) {
		throw("�摜car.bmp������܂���\n");
	}
	if (barrier_image == -1) {
		throw("�摜barrier_image������܂���\n");
	}

	// �I�u�W�F�N�g�̐���
	player = new Player;

	// �R���X�g���N�^��csv�Ǎ����s��
	e_spawn = new E_Spawn();
	enemy = new Enemy * [e_spawn->GetMaxEnemy()]; E_num = 0;
	bullet = new Bullet * [MAX_BULLET_NUM];

	// �I�u�W�F�N�g�̏�����
	player->Initialize();

	for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++) {
		enemy[i] = nullptr;
	}
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bullet[i] = nullptr;
	}
}

eSceneType GameMainScene::Update()
{
	// �v���C���[�̍X�V
	player->Update();
	// �G��������
	spawn_Enemys();

	// �G�̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++)
	{
		// �l��null�łȂ��Ȃ�
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player->GetSpeed(),this,player->GetLocation());

			// ��ʊO�ɍs������A�G���������ăX�R�A���Z
			if (enemy[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[enemy[i]->GetType()]++;
				enemy[i]->Finalize();
				delete enemy[i];	// �������J��
				enemy[i] = nullptr;// null�ɂ���
			}

			//�����蔻��̊m�F
			if (IsHitCheck(player, enemy[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

	if (InputControl::GetButton(XINPUT_BUTTON_RIGHT_SHOULDER)) {
		SpawnBullet();
	}

		// Enemy_SpawnBullet();

	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] != nullptr) {
			bullet[i]->Update();
		}
		
	}
	BulletManager();

	// �ړ��ʋ����̍X�V player�X�s�[�h���擾����+�T�����l��mileage��+����i���t���[���j
	mileage += (int)player->GetSpeed() + 5;
	
	// �v���C���[�̔R�����̗͂��O�����Ȃ�A���U���g�ɑJ�ڂ���
	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}
	printfDx("%f\n", player->GetHp());

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	// �w�i�摜�̕`��
	//DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	//DrawGraph(0, mileage % 480, back_ground, TRUE);
	
	// �G�̕`�� csv�ɂ���G�̐��ȉ��Ȃ�
	for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] != nullptr) {
			bullet[i]->Draw();
		}

	}

	// �v���C���[�̕`��
	player->Draw();

	// UI�̕`��
	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	//SetFontSize(16);
	//DrawFormatString(510, 20, GetColor(0, 0, 0), "�n�C�X�R�A");
	//DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
	//DrawFormatString(510, 80, GetColor(0, 0, 0), "��������");

	//for (int i = 0; i < 3; i++) 
	//{
	//	DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
	//	DrawFormatString(510 + (i*50),140,GetColor(255, 255, 255), "%03d",enemy_count[i]);
	//}

	//DrawFormatString(510, 200, GetColor(0, 0, 0), "���s����");
	//DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d", mileage / 10);
	//DrawFormatString(510, 240, GetColor(0, 0, 0), "�X�s�[�h");
	//DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f",player->GetSpeed());

	//// �o���A�����`��
	//for (int i = 0; i < player->GetBarriarCount(); i++)
	//{
	//	DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	//}

	//// �R���Q�[�W�̕`��
	//float fx = 510.0f;
	//float fy = 390.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy +
	//	40.0f, GetColor(0, 102, 204), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
	//// �̗̓Q�[�W�̕`��
	//fx = 510.0f;
	//fy = 430.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy +
	//	40.0f, GetColor(255, 0, 0), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);


	//DrawBox(1000, 0, 1280, 720, GetColor(0, 153, 0), TRUE);
	float fx = 30.0f;
	float fy = 30.0f;
	//DrawFormatStringF(fx, fy, GetColor(255, 255, 255), "PLAYER HP");
	//DrawOval(230, 95 , 230, 25, GetColor(255, 255, 255), TRUE);
	DrawStringToHandle(fx, fy, "PLAYER HP", GetColor(255, 255, 255), FontManager::GetFont(1));
	DrawBoxAA(fx, fy + 50.0f, fx + (player->GetHp() * 400 / 1000), fy +
		80.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 50.0f, fx + 400.0f, fy + 80.0f, GetColor(255, 255, 255), FALSE);


	//DrawFormatString(510, 30, GetColor(255, 255, 255), "SCORE (��)");
	DrawStringToHandle(550, 30, "SCORE", GetColor(255, 255, 255), FontManager::GetFont(1));
	//DrawFormatString(555, 60, GetColor(255, 255, 255), "%08d", mileage / 10);
	DrawFormatStringToHandle(550, 90, GetColor(255, 255, 255), FontManager::GetFont(2), "%d", mileage / 10);
}

void GameMainScene::Finalize()
{
	// �X�R�A���Z����
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}

	// ���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	// �t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���J���܂���\n");
	}
	// �X�R�A��ۑ�
	fprintf(fp, "%d,\n", score);

	// ���������Ɠ��_��ۑ�
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	// ���I�m�ۂ����I�u�W�F�N�g����������
	player->Finalize();
	delete player;

	for (int i = 0; i <= e_spawn->GetMaxEnemy(); i++)
	{
		/*if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}*/
		delete enemy[i];
	}
	//delete[] enemy;
	//�e�̏���
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Finalize();
			delete bullet[i];
			bullet[i] = nullptr;
		}
	}
	delete[] bullet;
}

// ���݂̃V�[�����擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

// �n�C�X�R�A�Ǎ�
void GameMainScene::ReadHighScore()
{
	//RankingData data;
	//data.Initialize();

	//high_score = data.GetScore(0);

	//data.Finalize();

	high_score = RankingData::GetScore(0);
}

// �����蔻�菈���i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	// �v���C���[���o���A�𒣂��Ă����瓖���蔻�薳��
	if (p->IsBarrier()) {
		return false;
	}

	// �G��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (e == nullptr) {
		return false;
	}

	// �ʒu���̍����擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	// �����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
	// �R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����
	return ((fabs(diff_location.x)<box_ex.x)&&(fabsf(diff_location.y)<box_ex.y));
}

bool GameMainScene::SpawnBullet()
{
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] == nullptr)
		{
			bullet[i] = new Bullet();
			//�e�̃x�N�g���Ƃ����W�Ƃ��������Ƃ��ēn��
			bullet[i]->Initialize(player->GetAim(), player->GetLocation(), 5.0f, 10, 1, 0);

			return true;
		}
	}
	return false;
}


// �Q�[�����C���ɂ��邪�A�����Ƃ��Ďg���Ă���̂̓G�l�~�[��
bool GameMainScene::Enemy_SpawnBullet(Vector2D e_vec,Vector2D e_location,float speed,float damage)
{
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (bullet[i] == nullptr)
		{
			bullet[i] = new Bullet();
			//�e�̃x�N�g���Ƃ����W�Ƃ��������Ƃ��ēn��
			bullet[i]->Initialize(e_vec, e_location, speed, 10,damage, 1);

			return true;
		}
	}
	return false;
}

void GameMainScene::BulletManager()
{
	
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		bool hit = false;
		if (bullet[i] != nullptr)
		{
			//�e�𔭎˂����̂��v���C���[��������
			if (bullet[i]->GetType() == 0)	
			{
				for (int j = 0; j <= e_spawn->GetMaxEnemy(); j++)//�G�̍ő吔
				{
					if (enemy[j] != nullptr) {
						//�G�ƒe�̓����蔻��@�e�̍��W�A���a�ƓG�̍��W�A���a�������Ƃ���
						if (CheckCollision(bullet[i]->GetLocation(), bullet[i]->GetRadius(), enemy[j]->GetLocation(),enemy[j]->Get_Radius()))
						{
							hit = true;
							enemy[j] = nullptr;
						}
					}
				}
			}
			//�e�𔭎˂����̂��G�l�~�[��������
			else if (bullet[i]->GetType() == 1)	
			{
				//�v���C���[�ƒe�̓����蔻��@�e�̍��W�A���a�ƃv���C���[�̍��W�A���a�������Ƃ���
				if(CheckCollision(bullet[i]->GetLocation(), bullet[i]->GetRadius(), player->GetLocation(), player->GetRadius()))
				{
					hit = true;
					player->DecreaseHp(bullet[i]->GetDamage());
				}
			}

			//�e���͈͊O�ɍs�������̏���
			if (bullet[i]->GetLocation().x < 0 || bullet[i]->GetLocation().x > 1280 ||
				bullet[i]->GetLocation().y < 0 || bullet[i]->GetLocation().y > 720)
			{
				bullet[i] = nullptr;
			}
			if (hit == true) {
				bullet[i] = nullptr;
			}
		}
	}
}

void GameMainScene::spawn_Enemys()
{
	if (enemy[E_num] == nullptr) {
		// �G�l�~�[�̏o�����Ԃɓ��B������
		if (++e_spownCnt > e_spawn->LoadEnemy(E_num).time * 60) {

			//�o�������G�l�~�[�̏���S�đ��M
			enemy[E_num] = new Enemy(
				e_spawn->LoadEnemy(E_num).location_x		// X���W�擾
				, e_spawn->LoadEnemy(E_num).location_y		// Y���W�擾
				, e_spawn->LoadEnemy(E_num).radius			// ���a�擾
				, e_spawn->LoadEnemy(E_num).speed			// �X�s�[�h�擾
				, e_spawn->LoadEnemy(E_num).bullet_speed		// ���̃X�s�[�h�擾
				, e_spawn->LoadEnemy(E_num).score			// ���j���̃X�R�A���擾
				, e_spawn->LoadEnemy(E_num).hp				// HP�擾
				, E_num										// �����̖ڂȂ̂�
				, 1											// �G�l�~�[�̃^�C�v�i���������j
				, enemy_image[GetRand(enemy_image_num - 1)]								// �G�l�~�[�̉摜
			);
			// �G�l�~�[�̐����}�b�N�X�l�𒴂��Ă��Ȃ��Ȃ�
			if (E_num <= e_spawn->GetMaxEnemy()) {
				E_num = E_num + 1;
			}
		}
	}
}
