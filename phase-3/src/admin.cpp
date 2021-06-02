#include "admin.hpp"

Admin::Admin(std::string Email, std::string Username, std::string Password, int Age, int UserID, bool Publisher, int* InputNetworkMoney)
	: User(Email, Username, Password, Age, UserID, Publisher)
{
	NetworkMoney = InputNetworkMoney;
}

std::string Admin::GetUsername()
{
	throw PermissionDenied();
}

std::string Admin::GetPasswrord()
{
	throw PermissionDenied();
}

std::string Admin::GetEmail()
{
	throw PermissionDenied();
}

int Admin::GetUserID()
{
	throw PermissionDenied();
}

bool Admin::IsPublisher()
{
	return false;
}

std::vector<User*> Admin::GetListOfFollowers()
{
	throw PermissionDenied();
}

void Admin::Follow(int ID, User* ChosenUser)
{
	throw PermissionDenied();
}

void Admin::AddCredit(int Money)
{
	throw PermissionDenied();
}

bool Admin::DoesHaveThisFilm(Film* InputFilm)
{
	return false;
}

int Admin::GiveMoney(int InputAmount)
{
	throw PermissionDenied();
}

void Admin::AddFilm(Film* InputFilm)
{
	throw PermissionDenied();
}

void Admin::ShowPurchasedFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear,
	int FilmPrice, int FilmMaxYear, std::string FilmDirector)
{
	throw PermissionDenied();
}

void Admin::GetNotification(std::string NewNotification)
{
	throw PermissionDenied();
}

void Admin::ShowUnreadNotifications()
{
	throw PermissionDenied();
}

void Admin::ShowAllNotifications(int Limit)
{
	throw PermissionDenied();
}

void Admin::RegisterFilm(Film* NewFilm)
{
	throw PermissionDenied();
}

void Admin::EditFilmInformation(int FilmID, std::vector<std::string> Words)
{
	throw PermissionDenied();
}

void Admin::DeleteFilm(Film* DeleteFilm)
{
	throw PermissionDenied();
}

void Admin::ShowFollowers(int LastUserID)
{
	throw PermissionDenied();
}

void Admin::ReplyComment(int FilmID, int CommentID, std::string Content)
{
	throw PermissionDenied();
}

void Admin::DeleteComment(Film* ChosenFilm, int CommentID)
{
	throw PermissionDenied();
}

void Admin::ShowPublishedFilms(int LastFilmID, std::string FilmName, int FilmMinRate,
	int FilmMinYear, int FilmPrice, int FilmMaxYear, std::string FilmDirector)
{
	throw PermissionDenied();
}

bool Admin::IsFilmForUser(Film* ChosenFilm)
{
	return false;
}

std::vector<Film*> Admin::GetEligibleFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
	int FilmMaxYear, std::string FilmDirector) {
	throw PermissionDenied();
}

int Admin::GetMoney()
{
	return *NetworkMoney;
}
