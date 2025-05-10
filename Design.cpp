#include "Design.h"
#include "GameStyle.h"
#include <iostream>

using namespace std;

RenderWindow* Design::Window = new RenderWindow(VideoMode({ 1400, 940 }), "JCross", Style::Close | Style::Titlebar);

Color Design::MenuTextColor;
Color Design::MenuButtonColor;
Color Design::GameStyleBtnColor;

Color Design::StartBackgroundColor;
Color Design::BackgroundColor;

Color Design::HintTextColor;
Color Design::HintCellColor;
Color Design::HintCellOutlineColor;

Color Design::GameCellColor;
Color Design::FilledCellColor;
Color Design::GridOutlineColor;
Color Design::CrossColor;

Color Design::IncorrectCellColor;
Color Design::TransparentBlackColor = Color(0, 0, 0, 400);
Color Design::TransparentGrayColor = Color(120, 120, 120, 200);


Font Design::FirstFont;
Font Design::SecondFont;

Texture Design::BackgroundTexture[];

void Design::loadFonts()
{
    Design::FirstFont.loadFromFile("fonts/Metch_Bright.ttf");
    Design::SecondFont.loadFromFile("fonts/Aromatron-Regular.otf");
}

void Design::loadTextures()
{
    for (int i = 0; i < 12; i++) 
    {
        string filename = "pics/cadr" + std::to_string(i) + ".png";
        BackgroundTexture[i].loadFromFile(filename);
    }
}


void Design::applyStyle(GameStyle style)
{
    switch (style)
    {
    case GameStyle::LightPink:
	    {
    		Design::MenuTextColor = Color(90, 70, 85);
    		Design::MenuButtonColor = Color(245, 230, 230);
    		Design::GameStyleBtnColor = Color(90, 70, 85);

    		Design::StartBackgroundColor = Color(250, 227, 227);
    		Design::BackgroundColor = Color(232, 216, 216);

    		Design::HintTextColor = Color(90, 70, 85);
    		Design::HintCellColor = Color(245, 230, 230);
    		Design::HintCellOutlineColor = Color(210, 170, 180);

    		Design::GameCellColor = Color(255, 240, 235);
    		Design::FilledCellColor = Color(90, 40, 60);
    		Design::GridOutlineColor = Color(140, 100, 110);
    		Design::CrossColor = Color(90, 40, 60);

    		Design::IncorrectCellColor = Color(189, 175, 175);
    		break;
	    }
    case GameStyle::DarkPink:
	    {
    		Design::MenuTextColor = Color(100, 40, 30);
    		Design::MenuButtonColor = Color(240, 210, 200);
    		Design::GameStyleBtnColor = Color(100, 40, 30);

    		Design::StartBackgroundColor = Color(242, 229, 208);
    		Design::BackgroundColor = Color(245, 235, 220);

    		Design::HintTextColor = Color(100, 40, 30);
    		Design::HintCellColor = Color(240, 210, 200);
    		Design::HintCellOutlineColor = Color(160, 90, 70);

    		Design::GameCellColor = Color(255, 235, 215);
    		Design::FilledCellColor = Color(120, 30, 30);
    		Design::GridOutlineColor = Color(140, 60, 50);
    		Design::CrossColor = Color(120, 30, 30);

    		Design::IncorrectCellColor = Color(209, 182, 176);
    		break;
	    }
    case GameStyle::Dark:
	    {
    		Design::MenuTextColor = Color(200, 200, 200);
    		Design::MenuButtonColor = Color(45, 47, 56);
    		Design::GameStyleBtnColor = Color(200, 200, 200);

    		Design::StartBackgroundColor = Color(30, 33, 41);
    		Design::BackgroundColor = Color(24, 26, 32);

    		Design::HintTextColor = Color(200, 200, 200);
    		Design::HintCellColor = Color(45, 47, 56);
    		Design::HintCellOutlineColor = Color(80, 85, 100);

    		Design::GameCellColor = Color(36, 39, 48);
    		Design::FilledCellColor = Color(225, 195, 120);
    		Design::GridOutlineColor = Color(100, 100, 110);
    		Design::CrossColor = Color(225, 195, 120);

    		Design::IncorrectCellColor = Color(140, 120, 76);
		    break;
	    }
    case GameStyle::GameDark:
	    {
    		Design::MenuTextColor = Color(255, 210, 140);
    		Design::MenuButtonColor = Color(60, 40, 50);
    		Design::GameStyleBtnColor = Color(255, 210, 140);

    		Design::StartBackgroundColor = Color(29, 26, 38);
    		Design::BackgroundColor = Color(20, 18, 26);

    		Design::HintTextColor = Color(255, 210, 140);
    		Design::HintCellColor = Color(60, 40, 50);
    		Design::HintCellOutlineColor = Color(120, 80, 90);

    		Design::GameCellColor = Color(40, 30, 50);
    		Design::FilledCellColor = Color(255, 90, 90);
    		Design::GridOutlineColor = Color(255, 190, 120);
    		Design::CrossColor = Color(255, 90, 90);

    		Design::IncorrectCellColor = Color(92, 31, 31);
    		break;
	    }
    }
}
