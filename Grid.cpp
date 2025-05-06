#include "Grid.h"

#include <iostream>

#include "Design.h"

Grid::Grid():field_width(0), cell_size(0) {}

Grid::Grid(int field_width, vector<vector<int>> hints[])
{
    font.loadFromFile("fonts/MEDIO_VINTAGE.otf");

    this->field_width = field_width;

	this->hints[0] = hints[0];
    this->hints[1] = hints[1];

	cell_states = vector<vector<int>>(field_width, vector<int>(field_width, 0));

    for (int i = 0; i < 2; ++i) {
        max_sizes[i] = max_element(hints[i].begin(), hints[i].end(),
            [](const vector<int>& a, const vector<int>& b) {
                return a.size() < b.size();
            })->size();
    }

    height = field_width + max_sizes[0];
    width = field_width + max_sizes[1];

    cell_size = Design::Window->getSize().x / (height * 1.7);

	center_x = (Design::Window->getSize().x - width * cell_size) / 2.f;
	center_y = (Design::Window->getSize().y - height * cell_size) / 2.f;

    cur_result[0] = vector<vector<int>>(field_width);
    cur_result[1] = vector<vector<int>>(field_width);

    incorrect_columns = vector<bool>(field_width, false);
    incorrect_rows = vector<bool>(field_width, false);
}


bool Grid::isSolved()
{
    for (int i = 0; i < field_width; i++)
    {
        if (cur_result[0][i] != hints[0][i] && cur_result[1][i] != hints[1][i]) return false;
    }
    return true;
}

void Grid::compareResultWithHints()
{
    for (int i = 0; i < field_width; i++)
    {
        incorrect_columns[i] = (cur_result[0][i] > hints[0][i]);
        incorrect_rows[i] = (cur_result[1][i] > hints[1][i]);
    }
}

void Grid::resultUpdate(int grid_x, int grid_y)
{
    int count = 0;

    // Оновлення стовпця
    cur_result[0][grid_x].clear();
    for (int i = 0; i < field_width; ++i)
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

    // Оновлення рядка
    cur_result[1][grid_y].clear();
    count = 0;
    for (int j = 0; j < field_width; ++j)
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
}

void Grid::handleClick(Vector2i mousePos, bool filled)
{
    int col = (mousePos.x - center_x) / cell_size;
    int row = (mousePos.y - center_y) / cell_size;

    if (row >= max_sizes[0] && row < height && col >= max_sizes[1] && col < width)
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

void Grid::drawGrid()
{
    RectangleShape cell(Vector2f(cell_size, cell_size));

    Text text;
    text.setFont(font);
    text.setCharacterSize(cell_size * 0.8);
    text.setFillColor(Design::HintTextColor);

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            cell.setPosition(Vector2f(center_x + i * cell_size, center_y + j * cell_size));

            if (i < max_sizes[1] || j < max_sizes[0])
            {
	            cell.setFillColor(Design::HintCellColor);
                cell.setOutlineColor(Design::HintCellOutlineColor);
                cell.setOutlineThickness(3);
                Design::Window->draw(cell);

            	if (i >= max_sizes[1] && j < max_sizes[0])
            	{
            		// Номер стовпця у верхніх підказках
            		int top_el_col_indx = i - max_sizes[1];
            		// Позиція елемента у стовпчику(знизу вгору)
            		int top_el_col_pos = (max_sizes[0] - 1) - j;

            		if (top_el_col_indx >= 0 && top_el_col_indx < (int)hints[0].size() && top_el_col_pos >= 0 && 
                        top_el_col_pos < (int)hints[0][top_el_col_indx].size())
            		{
            			text.setString(to_string(hints[0][top_el_col_indx][top_el_col_pos]));
            		}
            		else text.setString("");
            	}
            	else if (i < max_sizes[1] && j >= max_sizes[0])
            	{
            		// Номер стовпця у лівих підказках
            		int left_el_row_indx = j - max_sizes[0];
            		// Позиція елемента у рядку(справа на ліво)
            		int left_el_row_pos = (max_sizes[1] - 1) - i;

            		if (left_el_row_indx >= 0 && left_el_row_indx < (int)hints[1].size() && left_el_row_pos >= 0 && 
                        left_el_row_pos < (int)hints[1][left_el_row_indx].size())
            		{
            			text.setString(to_string(hints[1][left_el_row_indx][left_el_row_pos]));
            		}
            		else text.setString("");
            	}

            	float text_x = cell.getPosition().x + (cell_size - text.getCharacterSize()) / 2.f;
            	float text_y = cell.getPosition().y + (cell_size - text.getCharacterSize()) / 2.f;
            	text.setPosition(Vector2f(text_x, text_y - 5.f)); 
                Design::Window->draw(text);
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

                	if (incorrect_columns[x] || incorrect_rows[y])
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
}

