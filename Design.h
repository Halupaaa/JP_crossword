#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace sf;

struct Design
{
    static RenderWindow* Window;

    static const Color BackgroundColor;

    static const Color HintTextColor;
    static const Color HintCellColor;
	static const Color HintCellOutlineColor;

    static const Color GameCellColor;
    static const Color FilledCellColor;
    static const Color GridOutlineColor;
    static const Color CrossColor;

    static const Color IncorrectCellColor;
};
