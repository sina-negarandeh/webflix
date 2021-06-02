#ifndef COMMANDHANDLER_H

#define COMMANDHANDLER_H

#include <iostream>
#include <string>
#include "network.hpp"

class CommandHandler
{
public:
	CommandHandler(Network* VirtualNetwork);
	void Run(std::string Line);
	std::string CorrectCommand(std::string Command);
	bool DoesItHaveError(std::string Command);
	bool DoesItHaveRequestError(std::string Command);
	bool DoesItHaveFindError(std::string Command, int LetterCounter, std::string Request);
	void RunCommand(std::string Command);
	int GetSessionID();
	Network* GetNetwork();
private:
	Network* VirtualNetwork;
};

#endif
