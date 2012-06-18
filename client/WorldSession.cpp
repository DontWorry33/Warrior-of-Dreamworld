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
#include "WorldSession.h"
#include "Opcodes.h"
#include "Defines.h"
#include "Game.h"
#include <cassert>

WorldSession::WorldSession(Game* pGame) : 
NetworkThread(&WorldSession::RecievePackets, this),
pGame(pGame)
{
}

void WorldSession::ConnectToServer()
{
    assert(Socket.connect(sf::IpAddress::getLocalAddress(), 0xBEEF) == sf::Socket::Done);
}

void WorldSession::RecievePackets()
{
    sf::Uint16 Opcode;
    sf::Packet Packet;

    while(true)
    {
        sf::Socket::Status Status;
        do
        {
            Status = Socket.receive(Packet);
        } while(Status != sf::Socket::Status::Done);

        Packet >> Opcode;
        if(Opcode > MSG_COUNT)
            printf("Opcode > MSG_COUNT.\n");
            
        (this->*OpcodeTable[Opcode].Handler)(Packet);
        Packet.clear();
    }
}

void WorldSession::SendPacket(sf::Packet& Packet)
{
    GlobalMutex.lock();

    Socket.send(Packet);

    GlobalMutex.unlock();
}

void WorldSession::HandleLoginOpcode(sf::Packet& Packet)
{
    Uint16 Status;
    Packet >> Status;

    printf("Recieved: MSG_LOGIN: %u\n", Status);

    if(Status != LOGIN_SUCCESS)
    {
        printf("Login fail\n");
        Socket.disconnect();
        return;
    }

    Uint16 MapID, x, y;
    
    Packet >> MapID >> x >> y;
    std::cout << MapID << " " << x << " " << y;

    if(!Packet.endOfPacket())
    {
        Socket.disconnect();
        printf("Invalid packet: too big");
        return;
    }

    printf("Packet is good!\n");
    World* pWorld = new World(this);
    pWorld->pPlayer = new Player(x, y);
    pWorld->LoadTileMap(MapID);
    pGame->ChangeState(pWorld);
}