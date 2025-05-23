#include "Grid.h"
#include "Design.h"
#include <algorithm>


Grid::Grid() : field_width(0), cell_size(0)
{
	Vector2i size(0, 0);
    Vector2f center_pos(0,0);
    max_sizes[0] = 0;
    max_sizes[1] = 0;
}

Grid::Grid(int field_width, vector<vector<int>> hints[])
{
	Design::loadFonts();

    this->field_width = field_width;

	this->hints[0] = hints[0];
    this->hints[1] = hints[1];

	cell_states = vector<vector<int>>(field_width, vector<int>(field_width, 0));

    for (int i = 0; i < 2; ++i) 
    {
        max_sizes[i] = max_element(hints[i].begin(), hints[i].end(),
            [](const vector<int>& a, const vector<int>& b) { return a.size() < b.size(); })->size();
    }

	size.y = field_width + max_sizes[0]; //height
    size.x = field_width + max_sizes[1]; //width

    cell_size = Design::Window->getSize().x / (size.y * 1.7);

    center_pos.x = (Design::Window->getSize().x - size.x * cell_size) / 2.f;
    center_pos.y = (Design::Window->getSize().y - size.y * cell_size) / 2.f;

    cur_result[0] = vector<vector<int>>(field_width);
    cur_result[1] = vector<vector<int>>(field_width);

	incorrect[0] = vector<bool>(field_width, false); //column
	incorrect[1] = vector<bool>(field_width, false); //row

    solved[0] = vector<bool>(field_width, false); //column
	solved[1] = vector<bool>(field_width, false); //row
    
}

bool Grid::isSolved()
{
    for (int k = 0; k < 2; k++)
    {
        for (const vector<int>& vec : cur_result[k]) 
        {
            if (find(vec.begin(), vec.end(), 0) != vec.end()) 
				return false;
        }
    }

    for (int i = 0; i < field_width; i++)
    {
        vector<int> col = cur_result[0][i];
        vector<int> row = cur_result[1][i];

        reverse(col.begin(), col.end());
        reverse(row.begin(), row.end());

        if (col != hints[0][i] || row != hints[1][i]) return false;
    }
    return true;
}

void Grid::isRowOrColumnSolved(int x, int y)
{
    {
        vector<int> col = cur_result[0][x];
        vector<int> hint_col = hints[0][x];
        reverse(col.begin(), col.end());
        bool matched = (col == hint_col);
        solved[0][x] = matched;

        if (matched)
        {
            for (int i = 0; i < field_width; i++)
            {
                if (cell_states[i][x] == 0) cell_states[i][x] = 2;
            }
        }
    }

    {
        vector<int> row = cur_result[1][y];
        vector<int> hint_row = hints[1][y];
        reverse(row.begin(), row.end());
        bool matched = (row == hint_row);
        solved[1][y] = matched;

        if (matched)
        {
            for (int j = 0; j < field_width; j++)
            {
                if (cell_states[y][j] == 0) cell_states[y][j] = 2;
            }
        }
    }
}



// Check if the maximum value in the result exceeds the hint
bool Grid::maxExceedsHint (const vector<int>& result, const vector<int>& hint)
{
    if (result.empty()) return false;
    int max_result = *max_element(result.begin(), result.end());
    int max_hint = hint.empty() ? 0 : *max_element(hint.begin(), hint.end());
    return max_result > max_hint;
}

void Grid::compareResultWithHints()
{
    for (int i = 0; i < field_width; i++)
    {
        incorrect[0][i] = maxExceedsHint(cur_result[0][i], hints[0][i]); // стовпчик
        incorrect[1][i] = maxExceedsHint(cur_result[1][i], hints[1][i]); // рядок
    }
}

 
void Grid::resultUpdate(int grid_x, int grid_y)
{
    int count = 0;

	// Update column
    cur_result[0][grid_x].clear();
    for (int i = 0; i < field_width; i++)
    {
        if (cell_states[i][grid_x] == 1)
            count++;
        else if (count > 0)
        {
            cur_result[0][grid_x].push_back(count);
            count = 0;
        }
    }
    if (count > 0)
        cur_result[0][grid_x].push_back(count);

	// Update row
    cur_result[1][grid_y].clear();
    count = 0;
    for (int j = 0; j < field_width; j++)
    {
        if (cell_states[grid_y][j] == 1)
            count++;
        else if (count > 0)
        {
            cur_result[1][grid_y].push_back(count);
            count = 0;
        }
    }
    if (count > 0)
        cur_result[1][grid_y].push_back(count);

    isRowOrColumnSolved(grid_x, grid_y);
}

void Grid::handleClick(Vector2i& mousePos, bool filled)
{
    int col = (mousePos.x - center_pos.x) / cell_size;
    int row = (mousePos.y - center_pos.y) / cell_size;

    if (row >= max_sizes[0] && row < size.y && col >= max_sizes[1] && col < size.x)
    {
        int grid_x = col - max_sizes[1];
        int grid_y = row - max_sizes[0];

        if (grid_x >= 0 && grid_x < field_width && grid_y >= 0 && grid_y < field_width)
        {
			if (cell_states[grid_y][grid_x] == 1 || cell_states[grid_y][grid_x] == 2)
				cell_states[grid_y][grid_x] = 0;
			else cell_states[grid_y][grid_x] = filled? 1 : 2;
        }
        resultUpdate(grid_x, grid_y);
    }
}

