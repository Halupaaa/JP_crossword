#include "Button.h"

#include <any>

#include "Design.h"
#include "GameState.h"

Button::Button()
{
    box.setOutlineThickness(1);
	Design::loadFonts();
}

Button::Button( const string& text, float yPos, Vector2f buttonSize)
{
    if (std::any_of(text.begin(), text.end(), ::isdigit)) 
    {
        label.setFont(Design::SecondFont);
    }
    else label.setFont(Design::FirstFont);

    label.setString(text);
    label.setCharacterSize(buttonSize.y * 2.f / 3.f);

    FloatRect bounds = label.getLocalBounds();
    label.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

    box.setSize(buttonSize);

	Vector2f position (Design::Window->getSize().x / 2.f - buttonSize.x / 2.f, yPos);

    box.setPosition(position);
    label.setPosition(position.x + box.getSize().x / 2.f, position.y + box.getSize().y / 2.f);

    box.setFillColor(Design::MenuButtonColor);
    box.setOutlineColor(Design::MenuTextColor);
    label.setFillColor(Design::MenuTextColor);
    box.setOutlineThickness(2);
};

bool Button::isClicked(Vector2i mousePos)
{
    return box.getGlobalBounds().contains((Vector2f)mousePos);
}


void Button::draw()
{
    Design::Window->draw(box);
    Design::Window->draw(label);
}
