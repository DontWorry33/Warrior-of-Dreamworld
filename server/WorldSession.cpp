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
#include "../client/Opcodes.h"
#include "World.h"

WorldSession::WorldSession()
{
}

void WorldSession::ReceivePackets()
{
    for(auto SocketIterator = Sockets.begin(); SocketIterator != Sockets.end(); ++SocketIterator)
    {
        pSocket = (*SocketIterator);
        while(pSocket->receive(Packet) == sf::Socket::Status::Done)
        {
            //Here we handle the packet
        }
    }
}