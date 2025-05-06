#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Grid.h"

class Game
{
public:
	const bool running() const;

	void pollEvents(Grid& grid);
	void update(Grid& grid);
	void render(Grid& grid);
};

