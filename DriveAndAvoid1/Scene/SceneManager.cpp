#include "SceneManager.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "ResultScene.h"
#include "HelpScene.h"
#include "RankingDispScene.h"
#include "RankingInputScene.h"
#include "KH_TestScene.h"
#include "TakePictureScene.h"
#include "../Resource/FontManager.h"
#include "../Object/RankingData.h"
#include "EndScene.h"
#include "RuleScene.h"
#include "../Resource/SoundManager.h"
#include "../Utility/TakePicture.h"

SceneManager::SceneManager() : current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{

}
//�V�[���}�l�[�W���[�@�\�F����������
void SceneManager::Initialize()
{
	//�E�B���h�E�̃^�C�g����ݒ�
	SetMainWindowText("KAO-");

	SetGraphMode(1280, 720, 32);

	//�E�B���h�E���[�h�ŋN��
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("�E�B���h�E���[�h�ŋN���ł��܂���ł���\n");
	}

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		throw("Dx���C�u�������������ł��܂���ł���\n");
	}

	//�`���w�菈��
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("�w���̎w�肪�ł��܂���ł���\n");
	}

	//SetWindowSize(1280, 720);
	
	SetAlwaysRunFlag(true);

	FontManager::Initialize();
	RankingData::Initialize();
	SoundManager::Initialize();
	TakePicture::Initialize();

	//�^�C�g���V�[������n�߂�
	ChangeScene(eSceneType::E_TITLE);
}

//�V�[���}�l�[�W���[�@�\�F�X�V����
void SceneManager::Update()
{
	//�t���[���J�n���ԁi�}�C�N���b�j���擾
	LONGLONG start_time = GetNowHiPerformanceCount();

	//���C�����[�v
	while (ProcessMessage() != -1)
	{
		//���ݎ��Ԃ��擾
		LONGLONG now_time = GetNowHiPerformanceCount();

		//1�t���[��������̎��Ԃɓ��B������A�X�V�y�ѕ`�揈�����s��
		if ((now_time - start_time) >= DELTA_SECOND)
		{
			//�t���[���J�n���Ԃ��X�V����
			start_time = now_time;

			//���͋@�\�F�X�V����
			InputControl::Update();

			//�X�V�����i�߂�l�͎��̃V�[�����j
			eSceneType next = current_scene->Update();

			//�`�揈��
			Draw();

			//�G���h���I������Ă�����A�Q�[�����I������
			if (next == eSceneType::E_END)
			{
				break;
			}

			//���݂̃V�[���Ǝ��̃V�[��������Ă�����A�؂�ւ��������s��

			if (next != current_scene->GetNowScene()) 
			{
				ChangeScene(next);
			}
		}

		//ESCAPE�L�[�������ꂽ��A�Q�[�����I������
		if (CheckHitKey(KEY_INPUT_ESCAPE) || InputControl::GetButtonUp(XINPUT_BUTTON_BACK))
		{
			break;
		}
	}
}

//�V�[���}�l�[�W���[�@�\�F�I��������
void SceneManager::Finalize()
{
	//�V�[�����̍폜
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	//�t�H���g�폜
	FontManager::Finalize();
	RankingData::Finalize();
	SoundManager::Finalize();
	TakePicture::Finalize();

	//DX���C�u�����̎g�p���I������
	DxLib_End();
}

//�V�[���}�l�[�W���[�@�\�F�`�揈��
void SceneManager::Draw() const
{
	//��ʂ̏�����
	ClearDrawScreen();

	//�V�[���̕`��
	current_scene->Draw();

	//����ʂ̓��e��\��ʂɔ��f
	ScreenFlip();
}

//�V�[���؂�ւ�����
void SceneManager::ChangeScene(eSceneType scene_type)
{
	//�V�[���𐶐�����iSceneBase���p������Ă��邩�H�j
	SceneBase* new_scene = dynamic_cast<SceneBase*>(CreateScene(scene_type));

	//�G���[�`�F�b�N
	if (new_scene == nullptr)
	{
		throw("�V�[���������ł��܂���ł����B\n");
	}

	//�O��V�[���̏I�����������s��
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//�V�������������V�[���̏��������s��
	new_scene->Initialize();

	//���݃V�[���̍X�V
	current_scene = new_scene;
}

//�V�[����������
SceneBase* SceneManager::CreateScene(eSceneType scene_type)
{
	//�����i�V�[���^�C�v�j�ɂ���āA��������V�[�������肷��
	switch (scene_type)
	{
	case eSceneType::E_TITLE:
		return new TitleScene;
	case eSceneType::E_MAIN:
		return new GameMainScene;
	case eSceneType::E_RESULT:
		return new ResultScene;
	case eSceneType::E_HELP:
		return new HelpScene;
	case eSceneType::E_RANKING_DISP:
		return new RankingDispScene;
	case eSceneType::E_RANKING_INPUT:
		return new RankingInputScene;
	case eSceneType::E_TAKE_PICTURE:
		return new TakePictureScene;
	case eSceneType::E_END1:
		return new EndScene;
	case eSceneType::E_RULE:
		return new RuleScene;
	case eSceneType::E_TEST:
		return new KH_TestScene;
	default:
		return nullptr;
	}
}