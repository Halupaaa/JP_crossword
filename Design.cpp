#include "Design.h"

RenderWindow* Design::Window = new RenderWindow(VideoMode({ 1400, 940 }), "JCross", Style::Close | Style::Titlebar);

/*dark pricolne
const Color Design::BackgroundColor = Color(24, 26, 32);

const Color Design::HintTextColor = Color(200, 200, 200);
const Color Design::HintCellColor = Color(45, 47, 56);
const Color Design::HintCellOutlineColor = Color(80, 85, 100);

const Color Design::GameCellColor = Color(36, 39, 48);
const Color Design::FilledCellColor = Color(225, 195, 120);
const Color Design::GridOutlineColor = Color(100, 100, 110);
const Color Design::CrossColor = Color(225, 195, 120);

const Color Design::IncorrectCellColor = Color(140, 120, 76);
*/
/*sacura milashka

 const Color Design::BackgroundColor = Color(250, 245, 242);

const Color Design::HintTextColor = Color(90, 70, 85);
const Color Design::HintCellColor = Color(245, 230, 230);
const Color Design::HintCellOutlineColor = Color(210, 170, 180);

const Color Design::GameCellColor = Color(255, 240, 235);
const Color Design::FilledCellColor = Color(90, 40, 60);
const Color Design::GridOutlineColor = Color(140, 100, 110);
const Color Design::CrossColor = Color(200, 120, 140);

const Color Design::IncorrectCellColor = Color(189, 175, 175);
*/

/* pricolna sacura*/
const Color Design::MenuTextColor = Color(200, 100, 120);
const Color Design::MenuButtonColor = Color(255, 230, 235);

const Color Design::TransparentColor = Color(0, 0, 0,100);

const Color Design::BackgroundColor = Color(245, 235, 220);

const Color Design::HintTextColor = Color(100, 40, 30);
const Color Design::HintCellColor = Color(240, 210, 200);
const Color Design::HintCellOutlineColor = Color(160, 90, 70);

const Color Design::GameCellColor = Color(255, 235, 215);
const Color Design::FilledCellColor = Color(120, 30, 30);
const Color Design::GridOutlineColor = Color(140, 60, 50);
const Color Design::CrossColor = Color(120, 30, 30);

const Color Design::IncorrectCellColor = Color(209, 182, 176);


/*  Like a game nintendo pricolnaya

 const Color Design::BackgroundColor = Color(20, 18, 26);

const Color Design::HintTextColor = Color(255, 210, 140);
const Color Design::HintCellColor = Color(60, 40, 50);
const Color Design::HintCellOutlineColor = Color(120, 80, 90);

const Color Design::GameCellColor = Color(40, 30, 50);
const Color Design::FilledCellColor = Color(255, 90, 90);
const Color Design::GridOutlineColor = Color(255, 190, 120);
const Color Design::CrossColor = Color(255, 130, 100);

const Color Design::IncorrectCellColor = Color(92, 31, 31);

*/

Font Design::FirstFont;
Font Design::SecondFont;

Texture Design::backgroundTexture;

void Design::loadFonts()
{
	Design::FirstFont.loadFromFile("fonts/Masa_Groovy.ttf");
	Design::SecondFont.loadFromFile("fonts/Groovy_Vibes2.otf");
}

void Design::loadTextures()
{
	backgroundTexture.loadFromFile("pics/waves1.jpeg");
	backgroundTexture.setSmooth(true);
}