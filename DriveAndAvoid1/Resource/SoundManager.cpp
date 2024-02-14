#include "SoundManager.h"
#include "DxLib.h"

int SoundManager::BGM[];
int SoundManager::SE[];

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::Initialize()
{
	BGM[0] = LoadSoundMem("Resource/sound/�G���h��ʉ������P.mp3");
	BGM[1] = LoadSoundMem("Resource/sound/�^�C�g������.mp3");
	BGM[2] = LoadSoundMem("Resource/sound/�{�X�퉹��.mp3");
	BGM[3] = LoadSoundMem("Resource/sound/�ʏ퉹�����P.mp3");
	BGM[4] = LoadSoundMem("Resource/sound/�ʏ퉹�����Q.mp3");

	SE[0] = LoadSoundMem("Resource/sound/�U����.mp3");
	SE[1] = LoadSoundMem("Resource/sound/Vois/voic1.mp3");
	SE[2] = LoadSoundMem("Resource/sound/Vois/voic2.mp3");
	SE[3] = LoadSoundMem("Resource/sound/Vois/voic3.mp3");
	SE[4] = LoadSoundMem("Resource/sound/Vois/voic4.mp3");
	SE[5] = LoadSoundMem("Resource/sound/Vois/voic5.mp3");

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
