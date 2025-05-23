#include "Menu.h"
#include "Design.h"
#include "Game.h"

Menu::Menu()
{
	Design::loadTextures();
	Design::loadFonts();
}

void Menu::updateAnimation()
{
    backgroundSprite.setScale(
        Design::Window->getSize().x / (float)Design::BackgroundTexture[0].getSize().x + 0.3,
		Design::Window->getSize().y / (float)Design::BackgroundTexture[0].getSize().y
    );

    if (animationClock.getElapsedTime().asSeconds() >= frameDelay)
    {
        currentFrame = (currentFrame + 1) % 11;
        backgroundSprite.setTexture(Design::BackgroundTexture[currentFrame]);
        animationClock.restart();
    }

    Design::Window->draw(backgroundSprite);
}

void Menu::GameStyleButton()
{
    Vector2f buttonSize(50.f, 50.f);
    Vector2f buttonPos(Design::Window->getSize().x - 100.f, Design::Window->getSize().y - 100.f);

    gameStyleBtn = Button("", buttonPos, buttonSize);
}

void Menu::startMenu()
{
    backgroundSprite.setColor(Design::StartBackgroundColor);

    titleText.setString("");

    mainText.setFont(Design::FirstFont);
    mainText.setString("jp crosswords");
    mainText.setCharacterSize(140);
    mainText.setFillColor(Design::MenuTextColor);


    FloatRect titleTextBounds = mainText.getLocalBounds();
    mainText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, 200);

    Vector2f buttonSize(400.f, 80.f);
    Vector2f buttonPos(Design::Window->getSize().x / 2.f - buttonSize.x / 2.f, Design::Window->getSize().y / 2.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);

    firstBtn = Button( "play", Vector2f(buttonPos.x, buttonPos.y - 100), buttonSize);
    secondBtn = Button( "about", buttonPos, buttonSize);
    thirdBtn = Button("exit", Vector2f(buttonPos.x, buttonPos.y + 100), buttonSize);
}

void Menu::infoMenu()
{
    backgroundSprite.setColor(Design::BackgroundColor);

	titleText.setFont(Design::FirstFont);
	titleText.setString("How to Play Japanese Crosswords?");
	titleText.setCharacterSize(65);
	titleText.setFillColor(Design::MenuTextColor);
	FloatRect titleTextBounds = titleText.getLocalBounds();
	titleText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    titleText.setPosition(Design::Window->getSize().x / 2.f, 130);
    Design::Window->draw(titleText);

    mainText.setFont(Design::FirstFont);
    mainText.setString("\nYour goal is to reveal a hidden picture by filling in \nthe correct squares - using logic, not luck.Numbers\n on the top and left show how many filled blocks\n are in each column or row.\nMultiple numbers mean separate groups, with at \nleast one empty square between them.Left click to \nfill a square.Right click to cross out a square.\nStart with rows or columns that have big or obvious \nclues.Look for overlaps - where filled blocks must go \nno matter what.\nTake your time.Stay sharp.And remember - it's not just \nabout solving it, it's about solving it right.Ready? Let's go!");
    mainText.setCharacterSize(35);
    mainText.setFillColor(Design::MenuTextColor);


    FloatRect mainBounds = mainText.getLocalBounds();
    mainText.setOrigin(mainBounds.width / 2.f, mainBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, Design::Window->getSize().y / 2.f - 50);

    Vector2f buttonSize(400.f, 80.f);
    Vector2f buttonPos(Design::Window->getSize().x / 2.f - buttonSize.x / 2.f, Design::Window->getSize().y / 2.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);

    firstBtn = Button("back", Vector2f(buttonPos.x, buttonPos.y + 300), buttonSize);
	secondBtn = Button("", Vector2f(-500, -500), buttonSize);
	thirdBtn = Button("", Vector2f(-500, -500), buttonSize);
    gameStyleBtn = Button("", Vector2f(-500, -500), buttonSize);

}

