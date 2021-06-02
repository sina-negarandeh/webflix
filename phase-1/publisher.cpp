#include "publisher.h"
#define NAME "name"
#define YEAR "year"
#define LENGTH "length"
#define SUMMARY "summary"
#define DIRECTOR "director"

Publisher::Publisher(std::string Email, std::string Username, std::string Password, int Age, int UserID, std::vector<Film*>* 
	InputListOfFilms, bool Publisher)
	: User(Email, Username, Password, Age, UserID, Publisher)
{
	ListOfFilms = InputListOfFilms;
}

void Publisher::RegisterFilm(Film* NewFilm)
{
	ListOfPublisherFilms.push_back(NewFilm);
	ListOfFilms->push_back(NewFilm);
	std::string NewNotification = "Publisher <publisher_name> with id " + std::to_string(GetUserID()) + " register new film.";
	std::vector<User*> ListOfFollowers = GetListOfFollowers();
	for (int Counter = 0; Counter < ListOfFollowers.size(); Counter++)
		ListOfFollowers[Counter]->GetNotification(NewNotification);
}

bool Publisher::IsFilmForUser(Film* ChosenFilm)
{
	for (int Counter = 0; ListOfPublisherFilms.size(); Counter++)
		if (ChosenFilm == ListOfPublisherFilms[Counter])
			return true;
	return false;
}

void Publisher::EditFilmInformation(int FilmID, std::vector<std::string> Words)
{
	Film* EditFilm = NULL;
	for (int Counter = 0; Counter < ListOfPublisherFilms.size(); Counter++)
		if (FilmID == ListOfPublisherFilms[Counter]->GetFilmID() && (*ListOfFilms)[Counter]->IsAvailable())
			EditFilm = ListOfPublisherFilms[Counter];

	if (EditFilm == NULL)
	{
		for (int Counter = 0; Counter < ListOfFilms->size(); Counter++)
			if (FilmID == (*ListOfFilms)[Counter]->GetFilmID() && (*ListOfFilms)[Counter]->IsAvailable())
				EditFilm = ListOfPublisherFilms[Counter];
		if (EditFilm != NULL)
			throw PermissionDenied();
		throw NotFound();
	}

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == NAME)
			EditFilm->SetName(Words[Counter + 1]);
		else if (Words[Counter] == YEAR)
			EditFilm->SetYear(stoi(Words[Counter + 1]));
		else if (Words[Counter] == LENGTH)
			EditFilm->SetLength(stoi(Words[Counter + 1]));
		else if (Words[Counter] == SUMMARY)
			EditFilm->SetSummary(Words[Counter + 1]);
		else if (Words[Counter] == DIRECTOR)
			EditFilm->SetDrictor(Words[Counter + 1]);
}

void Publisher::DeleteFilm(Film* DeleteFilm)
{
	int FilmID = DeleteFilm->GetFilmID();
	int Size = ListOfPublisherFilms.size();
	for (int Counter = 0; Counter < Size; Counter++)
		if ((DeleteFilm == ListOfPublisherFilms[Counter]) && (DeleteFilm->IsAvailable()))
		{
			DeleteFilm->Delete();
			return;
		}
	throw PermissionDenied();
}

void Publisher::ShowFollowers(int LastUserID)
{
	std::vector<User*> ListOfFollowers = GetListOfFollowers();
	std::cout << "List of Followers" << std::endl;
	std::cout << "#. User Id | User Username | User Email" << std::endl;
	for (int IDCounter = 1; IDCounter <= LastUserID; IDCounter++)
		for (int Counter = 0; Counter < ListOfFollowers.size(); Counter++)
			if(IDCounter == ListOfFollowers[Counter]->GetUserID())
				std::cout << (Counter + 1) << ". " << ListOfFollowers[Counter]->GetUserID() << " | " 
				<< ListOfFollowers[Counter]->GetUsername() << " | " << ListOfFollowers[Counter]->GetEmail() << std::endl;
}

void Publisher::ReplyComment(int FilmID, int CommentID, std::string Content)
{
	for (int Counter = 0; Counter < ListOfPublisherFilms.size(); Counter++)
		if (ListOfPublisherFilms[Counter]->GetFilmID() == FilmID && ListOfPublisherFilms[Counter]->IsAvailable())
			ListOfPublisherFilms[Counter]->AddReply(CommentID, Content);
}

void Publisher::DeleteComment(Film* ChosenFilm, int CommentID)
{
	for (int Counter = 0; Counter < ListOfPublisherFilms.size(); Counter++)
		if (ChosenFilm == ListOfPublisherFilms[Counter])
		{
			ChosenFilm->DeleteComment(CommentID);
			return;
		}
	throw PermissionDenied();
}

std::vector<Film*> Publisher::GetEligibleFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
	int FilmMaxYear, std::string FilmDirector)
{
	std::vector<Film*> ChosenFilms;
	for (int Counter = 0; Counter < ListOfPublisherFilms.size(); Counter++)
		if ((FilmName == ListOfPublisherFilms[Counter]->GetName() || FilmName == "") &&
			(FilmMinRate <= ListOfPublisherFilms[Counter]->GetRate() || FilmMinRate == -1))
				if ((FilmMinYear <= ListOfPublisherFilms[Counter]->GetYear() || FilmMinYear == 0) &&
					(FilmPrice == ListOfPublisherFilms[Counter]->GetPrice() || FilmPrice == -1))
						if ((ListOfPublisherFilms[Counter]->GetYear() <= FilmMaxYear || FilmMaxYear == 0) &&
							(FilmDirector == ListOfPublisherFilms[Counter]->GetDirector() || FilmDirector == "") &&
							(ListOfPublisherFilms[Counter]->IsAvailable()))
									ChosenFilms.push_back(ListOfPublisherFilms[Counter]);
	return ChosenFilms;
}

void Publisher::ShowPublishedFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
	int FilmMaxYear, std::string FilmDirector)
{
	std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
	std::vector<Film*> ChosenFilms = GetEligibleFilms(LastFilmID, FilmName, FilmMinRate , FilmMinYear, FilmPrice, FilmMaxYear, FilmDirector);
	
	for (int IDCounter = 1; IDCounter <= LastFilmID; IDCounter++)
		for (int Counter = 0; Counter < ChosenFilms.size(); Counter++)
			if (IDCounter == ChosenFilms[Counter]->GetFilmID())
			{
				Film* ChosenFilm = ChosenFilms[Counter];
				std::cout << (Counter + 1) << ". " << IDCounter << " | " << ChosenFilm->GetName() << " | " 
					<< ChosenFilm->GetLength() << " | " << ChosenFilm->GetPrice() << " | " << std::setprecision(2) << ChosenFilm->GetRate()
					<< " | " << ChosenFilm->GetYear() << " | " << ChosenFilm->GetDirector() << std::endl;
			}
}