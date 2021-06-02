#ifndef FILM_H

#define FILM_H

#include <iostream>
#include <vector>
#include <string>
#include "exception.hpp"
#include "comment.hpp"

class Film
{
public:
	Film(int PublisherID, int FilmID, std::string Name = "", int Year = 0, int Length = 0,
		int Price = 0, std::string Summary = "", std::string Director = "");
	~Film();
	int GetFilmID();
	void SetName(std::string Name);
	void SetYear(int Year);
	void SetLength(int Length);
	void SetSummary(std::string Summary);
	void SetDrictor(std::string Director);
	bool IsAvailable();
	void Delete();
	void AddRate(int InputRate, int InputUserID);
	float GetRate();
	int GetYear();
	int GetPrice();
	std::string GetDirector();
	int GetLength();
	std::string GetSummary();
	std::string GetCondition();
	int GetPubisherID();
	int GetCommentID();
	void AddComment(std::string Content, int UserID);
	void AddReply(int CommentID, std::string Content);
	int FindUserIDForComment(int InputCommentID);
	Comment* FindComment(int InputCommentID);
	void ShowDetails();
	void ShowComments();
	void DeleteComment(int CommentID);
	std::string GetName();
	std::vector<std::string> GetComments();
private:
	int FilmID;
	std::string Name;
	int Year;
	int Length;
	int Price;
	std::string Summary;
	std::string Director;
	bool Available = true;
	std::vector<int> ListOfRates;
	std::vector<int> ListOfUsersWhoRate;
	int PublisherID;
	int CommentID = 1;
	std::vector<Comment*> ListOfComments;
};

#endif
