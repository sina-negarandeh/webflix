#include "film.hpp"
#define LEFT_POINT_OF_INVERTAL 5
#define RIGHT_POINT_OF_INVERTAL 8

Film::Film(int InputPublisherID, int InputFilmID, std::string InputName, int InputYear, int InputLength, int InputPrice, 
	std::string InputSummary, std::string InputDirector)
{
	FilmID = InputFilmID;
	Name = InputName;
	Year = InputYear;
	Length = InputLength;
	Price = InputPrice;
	Summary = InputSummary;
	Director = InputDirector;
	PublisherID = InputPublisherID;
}

Film::~Film()
{
	for(int Counter = 0; Counter < ListOfComments.size(); Counter++)
		delete (ListOfComments[Counter]);
}

int Film::GetFilmID()
{
	return FilmID;
}

void Film::SetName(std::string InputName)
{
	Name = InputName;
}

void Film::SetYear(int InputYear)
{
	Year = InputYear;
}

void Film::SetLength(int InputLength)
{
	Length = InputLength;
}

void Film::SetSummary(std::string InputSummary)
{
	Summary = InputSummary;
}

void Film::SetDrictor(std::string InputDirector)
{
	Director = InputDirector;
}

bool Film::IsAvailable()
{
	return Available;
}

std::string Film::GetName()
{
	return Name;
}

void Film::Delete()
{
	Available = false;
}

float Film::GetRate()
{
	float Average = 0;
	for (int Counter = 0; Counter < ListOfRates.size(); Counter++)
		Average += ListOfRates[Counter];

	if (ListOfRates.size() == 0)
		return Average;
	else
		return (Average /= ListOfRates.size());
}

int Film::GetYear()
{
	return Year;
}

int Film::GetPrice()
{
	return Price;
}

std::string Film::GetDirector()
{
	return Director;
}

int Film::GetLength()
{
	return Length;
}

void Film::AddRate(int InputRate, int InputUserID)
{
	for (int Coutner = 0; Coutner < ListOfUsersWhoRate.size(); Coutner++)
		if (InputUserID == ListOfUsersWhoRate[Coutner])
		{
			ListOfRates[Coutner] = InputRate;
			return;
		}

	ListOfRates.push_back(InputRate);
	ListOfUsersWhoRate.push_back(InputUserID);
}

std::string Film::GetCondition()
{
	int AverageRate = GetRate();
	if (AverageRate < LEFT_POINT_OF_INVERTAL)
		return "Weak";
	else if (LEFT_POINT_OF_INVERTAL <= AverageRate < RIGHT_POINT_OF_INVERTAL)
		return "Average";
	else
		return "Strong";
}

int Film::GetPubisherID()
{
	return PublisherID;
}

int Film::GetCommentID()
{
	CommentID++;
	return (CommentID - 1);
}

void Film::AddComment(std::string Content, int UserID)
{
	Comment* NewCommemt = new Comment(Content, GetCommentID(), UserID);
	ListOfComments.push_back(NewCommemt);

}

Comment* Film::FindComment(int InputCommentID)
{
	for (int Counter = 0; Counter < ListOfComments.size(); Counter++)
		if (InputCommentID == ListOfComments[Counter]->GetCommentID() && ListOfComments[Counter]->IsAvailable())
			return ListOfComments[Counter];
	throw NotFound();
}

void Film::AddReply(int InputCommentID, std::string InputContent)
{	
	FindComment(InputCommentID)->GetListOfReplies()->push_back(InputContent);
}

int Film::FindUserIDForComment(int InputCommentID)
{
	return FindComment(InputCommentID)->GetUserID();
}

void Film::ShowDetails()
{
	
}

void Film::ShowComments()
{
	std::cout << "Comments" << std::endl;
	for (int Counter = 0; Counter < ListOfComments.size(); Counter++)
	{
		if (!ListOfComments[Counter]->IsAvailable())
			continue;
		std::cout << ListOfComments[Counter]->GetCommentID() << ". " << ListOfComments[Counter]->GetContent() << std::endl;
		ListOfComments[Counter]->ShowReplies();
	}
}

void Film::DeleteComment(int CommentID)
{
	Comment* ChosenComment = FindComment(CommentID);
	ChosenComment->Delete();
}

std::string Film::GetSummary()
{
	return Summary;
}

std::vector<std::string> Film::GetComments()
{
	std::vector<std::string> Comments;
	for (int Counter = 0; Counter < ListOfComments.size(); Counter++)
		Comments.push_back(ListOfComments[Counter]->GetContent());
	return Comments;
}