#pragma once


class Command
{
public:
	Command();

	virtual void execute() = 0;


	virtual ~Command();

private:

};

Command::Command()
{
}

Command::~Command()
{
}