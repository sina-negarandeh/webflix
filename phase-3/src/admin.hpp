#ifndef ADMIN_H

#define ADMIN_H

#include <iostream>
#include <vector>
#include <string>
#include "exception.hpp"
#include "film.hpp"
#include "user.hpp"

class Admin : public User
{
public:
	Admin(std::string Email, std::string Username, std::string Password, int Age, int UserID, bool Publisher, int* InputNetworkMoney);
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
	void RegisterFilm(Film* NewFilm);
	void EditFilmInformation(int FilmID, std::vector<std::string> Words);
	void DeleteFilm(Film* DeleteFilm);
	void ShowFollowers(int LastUserID);
	void ReplyComment(int FilmID, int CommentID, std::string Content);
	void DeleteComment(Film* ChosenFilm, int CommentID);
	void ShowPublishedFilms(int LastFilmID, std::string FilmName, int FilmMinRate,
		int FilmMinYear, int FilmPrice, int FilmMaxYear, std::string FilmDirector);
	bool IsFilmForUser(Film* ChosenFilm);
	std::vector<Film*> GetEligibleFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
		int FilmMaxYear, std::string FilmDirector);
	int GetMoney();
private:
	int* NetworkMoney;
};

#endif

