#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Grid.h"
#include "Menu.h"

class Game
{

public:
	Menu menu;
	char menu_or_grid;

	Game();

	const bool running() const;

	void pollEvents(Grid& grid);
	void update(Grid& grid);
	void render(Grid& grid);
};

