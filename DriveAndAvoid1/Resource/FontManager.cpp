#include "FontManager.h"
#include "DxLib.h"

int FontManager::font0 = NULL;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

void FontManager::Initialize()
{
	font0 = CreateFontToHandle(NULL, 16, 4, DX_FONTTYPE_NORMAL);
}

void FontManager::Finalize()
{
	DeleteFontToHandle(font0);
}
