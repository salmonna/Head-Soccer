
#include "Client.h"


Client::Client():m_connected(false),m_server("127.0.0.1"),m_port(53000)
{
    if (m_socket.connect(m_server, m_port) == sf::Socket::Done) {
        std::cout << "Connected to server " << m_server << std::endl;
        m_connected = true;
    }
}

void Client::receiveData(MovingObject& otherPlayer) {
    sf::Packet packet;
    
    if (m_socket.receive(packet) == sf::Socket::Done) {
        float x, y;
        packet >> x >> y;
        otherPlayer.getSprite().setPosition(x, y);
    }
    packet.clear();

}

void Client::sendData(MovingObject& player) {
    sf::Packet packet;
    sf::Vector2f position = player.getSprite().getPosition();
    packet << position.x << position.y;
    if (m_socket.send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send data to the server" << std::endl;
    }
}

Client::~Client()
{
}