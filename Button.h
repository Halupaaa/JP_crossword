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
    Button(const string& text, float yPos, Font& f, Vector2f buttonSize);

    bool isClicked(Vector2i mousePos);

    void draw();
};
