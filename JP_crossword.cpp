#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include"Game.h"
#include "dependencies/include/nlohmann/json.hpp"

using json = nlohmann::json;

struct GridHints
{
    int size;
    vector<vector<int>> top_hints;
    vector<vector<int>> left_hints;
};

Grid generateRandomGrid(json info_hints, int grid_size, int& selected_index, int selected_grids[])
{
    do
    {
	    switch (grid_size)
	    {
			case 5: selected_index = rand() % 5; break;
			case 10: selected_index = rand() % 5 + 5; break;
			case 15: selected_index = rand() % 5 + 10; break;
			default: selected_index = 0; break;
	    }
    } while (selected_grids[selected_index] == 1);

    json selected_grid = info_hints["grids"][selected_index];

    int size = selected_grid["size"];
    vector<vector<int>> hints[2] = {
        selected_grid["top_hints"].get<vector<vector<int>>>(),
        selected_grid["left_hints"].get<vector<vector<int>>>()
    };
	Grid grid(size, hints);
    return grid;
}

int WinMain()
{
	srand(time(0));

    ifstream file("crossword_hints.json");
    if (!file.is_open()) 
    {
        cerr << "File is not open!" << endl;
        return 1;
    }

    json info_hints;
    file >> info_hints;
    file.close();

    Game game;

    Grid temp_grid = Grid();

    while (game.running())
    {
        if (game.state == GameState::NeedToGenerateGrid) 
        {
            int selected_index;
            temp_grid = generateRandomGrid(info_hints, game.grid_size, selected_index, game.selected_grids);
			game.selected_grids[selected_index] = 1;
            game.state = GameState::Game;
        }

        game.update(temp_grid);
        game.render(temp_grid);
    }

    return 0;
}