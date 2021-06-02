#ifndef NETWORK_H

#define NETWORK_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include "user.h"
#include "customer.h"
#include "publisher.h"
#include "admin.h"
#include "film.h"
#include "exception.h"
#include "film_recommender.h"


class Network
{
public:
	Network();
	~Network();
	std::vector<std::string> GetWords(std::string CommandLine);
	void Signup(std::string CommandLine);
	bool IsUsernameDuplicate(std::string Username);
	void GetParametersForSignup(std::string CommandLine, std::string& Email, std::string& Username, std::string& Password,
		int& Age, bool& IsPublisher);
	void Login(std::string CommandLine);
	void GetParametersForLogin(std::string CommandLine, std::string& Username, std::string& Password);
	int GetUserID();
	int GetLastUserID();
	int GetFilmID();
	int GetLastFilmID();
	User* GetLoggedInUser();
	std::vector<Film*>* GetListOfFilms();
	std::vector<User*> GetUsers();
	void Search(std::string CommandLine);
	void GetParametersSearch(std::string CommandLine, std::string& FilmName, int& FilmMinRate, int& FilmMinYear,
		int& FilmPrice, int& FilmMaxYear, std::string& FilmDirector);
	void PurchaseFilm(std::string Command);
	void GetParameterForFindFilm(std::string CommandLine, int& FilmID);
	Film* FindFilm(int FilmID);
	User* FindPublisher(Film* PublisherFilm);
	void GetMoneyForPublisher(Film* ChosenFilm);
	User* FindPubliser(int UserID);
	int CalculatePublisherMoney(Film* ChosenFilm);
	void RateFilm(std::string Command);
	void GetParameterForRateFilm(std::string Command, int& FilmID, int& Score);
	void GivePublisherMoney();
	void AddCredit(std::string CommandLine);
	void GetParametersAddCredit(std::string CommandLine);
	void ShowPublishedFilms(std::string CommandLine);
	void GetParametersShowPublishedFilms(std::string CommandLine, std::string& FilmName, int& FilmMinRate,
		int& FilmMinYear, int& FilmPrice, int& FilmMaxYear, std::string& FilmDirector);
	void ShowPurchasedFilms(std::string CommandLine);
	void GetParametersShowPurchasedFilms(std::string CommandLine, std::string& FilmName, int& FilmMinRate,
		int& FilmMinYear, int& FilmPrice, int& FilmMaxYear, std::string& FilmDirector);
	void Comment(std::string CommandLine);
	void GetParametersComment(std::string CommandLine, int& FilmID, std::string& Content);
	void ReplyComment(std::string CommandLine);
	void GetParametersReplyComment(std::string CommandLine, int& FilmID, int&CommentID, std::string& Content);
	void ShowUnreadNotifications(std::string CommandLine);
	void ShowAllNotifications(std::string CommandLine);
	void GetParametersShowAllNotifications(std::string CommandLine, int&  Limit);
	void RegisterFilm(std::string CommandLine);
	void GetParametersForRegister(std::string CommandLine, std::string& Name, int& Year, int& Length, int& Price,
		std::string& Summary, std::string& Director);
	void DeleteFilm(std::string CommandLine);
	void GetParametersForDelete(std::string CommandLine);
	void ShowDetailsOfFilm(std::string CommandLine);
	void GetParametersForShowDetail(std::string CommandLine, int& FilmID);
	void RecommendFilms(int FilmID, std::vector<int> ListOfRecommendedFilms);
	void DeleteComment(std::string CommandLine);
	void GetParametersForDeleteComment(std::string CommandLine, int& FilmID, int& CommentID);
	void EditFilmInformation(std::string Command);
	void GetParametersForEdit(std::string CommandLine);
	void Follow(std::string CommandLine);
	void GetParametersForFollow(std::string CommandLine);
	void ShowFollowers();
	std::vector<Film*> GetEligibleFilms(std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
		int FilmMaxYear, std::string FilmDirector);
	bool IsEmailFormatCorrect(std::string EmailAddress);
	void Logout();
	void GetMoney();
private:
	int UserID = 1;
	int FilmID = 1;
	int Amount = 0;
	User* LoggedInUser = NULL;
	std::vector<User*> ListOfUsers;
	std::vector<Film*> ListOfFilms;
	std::map<User*, int> ListOfAmount;
	FilmRecommender* Graph;
};

#endif
