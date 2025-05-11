#include "Game.h"
#include <algorithm>

Game::Game()
{
	menu = Menu();
	state = GameState::StartMenu;
	style = GameStyle::LightPink;
    Design::applyStyle(style);
    grid_size = 5;
}

const bool Game::running() const
{
    return Design::Window->isOpen();
}

void Game::pollEvents(Grid& grid)
{
    Event event;
    while (Design::Window->pollEvent(event))
    {
        if (event.type == Event::Closed) Design::Window->close();

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) 
        {
            if (state == GameState::Game) 
            {
                state = GameState::NavigationMenu;
                menu.navMenu();
            }
        }
        if (event.type == Event::MouseButtonPressed)
        {
            Vector2i mousePos = Mouse::getPosition(*Design::Window);
            int result;
            if (state == GameState::StartMenu)
            {
                result = menu.handleClick(mousePos);
                if (result == 0)
                {
	                style = static_cast<GameStyle>(((int)style + 1) % 4);
                    Design::applyStyle(style);

                }
            	else if (result == 1) state = GameState::CategoryMenu;
                else if (result == 2) state = GameState::InfoMenu;
                else if (result == 3) Design::Window->close();
            }
            else if (state == GameState::InfoMenu)
            {
            	result = menu.handleClick(mousePos);
                if (result == 1)
                    state = GameState::StartMenu;
            }
            else if (state == GameState::CategoryMenu)
            {
                result = menu.handleClick(mousePos);
                if (result == 1)
                {
                    grid_size = 5;
                }
                else if (result == 2) grid_size = 10;
                else if (result == 3) grid_size = 15;
                state = GameState::NeedToGenerateGrid;
            }
            else if (state == GameState::NavigationMenu)
            {
            	result = menu.handleClick(mousePos);
                if (result == 1)
                {
                    state = GameState::Game;
                }
                else if (result == 2) state = GameState::CategoryMenu;
                else if (result == 3) state = GameState::StartMenu;
                
            }
            else if (state == GameState::WinningNavigationMenu)
            {
                result = menu.handleClick(mousePos);
                if (result == 1)
                {
                    state = GameState::CategoryMenu;
                }
                else if (result == 2) state = GameState::StartMenu;
                else if (result == 3) Design::Window->close();
            }
            else
            {
	            if (event.mouseButton.button == Mouse::Left) grid.handleClick(mousePos, true);
	            else if (event.mouseButton.button == Mouse::Right) grid.handleClick(mousePos, false);
            }
        }
    }
}

void Game::updateSelectedGrid()
{
    for (int i = 0; i <= 10; i += 5)
    {
        if (all_of(selected_grids + i, selected_grids + i + 5,[](int val) { return val == 1; }))
        	fill(selected_grids + i, selected_grids + i + 5, 0);
    }
}

void Game::update(Grid& grid)
{
    pollEvents (grid);
    grid.compareResultWithHints();

	//if all grids of catagory have been selected, reset them
    updateSelectedGrid();

    if (state == GameState::Game && grid.isSolved()) 
    {
		//solved_grids[selected_index] = 1;
        state = GameState::WinningNavigationMenu;
        menu.navMenu();
    }
}

void Game::render(Grid& grid)
{
    Design::Window->clear(Color(Design::BackgroundColor));

    //draw frames
	if (state == GameState::StartMenu || state == GameState::CategoryMenu || state == GameState::InfoMenu ) 
        menu.draw(state);
    else if (state == GameState::NavigationMenu || state == GameState::WinningNavigationMenu)
    {
        grid.draw();
        menu.draw(state);
    }
	else grid.draw();

    Design::Window->display();
}
