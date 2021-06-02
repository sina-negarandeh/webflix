#include "customer.hpp"

Customer::Customer(std::string Email, std::string Username, std::string Password, int Age, int UserID, bool Publisher)
	: User(Email, Username, Password, Age, UserID, Publisher)
{
	
}

void Customer::RegisterFilm(Film* NewFilm)
{
	throw PermissionDenied();
}

void Customer::EditFilmInformation(int FilmID, std::vector<std::string> Words)
{
	throw PermissionDenied();
}

void Customer::DeleteFilm(Film* DeleteFilm)
{
	throw PermissionDenied();
}

void Customer::ShowFollowers(int LastUserID)
{
	throw PermissionDenied();
}

void Customer::ReplyComment(int FilmID, int CommentID, std::string Content)
{
	throw PermissionDenied();
}

void Customer::DeleteComment(Film* ChosenFilm, int CommentID)
{ 
	throw PermissionDenied();
}

void Customer::ShowPublishedFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
	int FilmMaxYear, std::string FilmDirector)
{
	throw PermissionDenied();
}

bool Customer::IsFilmForUser(Film* ChosenFilm)
{
	return false;
}