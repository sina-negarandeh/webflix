#include "user.h"

User::User(std::string InputEmail, std::string InputUsername, std::string InputPassword, int InputAge, int InputUserID, bool InputPublisher)
{
	Email = InputEmail;
	Username = InputUsername;
	Password = InputPassword;
	Age = InputAge;
	UserID = InputUserID;
	Publisher = InputPublisher;
}

std::string User::GetUsername()
{
	return Username;
}

std::string User::GetPasswrord()
{
	return Password;
}

std::string User::GetEmail()
{
	return Email;
}

int User::GetUserID()
{
	return UserID;
}

bool User::IsPublisher()
{
	return Publisher;
}

std::vector<User*> User::GetListOfFollowers()
{
	return ListOfFollowers;
}

void User::Follow(int ID, User* ChosenUser)
{
	ListOfFollowing.push_back(ChosenUser);
	ChosenUser->ListOfFollowers.push_back(this);
	std::string NewNotification = "User " + Username + " with id " + std::to_string(GetUserID()) + " follow you.";
	ChosenUser->GetNotification(NewNotification);
}

void User::AddCredit(int Money)
{
	Amount += Money;
}

bool User::DoesHaveThisFilm(Film* InputFilm)
{
	for (int Counter = 0; Counter < ListOfUserFilms.size(); Counter++)
		if (InputFilm == ListOfUserFilms[Counter])
			return true;
	return false;
}

int User::GiveMoney(int InputAmount)
{
	if (InputAmount > Amount)
		throw PermissionDenied();
	else
	{
		Amount -= InputAmount;
		return InputAmount;
	}
}

void User::AddFilm(Film* InputFilm)
{
	ListOfUserFilms.push_back(InputFilm);
}

std::vector<Film*> User::GetEligibleFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
	int FilmMaxYear, std::string FilmDirector)
{
	std::vector<Film*> ChosenFilms;
	for (int Counter = 0; Counter < ListOfUserFilms.size(); Counter++)
		if (FilmName == ListOfUserFilms[Counter]->GetName() || FilmName == "")
			if (FilmMinRate <= ListOfUserFilms[Counter]->GetRate() || FilmMinRate == -1)
				if (FilmMinYear <= ListOfUserFilms[Counter]->GetYear() || FilmMinYear == 0)
					if (FilmPrice == ListOfUserFilms[Counter]->GetPrice() || FilmPrice == -1)
						if (ListOfUserFilms[Counter]->GetYear() <= FilmMaxYear || FilmMaxYear == 0)
							if (FilmDirector == ListOfUserFilms[Counter]->GetDirector() || FilmDirector == "")
								ChosenFilms.push_back(ListOfUserFilms[Counter]);
	return ChosenFilms;

}

void User::ShowPurchasedFilms(int LastFilmID, std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice, int FilmMaxYear,
	std::string FilmDirector)
{
	std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
	std::vector<Film*> ChosenFilms = GetEligibleFilms(LastFilmID, FilmName, FilmMinRate, FilmMinYear, FilmPrice,
		FilmMaxYear, FilmDirector);
	for (int IDCounter = 1; IDCounter <= LastFilmID; IDCounter++)
		for (int Counter = 0; Counter < ChosenFilms.size(); Counter++)
			if (IDCounter == ChosenFilms[Counter]->GetFilmID())
			{
				Film* ChosenFilm = ChosenFilms[Counter];
				std::cout << (Counter + 1) << ". " << IDCounter << " | " << ChosenFilm->GetName() << " | " 
					<< ChosenFilm->GetLength() << " | " << ChosenFilm->GetPrice() << " | " << std::setprecision(2) << ChosenFilm->GetRate() << " | "
					<< ChosenFilm->GetYear() << " | " << ChosenFilm->GetDirector() << std::endl;
			}
}

void User::ShowUnreadNotifications()
{
	std::cout << "#. Notification Message" << std::endl;
	for (int Counter = (UnreadNotifications.size() - 1); 0 <= Counter; Counter--)
		std::cout << (UnreadNotifications.size() - Counter) << ". " << UnreadNotifications[Counter] << std::endl;

	UnreadNotifications.resize(0);
}

void User::ShowAllNotifications(int Limit)
{
	std::cout << "#. Notification Message" << std::endl;
	for (int Counter = (Notifications.size() - 1); (Notifications.size() - 1 - Limit) <= Counter; Counter--)
		std::cout << (Notifications.size() - Counter) << ". " <<  Notifications[Counter] << std::endl;
}

void User::GetNotification(std::string NewNotification)
{
	UnreadNotifications.push_back(NewNotification);
	Notifications.push_back(NewNotification);
}