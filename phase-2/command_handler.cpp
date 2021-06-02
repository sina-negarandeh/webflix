#include "command_handler.h"
#define QUESTION_MARK '?'
#define RESULT "OK"
#define SIGNUP_COMMAND "POST signup"
#define LOGIN_COMMAND "POST login"
#define REGISTER_FILM_COMMAND "POST films"
#define GET_DEATILS_OF_FILM_COMMAND "GET films ? film_id"
#define EDIT_FILM_COMMAND "POST put_films"
#define DELETE_FILM_COMMAND "POST delete_films"
#define FOLLOW_COMMAND "POST followers"
#define GET_FOLLOWERS_COMMAND "GET followers"
#define ADD_MONEY_COMMAND "POST money ?"
#define SEARCH_COMMAND "GET films"
#define BUY_COMMAND "POST buy"
#define RATE_COMMAND "POST rate"
#define GET_MONEY_COMMAND "POST money"
#define GET_PUBLISHED_COMMAND "GET published"
#define GET_PURCHASED_COMMAND "GET purchased"
#define POST_COMMENTS_COMMAND "POST comments"
#define GET_NOTIFICATIONS_COMMAND "GET notifications"
#define GET_ALL_NOTIFICATIONS_COMMAND "GET notifications read"
#define REPLY_COMMAND "POST replies"
#define DELETE_COMMENT_COMMAND "POST delete_comments"
#define POST "POST"
#define GET "GET"
#define SIGNUP_FOR_POST "signup"
#define LOGIN_FOR_POST "login"
#define FILMS_FOR_POST "films"
#define MONEY_FOR_POST "money"
#define REPLIES_FOR_POST "replies"
#define FOLLOWERS_FOR_POST "followers"
#define BUY_FOR_POST "buy"
#define RATE_FOR_POST "rate"
#define COMMENTS_FOR_POST "comments"
#define FOLLOWERS_FOR_GET "followers"
#define PUBLISHED_FOR_GET "published"
#define FILMS_FOR_GET "films"
#define PURCHASED_FOR_GET "purchased"
#define NOTIFICATIONS_FOR_GET "notifications"
#define NOTIFICATION_READ_FOR_GET "notifications read"
#define DELETE_FILMS_FOR_POST "delete_films"
#define DELETE_COMMENTS_FOR_POST "delete_comments"
#define PUT_FILMS_FOR_POST "put_films"
#define LOGOUT_FOR_POST "logout"
#define MONEY_FOR_GET "money"
#define LOGOUT_COMMAND "POST logout"
#define GET_MONEY "GET money"

CommandHandler::CommandHandler(Network* InputNetwork)
{
	VirtualNetwork = InputNetwork;
}

void CommandHandler::Run()
{
	std::string Line;

	while (getline(std::cin, Line))
		GetCommand(Line);
}

void CommandHandler::GetCommand(std::string Line)
{
	try
	{
		Line = CorrectCommand(Line);
		if (Line == "")
			return;
		if (DoesItHaveError(Line))
			return;
		RunCommand(Line);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what();
	}
}

std::string CommandHandler::CorrectCommand(std::string Command)
{
	if (Command.size() < 2)
		return "";

	for (int LetterCounter = 0; LetterCounter < Command.size(); LetterCounter++)
		if (Command[LetterCounter] == ' ' && Command[LetterCounter + 1] == ' ')
		{
			int SpaceCounter = 2;
			while (Command[LetterCounter + SpaceCounter] == ' ')
				SpaceCounter++;
			Command.erase(LetterCounter, SpaceCounter - 1);
		}

	if (Command[Command.size() - 1] == ' ')
		Command.erase((Command.size() - 1), 1);

	return Command;
}

bool CommandHandler::DoesItHaveError(std::string Command)
{
	if (DoesItHaveRequestError(Command))
		return true;

	return false;
}

bool CommandHandler::DoesItHaveRequestError(std::string Command)
{
	int LetterCounter = 1;
	while (Command[LetterCounter] != ' ')
		LetterCounter++;
	std::string Request = Command.substr(0, LetterCounter);
	if (Request != POST && Request != GET)
		throw BadRequest();
	if (DoesItHaveFindError(Command, LetterCounter, Request))
		throw NotFound();
	return false;
}

