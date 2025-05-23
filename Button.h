#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button
{
private:
    RectangleShape box;
    Text label;

public:
    Button();
    Button(const string& text, Vector2f buttonPos, Vector2f buttonSize);

    bool isClicked(const Vector2i& mousePos) const;

    void draw();
};
