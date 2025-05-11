#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameStyle.h"

using namespace sf;

struct Design
{
    static RenderWindow* Window;

    static Color MenuTextColor;
	static Color MenuButtonColor;
    static Color GameStyleBtnColor;

    static Color StartBackgroundColor;
    static Color BackgroundColor;

    static Color HintTextColor;
    static Color HintSolvedTextColor;
    static Color HintCellColor;
	static Color HintCellOutlineColor;

    static Color GameCellColor;
    static Color FilledCellColor;
    static Color GridOutlineColor;
    static Color CrossColor;

    static Color IncorrectCellColor;
    static Color TransparentBlackColor;
    static Color TransparentGrayColor;

    static Texture BackgroundTexture[11];

    static Font FirstFont;
    static Font SecondFont;

    static void loadTextures();
    static void loadFonts();

    static void applyStyle(GameStyle style);
};
