#ifndef PUBLISHER_H

#define PUBLISHER_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "user.h"
#include "exception.h"
#include "film.h"

class Network;


class Publisher : public User
{
public:
	Publisher(std::string Email, std::string Username, std::string Password, int Age, int UserID,
		std::vector<Film*>* ListOfFilms, bool Publisher = false);
	void RegisterFilm(Film* NewFilm);
	void EditFilmInformation(int FilmID, std::vector<std::string> Words);
	void DeleteFilm(Film* DeleteFilm);
	void ShowFollowers(int LastUserID);
	void ShowPublishedFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear,
		int FilmPrice, int FilmMaxYear, std::string FilmDirector);
	bool IsFilmForUser(Film* ChosenFilm);
	void ReplyComment(int FilmID, int CommentID, std::string Content);
	void DeleteComment(Film* ChosenFilm, int CommentID);
	std::vector<Film*> GetEligibleFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
		int FilmMaxYear, std::string FilmDirector);
private:
	std::vector<Film*>* ListOfFilms;
	std::vector<Film*> ListOfPublisherFilms;
};

#endif
