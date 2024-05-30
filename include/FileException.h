#pragma once
#include <exception>
#include <string>

class FileException : public std::exception {
public:
	FileException(const std::string& msg) : m_msg(std::string("exception : ") + msg) {
	
	};

	const char* what() const {
		return m_msg.c_str();
	}

private:
	std::string m_msg;
};