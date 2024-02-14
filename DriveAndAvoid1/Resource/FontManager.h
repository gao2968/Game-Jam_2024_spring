#pragma once
class FontManager
{
private:
	static int font[16];

public:
	FontManager();
	~FontManager();

	static void Initialize();
	static void Finalize();

	static int GetFont(int n) { return font[n]; }
};

