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
	BGM[0] = LoadSoundMem("sound/エンド画面音源候補１.mp3");
	BGM[1] = LoadSoundMem("sound/タイトル音源.mp3");
	BGM[2] = LoadSoundMem("sound/ボス戦音源.mp3");
	BGM[3] = LoadSoundMem("sound/通常音源候補１.mp3");
	BGM[4] = LoadSoundMem("sound/通常音源候補２.mp3");

	SE[0] = LoadSoundMem("sound/攻撃音.mp3");

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
