#include "Game.h"

#include <iostream>

#include "Design.h"
#include "Grid.h"

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
            if (event.mouseButton.button == Mouse::Left) grid.handleClick(mousePos, true);
            else if (event.mouseButton.button == Mouse::Right) grid.handleClick(mousePos, false);
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
    grid.drawGrid();

    Design::Window->display();
}
