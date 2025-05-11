#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <algorithm>
#include "Design.h"


using namespace sf;
using namespace std;

class Grid
{
private:
    Font font;

    int field_width;
    float cell_size;
    vector<vector<int>> cell_states;
    int max_sizes[2];
    int height;
    int width;
    float center_x;
    float center_y;

    vector<vector<int>> cur_result[2];

    vector<bool> incorrect[2];


public:
    vector<vector<int>> hints[2];

    Grid();
    Grid(int width, vector<vector<int>> hints[]);

    //
    bool isSolved();
	void isRowOrColumnSolved(int grid_x, int grid_y);
    void compareResultWithHints();
    void resultUpdate(int grid_x, int grid_y);

    void handleClick(Vector2i mousePos, bool fill);
    void draw();
};

