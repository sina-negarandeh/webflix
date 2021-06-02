#include <iostream>
#include <vector>
#include <string>
#include "handlers.hpp"
#include "my_server.hpp"
#include "network.hpp"
#include "command_handler.hpp"
using namespace std;

int main(int argc, char **argv) {
	Network VirtualNetwork;
	CommandHandler NetworkCommandHandler(&VirtualNetwork);
	try 
	{
	MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
		server.setNotFoundErrPage("static/404.html");
		server.get("/signup", new ShowPage("static/signup.html"));
		server.post("/signup", new SignupHandler(NetworkCommandHandler));
		server.get("/login", new ShowPage("static/login.html"));
		server.post("/login", new LoginHandler(NetworkCommandHandler));
		server.get("/home", new ShowHomeHandler(NetworkCommandHandler, "template/home.html"));
		server.get("/register", new ShowPage("static/register film.html"));
		server.post("/register", new RegisterHandler(NetworkCommandHandler));
		server.get("/logout", new LogoutHandler(NetworkCommandHandler));
		server.get("/profile", new ProfileHandler(NetworkCommandHandler, "template/profile.html"));
		server.get("/detail", new DetailHandler(NetworkCommandHandler, "template/detail.html"));
		server.get("/searchicon.png", new ShowImage("static/searchicon.png"));
		server.get("/delete", new DeleteHandler(NetworkCommandHandler));
		server.get("/buy", new BuyHandler(NetworkCommandHandler));
		server.get("/badrequest", new ShowPage("static/badrequest.html"));
		server.get("/notfound", new ShowPage("static/notfound.html"));
		server.get("/denied‬‬", new ShowPage("static/denied‬‬.html"));
		server.get("/", new ShowPage("static/home.html"));
		server.run();
	}
	catch (Server::Exception error)
	{
		cerr << error.getMessage() << endl;
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << endl;
	}
}