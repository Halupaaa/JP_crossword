#include "Grid.h"
#include "Design.h"

#include <iostream>

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

	incorrect[0] = vector<bool>(field_width, false); //column
	incorrect[1] = vector<bool>(field_width, false); //row

}

bool Grid::isSolved()
{
    for (int i = 0; i < field_width; i++)
    {
        if (cur_result[0][i] != hints[0][i] && cur_result[1][i] != hints[1][i]) return false;
    }
    return true;
}

bool Grid::isRowOrColumnSolved(int x, int y)
{
    vector<int> col = cur_result[0][x];
    vector<int> row = cur_result[1][y];

    reverse(col.begin(), col.end());
    reverse(row.begin(), row.end());

    return col == hints[0][x] || row == hints[1][y];
}

void Grid::compareResultWithHints()
{
    auto compareAgainstReversedHintByMax = [](const vector<int>& result, const vector<int>& hint) -> bool {
        vector<int> reversed_hint = hint;
        reverse(reversed_hint.begin(), reversed_hint.end());

        vector<bool> used(reversed_hint.size(), false);

        for (int block : result)
        {
            bool matched = false;
            int max_val = -1;
            int max_idx = -1;

            // знайти найбільший ще не використаний елемент у reversed_hint, який >= block
            for (int i = 0; i < reversed_hint.size(); ++i)
            {
                if (!used[i] && reversed_hint[i] >= block && reversed_hint[i] > max_val)
                {
                    max_val = reversed_hint[i];
                    max_idx = i;
                }
            }

            if (max_idx != -1)
				used[max_idx] = true; // позначити як використаний
            else
            	return true; // немає відповідного — помилка
        }
        return false; // усе гаразд
    };

    for (int i = 0; i < field_width; i++)
    {
        incorrect[0][i] = compareAgainstReversedHintByMax(cur_result[0][i], hints[0][i]); // стовпці
        incorrect[1][i] = compareAgainstReversedHintByMax(cur_result[1][i], hints[1][i]); // рядки
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

    Text text_hint;
    text_hint.setFont(font);
    text_hint.setCharacterSize(cell_size * 0.8);
    text_hint.setFillColor(Design::HintTextColor);

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

            	if (cell_states[y][x] == 2 || isRowOrColumnSolved(x, y))
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

/*
void Grid::drawGrid()
{
    RectangleShape cell(Vector2f(cell_size, cell_size));

    text_hint text_hint_obj; // Renamed to avoid conflict with sf::text_hint if used as a type
    text_hint_obj.setFont(font);
    text_hint_obj.setCharacterSize(static_cast<unsigned int>(cell_size * 0.75f)); // Adjusted size slightly, ensure it's unsigned
    text_hint_obj.setFillColor(Design::Hinttext_hintColor);

    for (int i = 0; i < width; ++i) // `width` is total grid columns (game + left_hints_width)
    {
        for (int j = 0; j < height; ++j) // `height` is total grid rows (game + top_hints_height)
        {
            cell.setPosition(Vector2f(center_x + i * cell_size, center_y + j * cell_size));

            // Calculate coordinates relative to the game grid's top-left corner
            // These can be negative if (i,j) is in the hint area.
            int game_coord_x = i - max_sizes[1]; // max_sizes[1] is width of left hint area
            int game_coord_y = j - max_sizes[0]; // max_sizes[0] is height of top hint area

            if (i < max_sizes[1] || j < max_sizes[0]) // Current cell (i,j) is in a hint area or the corner
            {
                cell.setFillColor(Design::HintCellColor);
                cell.setOutlineColor(Design::HintCellOutlineColor);
                cell.setOutlineThickness(3);
                Design::Window->draw(cell);

                std::string current_hint_str = "";
                bool draw_cross_on_this_hint = false;

                if (i >= max_sizes[1] && j < max_sizes[0]) // Top hints area (for game columns)
                {
                    int game_col_idx = game_coord_x; // This is the actual game column index
                    int hint_num_pos = (max_sizes[0] - 1) - j; // Position of hint number in the vertical display

                    if (game_col_idx >= 0 && game_col_idx < field_width && // Check game_col_idx is valid
                        hints[0].size() > game_col_idx &&
                        hint_num_pos >= 0 && hint_num_pos < (int)hints[0][game_col_idx].size())
                    {
                        current_hint_str = to_string(hints[0][game_col_idx][hint_num_pos]);
                    }

                    // Check if the corresponding game column is solved
                    if (isRowOrColumnSolved(0, game_col_idx)) {
                        draw_cross_on_this_hint = true;
                    }
                }
                else if (i < max_sizes[1] && j >= max_sizes[0]) // Left hints area (for game rows)
                {
                    int game_row_idx = game_coord_y; // This is the actual game row index
                    int hint_num_pos = (max_sizes[1] - 1) - i; // Position of hint number in the horizontal display

                    if (game_row_idx >= 0 && game_row_idx < field_width && // Check game_row_idx is valid
                        hints[1].size() > game_row_idx &&
                        hint_num_pos >= 0 && hint_num_pos < (int)hints[1][game_row_idx].size())
                    {
                        current_hint_str = to_string(hints[1][game_row_idx][hint_num_pos]);
                    }

                    // Check if the corresponding game row is solved
                    if (isRowOrColumnSolved(game_row_idx, 0))
                    {
                        draw_cross_on_this_hint = true;
                    }
                }
                // Else, it's the top-left empty corner: current_hint_str remains "", draw_cross_on_this_hint remains false

                if (!current_hint_str.empty()) {
                    text_hint_obj.setString(current_hint_str);
                    // Center text_hint_obj in the cell
                    sf::FloatRect text_hintBounds = text_hint_obj.getLocalBounds();
                    float text_hint_x_pos = cell.getPosition().x + (cell_size - text_hintBounds.width) / 2.f - text_hintBounds.left;
                    float text_hint_y_pos = cell.getPosition().y + (cell_size - text_hintBounds.height) / 2.f - text_hintBounds.top - cell_size * 0.05f; // Small vertical adjustment
                    text_hint_obj.setPosition(text_hint_x_pos, text_hint_y_pos);
                    Design::Window->draw(text_hint_obj);
                }

                if (draw_cross_on_this_hint) {
                    Vertex line1[] = {
                        Vertex(Vector2f(cell.getPosition().x + cell_size * 0.1f, cell.getPosition().y + cell_size * 0.1f), Design::CrossColor),
                        Vertex(Vector2f(cell.getPosition().x + cell_size * 0.9f, cell.getPosition().y + cell_size * 0.9f), Design::CrossColor)
                    };
                    Vertex line2[] = {
                        Vertex(Vector2f(cell.getPosition().x + cell_size * 0.9f, cell.getPosition().y + cell_size * 0.1f), Design::CrossColor),
                        Vertex(Vector2f(cell.getPosition().x + cell_size * 0.1f, cell.getPosition().y + cell_size * 0.9f), Design::CrossColor)
                    };
                    Design::Window->draw(line1, 2, Lines);
                    Design::Window->draw(line2, 2, Lines);
                }
            }
            else // Game grid area
            {
                // Here, game_coord_x and game_coord_y are the 0-indexed coordinates for the game field.
                // They should be within [0, field_width-1] because of the loop bounds and the `else` condition.
                // For safety, an explicit check can be added, but it should hold true.
                // if (game_coord_x >= 0 && game_coord_x < field_width && game_coord_y >= 0 && game_coord_y < field_width)

                if (cell_states[game_coord_y][game_coord_x] == 1) { // Filled
                    cell.setFillColor(Design::FilledCellColor);
                }
                else { // Empty or crossed
                    cell.setFillColor(Design::GameCellColor); // Default for empty
                    // Check for incorrect row/column only if the cell isn't manually crossed out (state 2)
                    if (cell_states[game_coord_y][game_coord_x] != 2) {
                        if (incorrect[0][game_coord_x] || incorrect[1][game_coord_y]) {
                            cell.setFillColor(Design::IncorrectCellColor);
                        }
                    }
                }

                cell.setOutlineColor(Design::GridOutlineColor);
                cell.setOutlineThickness(2);
                Design::Window->draw(cell);

                if (cell_states[game_coord_y][game_coord_x] == 2 || isRowOrColumnSolved(game_coord_x, game_coord_y)) {
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

 */