void Menu::categoryMenu()
{
    backgroundSprite.setColor(Design::BackgroundColor);

    titleText.setString("");

    mainText.setFont(Design::FirstFont);
    mainText.setString("A random game will be picked \nfrom the category you chose");
    mainText.setCharacterSize(65);
    mainText.setFillColor(Design::MenuTextColor);

    FloatRect titleTextBounds = mainText.getLocalBounds();
    mainText.setOrigin((titleTextBounds.width / 2.f) - 20.f, titleTextBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, 250);

    Vector2f buttonSize(400.f, 80.f);
    Vector2f buttonPos(Design::Window->getSize().x / 2.f - buttonSize.x / 2.f, Design::Window->getSize().y / 2.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);

    firstBtn = Button("5 x 5", Vector2f(buttonPos.x, buttonPos.y - 100), buttonSize);
    secondBtn = Button("10 x 10", Vector2f(buttonPos.x, buttonPos.y), buttonSize);
    thirdBtn = Button("15 x 15", Vector2f(buttonPos.x, buttonPos.y + 100), buttonSize);
    gameStyleBtn = Button("", Vector2f(-5000, -5000), buttonSize);

}

void Menu::navMenu()
{
    titleText.setString("");

    mainText.setString("");

    RectangleShape overlay;
    overlay.setSize(Vector2f(Design::Window->getSize()));
    overlay.setFillColor(Design::TransparentBlackColor);
    Design::Window->draw(overlay);

    FloatRect titleTextBounds = mainText.getLocalBounds();
    mainText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, 200);

    Vector2f buttonSize(400.f, 80.f);
    Vector2f buttonPos(Design::Window->getSize().x / 2.f - buttonSize.x / 2.f, Design::Window->getSize().y / 2.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);

    firstBtn = Button("continue", Vector2f(buttonPos.x, buttonPos.y - 100), buttonSize);
    secondBtn = Button("new game", Vector2f(buttonPos.x, buttonPos.y), buttonSize);
    thirdBtn = Button("start menu", Vector2f(buttonPos.x, buttonPos.y + 100), buttonSize);
    gameStyleBtn = Button("", Vector2f(-500, -500), buttonSize);

}
void Menu::winNavMenu()
{
    titleText.setString("");

    RectangleShape overlay;
    overlay.setSize(Vector2f(Design::Window->getSize()));
    overlay.setFillColor(Design::TransparentBlackColor);
    Design::Window->draw(overlay);

    mainText.setFont(Design::FirstFont);
    mainText.setString("Puzzle solved!");
    mainText.setCharacterSize(120);
    if (Design::MenuButtonColor == Color(45, 47, 56) || 
        Design::MenuButtonColor == Color(60, 40, 50)) mainText.setFillColor(Design::MenuTextColor);
	else mainText.setFillColor(Design::MenuButtonColor);

    FloatRect titleTextBounds = mainText.getLocalBounds();
    mainText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    mainText.setPosition(Design::Window->getSize().x / 2.f, 250);

    Vector2f buttonSize(400.f, 80.f);
    Vector2f buttonPos(Design::Window->getSize().x / 2.f - buttonSize.x / 2.f, Design::Window->getSize().y / 2.f);
    Color boxColor(Design::MenuButtonColor);
    Color outlineColor(Design::MenuTextColor);
    Color textColor(Design::MenuTextColor);

    firstBtn = Button("new game", Vector2f(buttonPos.x, buttonPos.y - 100), buttonSize);
    secondBtn = Button("start menu", Vector2f(buttonPos.x, buttonPos.y), buttonSize);
    thirdBtn = Button("exit", Vector2f(buttonPos.x, buttonPos.y + 100), buttonSize);
    gameStyleBtn = Button("", Vector2f(-500, -500), buttonSize);

}

int Menu::handleClick(Vector2i& mousePos)
{
    if (gameStyleBtn.isClicked(mousePos)) return 0;
    else if (firstBtn.isClicked(mousePos)) return 1;
    else if (secondBtn.isClicked(mousePos)) return 2;
    else if (thirdBtn.isClicked(mousePos)) return 3;
	else return -1;
}

void Menu::draw(GameState& state)
{
    switch (state)
    {
	    case GameState::StartMenu:
        {
	    	updateAnimation();
	    	GameStyleButton();
			startMenu();
	    	break;
        }
		case GameState::InfoMenu: infoMenu(); break;
		case GameState::CategoryMenu: categoryMenu(); break;
		case GameState::NavigationMenu: navMenu(); break;
		case GameState::WinningNavigationMenu: winNavMenu(); break;
    }

    Design::Window->draw(titleText);
	Design::Window->draw(mainText);
    firstBtn.draw();
    secondBtn.draw();
    thirdBtn.draw();
	gameStyleBtn.draw();
}