bool CommandHandler::DoesItHaveFindError(std::string Command, int LetterCounter, std::string Request)
{
	int FirstLetter = LetterCounter + 1;
	LetterCounter = 1;

	while (Command[FirstLetter + LetterCounter] != QUESTION_MARK && (FirstLetter + LetterCounter) < Command.size())
		LetterCounter++;

	std::string Order;

	if (Command[FirstLetter + LetterCounter] == QUESTION_MARK)
		Order = Command.substr(FirstLetter, LetterCounter - 1);
	else
		Order = Command.substr(FirstLetter, LetterCounter);

	if (Request == POST)
	{
		if (Order == SIGNUP_FOR_POST || Order == LOGIN_FOR_POST)
			return false;
		else if (Order == FILMS_FOR_POST || Order == MONEY_FOR_POST || Order == REPLIES_FOR_POST)
			return false;
		else if (Order == FOLLOWERS_FOR_POST || Order == BUY_FOR_POST || Order == RATE_FOR_POST || Order == COMMENTS_FOR_POST)
			return false;
		else if (Order == DELETE_FILMS_FOR_POST || Order == DELETE_COMMENTS_FOR_POST || Order == PUT_FILMS_FOR_POST)
			return false;
		else if (Order == LOGOUT_FOR_POST)
			return false;
	}
	else if (Request == GET)
	{
		if (Order == FOLLOWERS_FOR_GET || Order == PUBLISHED_FOR_GET)
			return false;
		else if (Order == FILMS_FOR_GET || Order == PURCHASED_FOR_GET || Order == NOTIFICATIONS_FOR_GET || Order == NOTIFICATION_READ_FOR_GET)
			return false;
		else if (Order == MONEY_FOR_GET)
			return false;
	}

	return true;
}

void CommandHandler::RunCommand(std::string Command)
{
	if (Command.substr(0, 11) == SIGNUP_COMMAND)
	{
		VirtualNetwork->Signup(Command);
		std::cout << RESULT << std::endl;
		return;
	}
	else if (Command.substr(0, 10) == LOGIN_COMMAND)
	{
		VirtualNetwork->Login(Command);
		std::cout << RESULT << std::endl;
		return;
	}
	else if (Command.substr(0, 11) == LOGOUT_COMMAND)
	{
		VirtualNetwork->Logout();
		std::cout << RESULT << std::endl;
		return;
	}

	User* LoggedInUser = VirtualNetwork->GetLoggedInUser();

	if (LoggedInUser == NULL)
		throw PermissionDenied();

	if (Command.substr(0, 10) == REGISTER_FILM_COMMAND)
		VirtualNetwork->RegisterFilm(Command);
	else if (Command.substr(0, 19) == GET_DEATILS_OF_FILM_COMMAND)
	{
		VirtualNetwork->ShowDetailsOfFilm(Command);
		return;
	}
	else if (Command.substr(0, 14) == EDIT_FILM_COMMAND)
		VirtualNetwork->EditFilmInformation(Command);
	else if (Command.substr(0, 17) == DELETE_FILM_COMMAND)
		VirtualNetwork->DeleteFilm(Command);
	else if (Command.substr(0, 14) == FOLLOW_COMMAND)
		VirtualNetwork->Follow(Command);
	else if (Command.substr(0, 13) == GET_FOLLOWERS_COMMAND)
	{
		VirtualNetwork->ShowFollowers();
		return;
	}
	else if (Command.substr(0, 12) == ADD_MONEY_COMMAND)
		VirtualNetwork->AddCredit(Command);
	else if (Command.substr(0, 9) == SEARCH_COMMAND)
	{
		VirtualNetwork->Search(Command);
		return;
	}
	else if (Command.substr(0, 8) == BUY_COMMAND)
		VirtualNetwork->PurchaseFilm(Command);
	else if (Command.substr(0, 9) == RATE_COMMAND)
		VirtualNetwork->RateFilm(Command);
	else if (Command.substr(0, 10) == GET_MONEY_COMMAND)
		VirtualNetwork->GivePublisherMoney();
	else if (Command.substr(0, 13) == GET_PUBLISHED_COMMAND)
	{
		VirtualNetwork->ShowPublishedFilms(Command);
		return;
	}
	else if (Command.substr(0, 13) == GET_PURCHASED_COMMAND)
	{
		VirtualNetwork->ShowPurchasedFilms(Command);
		return;
	}
	else if (Command.substr(0, 13) == POST_COMMENTS_COMMAND)
		VirtualNetwork->Comment(Command);
	else if (Command.substr(0, 17) == GET_NOTIFICATIONS_COMMAND)
	{
		VirtualNetwork->ShowUnreadNotifications(Command);
		return;
	}
	else if (Command.substr(0, 22) == GET_ALL_NOTIFICATIONS_COMMAND)
	{
		VirtualNetwork->ShowAllNotifications(Command);
		return;
	}
	else if (Command.substr(0, 12) == REPLY_COMMAND)
		VirtualNetwork->ReplyComment(Command);
	else if (Command.substr(0, 20) == DELETE_COMMENT_COMMAND)
		VirtualNetwork->DeleteComment(Command);
	else if (Command.substr(0, 9) == GET_MONEY)
	{
		VirtualNetwork->GetMoney();
		return;
	}
	std::cout << RESULT << std::endl;
}