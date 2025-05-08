#include "Button.h"
#include "Design.h"

Button::Button()
{
    box.setOutlineThickness(3);
}

Button::Button( const string& text, float yPos, Font& f, Vector2f buttonSize)
{
    label.setFont(f);
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
    box.setOutlineThickness(3);
};

void Button::draw()
{
    Design::Window->draw(box);
    Design::Window->draw(label);
}
