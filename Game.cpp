#include "Game.h"
#include "Design.h"
#include <iostream>


Game::Game()
{
	this->menu = Menu();
	this->menu_or_grid = 's';
}

const bool Game::running() const
{
    return Design::Window->isOpen();
}

//

void Game::pollEvents(Grid& grid)
{
    Event event;
    while (Design::Window->pollEvent(event))
    {
        if (event.type == Event::Closed) Design::Window->close();

        if (event.type == Event::MouseButtonPressed)
        {
            Vector2i mousePos = Mouse::getPosition(*Design::Window);
            if (menu_or_grid == 's' || menu_or_grid == 'n')
            {
                int result = menu.handleClick(mousePos);
                if (result == 1)
                {
	                menu_or_grid = 'g';
                }
                else if (result == 2) cout << "about info\n";
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

void Game::update(Grid& grid)
{
    pollEvents (grid);
    grid.compareResultWithHints();

}

void Game::render(Grid& grid)
{
    Design::Window->clear(Color(Design::BackgroundColor));

    //draw frames
	if (menu_or_grid == 's' || menu_or_grid == 'n') menu.draw(menu_or_grid);
	else grid.draw();

    Design::Window->display();
}
