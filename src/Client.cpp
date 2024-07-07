
#include "Client.h"
#include "FileException.h"
//---------------------------------------------------------
// Constructor: Initializes Client with default values and attempts to connect to a server.
Client::Client():m_connected(false),m_server("192.168.1.24"),m_port(53000)
{
    if (m_socket.connect(m_server, m_port) == sf::Socket::Done) {
        std::cout << "Connected to server " << m_server << std::endl;
        m_connected = true;
    }
    else
    {
        throw FileException("Faild to conect to server");
    }
}
//---------------------------------------------------------
// Receives data from the server into a packet and processes it to update another player's state.
void Client::receiveData(MovingObject& ) {
    sf::Packet packet;

    if (m_socket.receive(packet) == sf::Socket::Done) {
        float key;
        packet >> key;
      //  otherPlayer.move(key);
    }
    packet.clear();
}
//---------------------------------------------------------
// Sends data (such as player's position) to the server in a packet.
void Client::sendData(MovingObject& Player) {
    sf::Packet packet;
    float key = 0;
    sf::Vector2f position = Player.getSprite().getPosition();
    packet << key;
    if (m_socket.send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send data to the server" << std::endl;
    }
}

Client::~Client()
{
}