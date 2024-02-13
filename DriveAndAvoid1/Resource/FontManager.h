#pragma once
class FontManager
{
private:
	static int font0;
	static int font1;
	static int font2;

public:
	FontManager();
	~FontManager();

	static void Initialize();
	static void Finalize();

	static int GetFont0() { return font0; }
	static int GetFont1() { return font1; }
	static int GetFont2() { return font2; }
};