void Grid::draw()
{
    RectangleShape cell(Vector2f(cell_size, cell_size));

    Text text_hint;
    text_hint.setFont(Design::SecondFont);
    text_hint.setCharacterSize(cell_size * 0.8);
    text_hint.setFillColor(Design::HintTextColor);

    for (int i = 0; i < size.x; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            cell.setPosition(Vector2f(center_pos.x + i * cell_size, center_pos.y + j * cell_size));

            if (i < max_sizes[1] || j < max_sizes[0])
            {
	            cell.setFillColor(Design::HintCellColor);
                cell.setOutlineColor(Design::HintCellOutlineColor);
                cell.setOutlineThickness(3);
                Design::Window->draw(cell);
                text_hint.setString("");

            	if (i >= max_sizes[1] && j < max_sizes[0])
            	{
            		// Номер стовпця у верхніх підказках
            		int game_col_idx = i - max_sizes[1];
            		// Позиція елемента у стовпчику(знизу вгору)
            		int hint_num_pos = (max_sizes[0] - 1) - j;

            		if (game_col_idx >= 0 && game_col_idx < (int)hints[0].size() && hint_num_pos >= 0 &&
                        hint_num_pos < (int)hints[0][game_col_idx].size())
            		{
            			text_hint.setString(to_string(hints[0][game_col_idx][hint_num_pos]));

                        if (solved[0][game_col_idx]) text_hint.setFillColor(Design::HintSolvedTextColor);
                        else text_hint.setFillColor(Design::HintTextColor);
            		}
            		else text_hint.setString("");
            	}
            	else if (i < max_sizes[1] && j >= max_sizes[0])
            	{
            		// Номер стовпця у лівих підказках
            		int game_row_idx = j - max_sizes[0];
            		// Позиція елемента у рядку(справа на ліво)
            		int hint_num_pos = (max_sizes[1] - 1) - i;

            		if (game_row_idx >= 0 && game_row_idx < (int)hints[1].size() && hint_num_pos >= 0 &&
                        hint_num_pos < (int)hints[1][game_row_idx].size())
            		{
            			text_hint.setString(to_string(hints[1][game_row_idx][hint_num_pos]));

                        if (solved[1][game_row_idx]) text_hint.setFillColor(Design::HintSolvedTextColor);
                        else text_hint.setFillColor(Design::HintTextColor);
            		}
            		else text_hint.setString("");
            	}

            	//float text_hint_x = cell.getPosition().x + (cell_size - text_hint.getCharacterSize()) / 2.f;
            	//float text_hint_y = cell.getPosition().y + (cell_size - text_hint.getCharacterSize()) / 2.f;
                FloatRect text_hintBounds = text_hint.getLocalBounds();
                float text_hint_x = cell.getPosition().x + (cell_size - text_hintBounds.width) / 2.f - text_hintBounds.left;
                float text_hint_y = cell.getPosition().y + (cell_size - text_hintBounds.height) / 2.f - text_hintBounds.top - cell_size * 0.05f;
            	text_hint.setPosition(Vector2f(text_hint_x, text_hint_y)); 
                Design::Window->draw(text_hint);
            }
            else
            {
                int x = i - max_sizes[1];
                int y = j - max_sizes[0];

            	if (cell_states[y][x] == 1)
					cell.setFillColor(Design::FilledCellColor);
                else
                {
	                cell.setFillColor(Design::GameCellColor);

                	if (incorrect[0][x] || incorrect[1][y])
						cell.setFillColor(Design::IncorrectCellColor);
                }

                cell.setOutlineColor(Design::GridOutlineColor);
                cell.setOutlineThickness(2);
                Design::Window->draw(cell);

            	if (cell_states[y][x] == 2)
                {
                    Vertex line1[] = {
                        Vertex(Vector2f(cell.getPosition().x, cell.getPosition().y), Design::CrossColor),
                        Vertex(Vector2f(cell.getPosition().x + cell_size, cell.getPosition().y + cell_size), Design::CrossColor)
                    };
                    Vertex line2[] = {
                        Vertex(Vector2f(cell.getPosition().x + cell_size, cell.getPosition().y), Design::CrossColor),
                        Vertex(Vector2f(cell.getPosition().x, cell.getPosition().y + cell_size), Design::CrossColor)
                    };
                    Design::Window->draw(line1, 2, Lines);
                    Design::Window->draw(line2, 2, Lines);
                }
            }
        }
    }

    Text enterText;
    enterText.setFont(Design::FirstFont);
    enterText.setString("Press ENTER \nto navigate");
    enterText.setCharacterSize(22);
    enterText.setFillColor( Design::TransparentGrayColor);
    FloatRect titleTextBounds = enterText.getLocalBounds();
    enterText.setOrigin(titleTextBounds.width / 2.f, titleTextBounds.height / 2.f);
    enterText.setPosition(Design::Window->getSize().x - 80, 30);
    Design::Window->draw(enterText);
}
