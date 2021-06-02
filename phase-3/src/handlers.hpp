#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <iostream>
#include "command_handler.hpp"
#include "film.hpp"

class DeleteHandler : public RequestHandler
{
public:
	DeleteHandler (CommandHandler& InputNetworkCommandHandler);
	Response *callback(Request *);
private:
	CommandHandler* NetworkCommandHandler;
};

class BuyHandler : public RequestHandler
{
public:
	BuyHandler (CommandHandler& InputNetworkCommandHandler);
	Response *callback(Request *);
private:
	CommandHandler* NetworkCommandHandler;
};

class SignupHandler : public RequestHandler
{
public:
	SignupHandler (CommandHandler& InputNetworkCommandHandler);
	Response *callback(Request *);
private:
	CommandHandler* NetworkCommandHandler;
};

class LoginHandler : public RequestHandler {
public:
	LoginHandler (CommandHandler& InputNetworkCommandHandler);
 	Response *callback(Request *);
private:
	CommandHandler* NetworkCommandHandler;
};

class ShowHomeHandler : public TemplateHandler {
public:
  	ShowHomeHandler(CommandHandler& InputNetworkCommandHandler, std::string filePath);
  	std::map<std::string, std::string> handle(Request *req);
private:
	CommandHandler* NetworkCommandHandler;
};

class RegisterHandler : public RequestHandler {
public:
	RegisterHandler (CommandHandler& InputNetworkCommandHandler);
 	Response *callback(Request *);
private:
	CommandHandler* NetworkCommandHandler;
};

class LogoutHandler : public RequestHandler {
public:
	LogoutHandler (CommandHandler& InputNetworkCommandHandler);
 	Response *callback(Request *);
private:
	CommandHandler* NetworkCommandHandler;
};

class ProfileHandler : public TemplateHandler {
public:
  	ProfileHandler(CommandHandler& InputNetworkCommandHandler, std::string filePath);
  	std::map<std::string, std::string> handle(Request *req);
private:
	CommandHandler* NetworkCommandHandler;
};

class FilmHandler : public TemplateHandler {
public:
  	FilmHandler(CommandHandler& InputNetworkCommandHandler, std::string filePath);
  	std::map<std::string, std::string> handle(Request *req);
private:
	CommandHandler* NetworkCommandHandler;
};

class DetailHandler : public TemplateHandler {
public:
  	DetailHandler(CommandHandler& InputNetworkCommandHandler, std::string filePath);
  	std::map<std::string, std::string> handle(Request *req);
private:
	CommandHandler* NetworkCommandHandler;
};

#endif
