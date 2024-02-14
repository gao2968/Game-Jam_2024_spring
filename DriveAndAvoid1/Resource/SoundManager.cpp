#include "SoundManager.h"
#include "DxLib.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::Initialize()
{
	BGM[0] = LoadSoundMem("sound/�G���h��ʉ������P.mp3");
	BGM[1] = LoadSoundMem("sound/�^�C�g������.mp3");
	BGM[2] = LoadSoundMem("sound/�{�X�퉹��.mp3");
	BGM[3] = LoadSoundMem("sound/�ʏ퉹�����P.mp3");
	BGM[4] = LoadSoundMem("sound/�ʏ퉹�����Q.mp3");

	SE[0] = LoadSoundMem("sound/�U����.mp3");

}

void SoundManager::Finalize()
{
	for (int i = 0; i < 8; i++)
	{
		DeleteSoundMem(BGM[i]);
	}
	for (int i = 0; i < 16; i++)
	{
		DeleteSoundMem(SE[i]);
	}
}
