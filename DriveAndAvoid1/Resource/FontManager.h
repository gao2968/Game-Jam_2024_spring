#pragma once
class FontManager
{
private:
	static int font0;

public:
	FontManager();
	~FontManager();

	static void Initialize();
	static void Finalize();

	static int GetFont0() { return font0; }
};

