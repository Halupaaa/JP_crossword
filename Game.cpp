#include "Game.h"
#include <chrono>
#include <thread>
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

            switch (state)
            {
				case GameState::StartMenu:
	            {
					result = menu.handleClick(mousePos);
		            switch (result)
		            {
						case 0:
                        {
							style = static_cast<GameStyle>(((int)style + 1) % 4);
								Design::applyStyle(style);
								break;
                        }
						case 1: state = GameState::CategoryMenu; break;
						case 2: state = GameState::InfoMenu; break;
						case 3: Design::Window->close(); break;
                        default: break;
		            }
                    break;
	            }
				case GameState::InfoMenu:
				{
                    result = menu.handleClick(mousePos);
                    if (result == 1) state = GameState::StartMenu;
                    break;
				}
				case GameState::CategoryMenu:
                {
                    result = menu.handleClick(mousePos);
                    if (result != -1)
                    {
	                    switch (result)
	                    {
		                    case 1: grid_size = 5; break;
		                    case 2: grid_size = 10; break;
		                    case 3: grid_size = 15; break;
		                    default: break;
	                    }
                    	state = GameState::NeedToGenerateGrid;
                    }
                    break;
				}
                case GameState::NavigationMenu:
                {
                    result = menu.handleClick(mousePos);
                    switch (result)
                    {
	                    case 1: state = GameState::Game; break;
	                    case 2: state = GameState::CategoryMenu; break;
	                    case 3: state = GameState::StartMenu; break;
                        default: break;
                    }
                    break;
                }
                case GameState::WinningNavigationMenu:
                {
                    result = menu.handleClick(mousePos);
                    switch (result)
                    {
	                    case 1: state = GameState::CategoryMenu; break;
	                    case 2: state = GameState::StartMenu; break;
	                    case 3: Design::Window->close(); break;
                        default: break;
                    }
                    break;
                }
				default:
				{
                    if (event.mouseButton.button == Mouse::Left) grid.handleClick(mousePos, true);
                    else if (event.mouseButton.button == Mouse::Right) grid.handleClick(mousePos, false);
					break;
				}
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

    static int solveCounter = 0;
    if (state == GameState::Game && grid.isSolved()) 
    {
        solveCounter++;
        if (solveCounter == 2)
        {
            this_thread::sleep_for(chrono::milliseconds(1000));
            state = GameState::WinningNavigationMenu;
            menu.navMenu();
            solveCounter++;
        }
	    
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
