#include <iostream>
#include"Game.h"

int main()
{
    vector<vector<int>> top_hints_5_1 = { {1,1}, {2,1}, {1,1,1}, {1,2}, {1,1} };
    vector<vector<int>> left_hints_5_1 = { {5}, {1}, {1}, {1}, {5} };
    vector<vector<int>>hints_5_1[2] = { top_hints_5_1 , left_hints_5_1 };

    vector<vector<int>> hints_5_2[2] = { {{1,1,1},{3}, {2,2}, {3}, {1,1,1} }, { {1,1,1}, {3}, {2,2}, {3}, {1,1,1}} };

    vector<vector<int>>hints_10[2] = { {{1}, {1,5}, {7,2}, {4,1},{7,2}, {7},{7,2}, {1,5}, {1,1,1}, {1,2}}, {{1, 1, 1}, {1, 1, 1}, {}, {7,}, {6,2}, {1,4,2},{8},{7}, {1,5,1}, {8}} };

    vector<vector<int>>hints_15[2] = { {{1,1}, {8}, {1,3}, {1,2,4},{1,2,7},{1,2,4,1},{1,4},{4,2,1}, {4,1,2}, {1,2,3}, {1,2,1,4}, {1,2,2,1,1}, {1,1,1,1}, {8},{1,1,1}} , {{1}, {2}, {1}, {2,2}, {2,1}, {9}, {1, 1, 1, 5}, {1, 1, 1, 7}, {15}, {1, 1}, {1,2, 3, 1}, {1, 2, 2, 3, 1}, {1,2,1}, {1, 2, 1}, {15}} };

    Grid grid_5_1 = Grid(5, hints_5_1);
    Grid grid_5_2 = Grid(5, hints_5_2);

    Grid grid_10 = Grid(10, hints_10);
    Grid grid_15 = Grid(15, hints_15);

    Game game;

    while (game.running())
    {
		Grid& temp_grid = grid_5_2;

        game.update(temp_grid);

        game.render(temp_grid);

        if (temp_grid.isSolved())
        {
	        cout << "NICEEEE PErerobi ozhu huinu" << endl;
			break;
        }


    }
}