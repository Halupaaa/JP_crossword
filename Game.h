#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameStyle.h"
#include "Grid.h"
#include "Menu.h"

class Game
{
public:
	Menu menu;
	GameState state;
	GameStyle style;
	int grid_size;
	int selected_grids[15] = {};

	Game();

	const bool running() const;

	void pollEvents(Grid& grid);
	void updateSelectedGrid();
	void update(Grid& grid);
	void render(Grid& grid);
};