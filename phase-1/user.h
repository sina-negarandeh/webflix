#ifndef USER_H

#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "exception.h"
#include "film.h"

class User
{
public:
	User(std::string Email, std::string Username, std::string Password, int Age, int UserID, bool Publisher = false);
	std::string GetUsername();
	std::string GetPasswrord();
	std::string GetEmail();
	int GetUserID();
	bool IsPublisher();
	std::vector<User*> GetListOfFollowers();
	void Follow(int ID, User* ChosenUser);
	void AddCredit(int Money);
	bool DoesHaveThisFilm(Film* InputFilm);
	int GiveMoney(int InputAmount);
	void AddFilm(Film* InputFilm);
	void ShowPurchasedFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, 
		int FilmPrice, int FilmMaxYear, std::string FilmDirector);
	void GetNotification(std::string NewNotification);
	void ShowUnreadNotifications();
	void ShowAllNotifications(int Limit);
	virtual void RegisterFilm(Film* NewFilm) = 0;
	virtual void EditFilmInformation(int FilmID, std::vector<std::string> Words) = 0;
	virtual void DeleteFilm(Film* DeleteFilm) = 0;
	virtual void ShowFollowers(int LastUserID) = 0;
	virtual void ReplyComment(int FilmID, int CommentID, std::string Content) = 0;
	virtual void DeleteComment(Film* ChosenFilm, int CommentID) = 0;
	virtual void ShowPublishedFilms(int LastFilmID, std::string FilmName, int FilmMinRate, 
		int FilmMinYear, int FilmPrice, int FilmMaxYear, std::string FilmDirector) = 0;
	virtual bool IsFilmForUser(Film* ChosenFilm) = 0;
	std::vector<Film*> GetEligibleFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
		int FilmMaxYear, std::string FilmDirector);
private:
	std::string Email;
	std::string Username;
	std::string Password;
	int Age;
	int UserID;
	bool Publisher;
	std::vector<User*> ListOfFollowing;
	std::vector<User*> ListOfFollowers;
	int Amount = 0;
	std::vector<Film*> ListOfUserFilms;
	std::vector<std::string> Notifications;
	std::vector<std::string> UnreadNotifications;
};

#endif
