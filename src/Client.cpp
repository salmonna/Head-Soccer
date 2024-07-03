
#include "Client.h"
#include "FileException.h"

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

void Client::receiveData(MovingObject& otherPlayer) {
    sf::Packet packet;

    if (m_socket.receive(packet) == sf::Socket::Done) {
        float key;
        packet >> key;
      //  otherPlayer.move(key);
    }
    packet.clear();
}

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