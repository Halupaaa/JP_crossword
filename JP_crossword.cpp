#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include"Game.h"
#include "dependencies/include/nlohmann/json.hpp"

using json = nlohmann::json;

struct GridHints {
    int size;
    vector<vector<int>> top_hints;
    vector<vector<int>> left_hints;
};

Grid generateRandomGrid(json info_hints)
{
    int selected_index = rand() % info_hints["grids"].size();

    json selected_grid = info_hints["grids"][selected_index];

    int size = selected_grid["size"];
    vector<vector<int>> hints[2] = {
        selected_grid["top_hints"].get<vector<vector<int>>>(),
        selected_grid["left_hints"].get<vector<vector<int>>>()
    };
	Grid grid(size, hints);
    return grid;
}

int main()
{
	srand(time(0));

    ifstream file("crossword_hints.json");
    if (!file.is_open()) {
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
		game.update(temp_grid);
        game.render(temp_grid);

        while (game.menu_or_grid == 'g')
        {
            temp_grid = generateRandomGrid(info_hints);
            game.update(temp_grid);

            while (!temp_grid.isSolved())
            {
                game.update(temp_grid);
                game.render(temp_grid);
            }
            if (temp_grid.isSolved())
            {
				game.menu_or_grid = 'n';
				game.menu.navMenu();

            }
        }
        
    }
    return 0;
}

/*
 vector<vector<int>> top_hints_5_1 = { {1,1}, {2,1}, {1,1,1}, {1,2}, {1,1} };
    vector<vector<int>> left_hints_5_1 = { {5}, {1}, {1}, {1}, {5} };
    vector<vector<int>>hints_5_1[2] = { top_hints_5_1 , left_hints_5_1 };

    vector<vector<int>> hints_5_2[2] = { {{1,1,1},{3}, {2,2}, {3}, {1,1,1} }, { {1,1,1}, {3}, {2,2}, {3}, {1,1,1}} };

    vector<vector<int>> hints_5_3[2] = {{{1,2},{4},{1,1}, {4},{2,1}}, {{2,1}, {4}, {1,1}, {4}, {1,2}}};

    vector<vector<int>> hints_5_4[2] = {{{2}, {4}, {1,3}, {4}, {2}}, {{1,1,1},{5},{3}, {1,1}, {3}}};

    vector<vector<int>> hints_5_5[2] = {{{4},{3},{3},{3},{4}},{{1,1},{5},{5},{1,1,1},{1,1}}};
    //

    vector<vector<int>>hints_10_1[2] = { {{1}, {1,5}, {7,2}, {4,1},{7,2}, {7},{7,2}, {1,5}, {1,1,1}, {1,2}}, {{1, 1, 1}, {1, 1, 1}, {}, {7,}, {6,2}, {1,4,2},{8},{7}, {1,5,1}, {8}} };

    vector<vector<int>>hints_10_2[2] = {{{2},{4},{4},{8}, {1,1},{1,1},{2,1,1},{4,1,1},{4,1,1},{8}},
        {{4},{1,3},{3,1},{1,4},{1,1},{3,1},{4,3},{4,4},{2,4},{2}} };

    vector<vector<int>>hints_10_3[2] = {{{7}, {4,1,1},{7,1},{2,3},{1,1},{1,1},{1,2},{1,1,1},{3,2},{7}},
        {{1,1},{1,1},{10},{2,2,1},{1,3},{1,1,1},{1,3},{2,4},{10},{1,1}} };

    vector<vector<int>>hints_10_4[2] = {{{1,2},{1,3},{1,4},{9},{10},{10},{9},{1,4},{1,3},{1,2}},
    {{2},{6},{8},{10},{10},{4},{4},{4},{4},{10}}};

    vector<vector<int>>hints_10_5[2] = {{{2,1},{1,2,2},{2,2},{1,2,1},{1,1,2,1,1},{1,1,2,3},{1,1,4},{2,2},{1,2,2},{2,1}},
    {{4},{3,1},{10},{1,1,1,1}, {1,2,1},{1,2,1},{1,1,1},{1,2,1},{1,1},{8}}};
    //
    vector<vector<int>>hints_15_1[2] = { {{1,1}, {8}, {1,3}, {1,2,4},{1,2,7},{1,2,4,1},{1,4},{4,2,1}, {4,1,2}, {1,2,3}, {1,2,1,4}, {1,2,2,1,1}, {1,1,1,1}, {8},{1,1,1}},

    {{1}, {2}, {1}, {2,2}, {2,1}, {9}, {1, 1, 1, 5}, {1, 1, 1, 7}, {15}, {1, 1}, {1,2, 3, 1}, {1, 2, 2, 3, 1}, {1,2,1}, {1, 2, 1}, {15}} };

    vector<vector<int>>hints_15_2[2] = { {{15},{11,1,1},{10,1},{2,8,2},{1,5,1},{3,1,1},{4},{7},{2,6},{1,1,1,5},{1,2,5,1,2},{2,5,1,1},{11,3},{9,1,1},{10,1,2}},
    {{10,1,2},{1,1,5,1,1},{1,6,3},{2,6,1,1},{1,3,1,1,2},{1,1,1,2,6},{6,1,6},{5,5},{5,1,5},{5,1,5},{4,1,4},{3,1,3},{3,1,3},{4,1,4},{5,5}}};

    vector<vector<int>>hints_15_3[2] = { {{9,1,3},{2,2,3,3},{1,2,1,1,6},{2,2},{4,2,1,3,1},{5,3,2},{3,11},{3,1,1,1,1,3},{3,1,1,1,1,3},{3,1,1,1,3},{3,1,1,3},{3,1,1,1,1,3},{3,1,1,1,3},{3,1,1,3},{3,1,1,1,1,3}},
    {{15},{10,4},{9,1,3},{1,1,1},{1,7,1,3},{2,2},{1,2,6,2},{2,1,1},{2,1,4,1,1},{1,1,1,1},{5,4,2},{2,3},{11,1,1},{12,2},{15}}};

    vector<vector<int>>hints_15_4[2] = {{{4},{2,1,4},{2,1,1,1},{1,2,4},{1,1},{1,1,2},{3,2,3},{2,4,1,2},{9,3,1},{5,7},{1,2,2,5,1},{3,1,1,1},{1,2,1},{2},{1,1}},

	{{1,1,3},{1,1,1,1,1},{5,1,1},{4,1,3},{1,6},{3,2},{4},{2,4},{3,3},{5,1},{2,1},{3,1,1,1},{1,3,2,2,1},{1,4,3},{3,1,2,3,2} }};

    vector<vector<int>>hints_15_5[2] = { {{1},{1,1,1},{2,1,2},{1,1,2},{2,6},{1,1,5,1},{8,2},{4,4},{1,5,2},{8,2},{8},{1,6},{1,2},{1,2},{1,1}},
    {{},{},{4},{6},{2,1,1},{3,2,1},{6,5},{14},{8},{8},{6},{1,1,4},{4,2,2},{3},{2,2}}};

 vector<vector<int>>hints_15_5[2] = { {{1},{1,1,1},{2,1,2},{1,1,2},{2,6},{1,1,5,1},{8,2},{4,4},{1,5,2},{8,2},{8},{1,6},{1,2},{1,2},{1,1}},
    {{},{},{4},{6},{2,1,1},{3,2,1},{6,5},{14},{8},{8},{6},{1,1,4},{4,2,2},{3},{2,2}} };
*/