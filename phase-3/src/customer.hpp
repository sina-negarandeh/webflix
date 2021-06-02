#ifndef CUSTOMER_H

#define CUSTOMER_H

#include <vector>
#include <string>
#include "user.hpp"
#include "exception.hpp"

class Customer : public User
{
public:
	Customer(std::string Email, std::string Username, std::string Password, int Age, int UserID, bool Publisher = false);
	void RegisterFilm(Film* NewFilm);
	void EditFilmInformation(int FilmID, std::vector<std::string> Words);
	void DeleteFilm(Film* DeleteFilm);
	void ShowFollowers(int LastUserID);
	void ReplyComment(int FilmID, int CommentID, std::string Content);
	void DeleteComment(Film* ChosenFilm, int CommentID);
	void ShowPublishedFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
		int FilmMaxYear, std::string FilmDirector);
	bool IsFilmForUser(Film* ChosenFilm);
private:
};

#endif
