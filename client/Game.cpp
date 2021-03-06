/*
Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
Copyright (C) 2012  Mislav Blazevic

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "Game.h"

Game::Game(bool FullScreen) :
CurrentState(NULL)
{
    Window.create(sf::VideoMode(WindowWidth, WindowHeight), "Warrior of Dreamworld", FullScreen ? sf::Style::Fullscreen : sf::Style::Close);
    Window.setFramerateLimit(60);
}

Game::~Game()
{
    delete CurrentState;
}

void Game::Run()
{
    sf::Event Event;

    while(Window.isOpen())
    {
        while(Window.pollEvent(Event))
        {
            CurrentState->HandleEvent(Event);
        }
        Session->RecievePackets();
        Window.clear();
        CurrentState->Draw();
        Window.display();
    }
}

void Game::ChangeState(GameState* NewState)
{
    delete CurrentState;
    CurrentState = NewState;
}