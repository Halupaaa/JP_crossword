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
    Vector2i size;
    Vector2f center_pos;

	vector<vector<int>> cur_result[2]; //when grid is solved, cur_result = hints

    vector<bool> incorrect[2];
    vector<bool> solved[2];

    bool maxExceedsHint(const vector<int>& result, const vector<int>& hint);

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

