#include "FontManager.h"
#include "DxLib.h"

int FontManager::font0 = NULL;
int FontManager::font1 = NULL;
int FontManager::font2 = NULL;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

void FontManager::Initialize()
{
	font0 = CreateFontToHandle(NULL, 16, 4, DX_FONTTYPE_NORMAL);
	font1 = CreateFontToHandle("Bauhaus 93", 32, 16, DX_FONTTYPE_NORMAL);
	font2 = CreateFontToHandle("Bauhaus 93", 24, 12, DX_FONTTYPE_NORMAL);
}

void FontManager::Finalize()
{
	DeleteFontToHandle(font0);
	DeleteFontToHandle(font1);
	DeleteFontToHandle(font2);
}
