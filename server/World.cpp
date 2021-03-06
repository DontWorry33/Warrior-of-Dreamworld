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
#include "World.h"
#include "AuthSession.h"

#define SERVER_HEARTHBEAT 50

World* pWorld;

World::World()
{
    for(int i=0; i < MAP_COUNT; ++i)
    {
        Maps.push_back(new Map);
    }

    pAuthSession = new AuthSession();
}

int World::Run()
{    
    sf::Clock Clock;

    //TODO: Load all

    while(true)
    {
        pAuthSession->HandleAll();

        for(auto SessionIterator = Sessions.begin(); SessionIterator != Sessions.end(); ++SessionIterator)
            (*SessionIterator)->ReceivePackets();

        if(Clock.getElapsedTime().asMilliseconds() < SERVER_HEARTHBEAT)
            sf::sleep(sf::milliseconds(SERVER_HEARTHBEAT - Clock.getElapsedTime().asMilliseconds()));

        Update(Clock.getElapsedTime().asMilliseconds());
        Clock.restart();
    }

    //TODO: Save all
}

void World::Update(Int32 diff)
{
    for(auto MapIterator = Maps.begin(); MapIterator != Maps.end(); ++MapIterator)
    {
        (*MapIterator)->Update(diff);
    }
}

void World::AddSession(sf::TcpSocket* pSocket, Player* pPlayer, Uint16 MapID)
{
    WorldSession* pWorldSession = new WorldSession(pSocket, pPlayer);
    pPlayer->BindSession(pWorldSession);
    Sessions.push_back(pWorldSession);
    Maps[MapID]->AddPlayer(pPlayer);
}