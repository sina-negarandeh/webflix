#include <iostream>
#include <vector>
#include <string>
#include "network.h"
#include "command_handler.h"
using namespace std;

int main()
{
	Network VirtualNetwork;
	CommandHandler NetworkCommandHandler(&VirtualNetwork);
	NetworkCommandHandler.Run();
	return 0;
}