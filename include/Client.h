

#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "gameObject/MovingObject.h"

class Client
{
public:
	Client();

	void receiveData(MovingObject& otherPlayer);
	void sendData(MovingObject& Player);

	~Client();

private:
	bool m_connected;
	sf::IpAddress m_server;
	unsigned short m_port;
	sf::TcpSocket m_socket;
};

