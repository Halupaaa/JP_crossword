#include "Button.h"
#include "Design.h"
#include "GameState.h"
#include <any>

Button::Button()
{
	Design::loadFonts();
}

Button::Button(const string& text, Vector2f buttonPos, Vector2f buttonSize)
{
    if (any_of(text.begin(), text.end(), ::isdigit)) 
    {
        label.setFont(Design::SecondFont);
    }
    else label.setFont(Design::FirstFont);

    label.setString(text);
    label.setCharacterSize(buttonSize.y * 2.f / 3.f);

    FloatRect bounds = label.getLocalBounds();
    label.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

    box.setSize(buttonSize);

    box.setPosition(buttonPos.x, buttonPos.y);
    label.setPosition(buttonPos.x + box.getSize().x / 2.f, buttonPos.y + box.getSize().y / 2.f);

    box.setFillColor( buttonSize.x == 50.f ? Design::GameStyleBtnColor : Design::MenuButtonColor);
    box.setOutlineColor(Design::HintCellOutlineColor);
    label.setFillColor(Design::MenuTextColor);
    box.setOutlineThickness(3);
};

bool Button::isClicked(const Vector2i& mousePos) const
{
    return box.getGlobalBounds().contains((Vector2f)mousePos);
}

void Button::draw()
{
    Design::Window->draw(box);
    Design::Window->draw(label);
}
