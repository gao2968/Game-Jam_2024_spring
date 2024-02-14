#include "FontManager.h"
#include "DxLib.h"

int FontManager::font[];

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

void FontManager::Initialize()
{
	font[0] = CreateFontToHandle(NULL, 16, 4, DX_FONTTYPE_NORMAL);
	font[1] = CreateFontToHandle("Bauhaus 93", 32, 16, DX_FONTTYPE_NORMAL);
	font[2] = CreateFontToHandle("Bauhaus 93", 24, 12, DX_FONTTYPE_NORMAL);
	font[3] = CreateFontToHandle("Bauhaus 93", 48, 24, DX_FONTTYPE_NORMAL);
}

void FontManager::Finalize()
{
	DeleteFontToHandle(font[0]);
	DeleteFontToHandle(font[1]);
	DeleteFontToHandle(font[2]);
	DeleteFontToHandle(font[3]);
}
