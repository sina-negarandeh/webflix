#include "network.h"
#define NAME "name"
#define YEAR "year"
#define LENGTH "length"
#define SUMMARY "summary"
#define DIRECTOR "director"
#define WEAK 0.8
#define AVERAGE 0.9
#define STRONG 0.95
#define USERNAME "username"
#define PASSWORD "password"
#define EMAIL "email"
#define AGE "age"
#define PUBLISHER "publisher"
#define TRUE "true"
#define MIN_RATE "min_rate"
#define MIN_YEAR "min_year"
#define PRICE "price"
#define MAX_YEAR "max_year"
#define FILM_ID "film_id"
#define SCORE "score"
#define AMOUNT "amount"
#define CONTENT "content"
#define COMMENT_ID "comment_id"
#define LIMIT "limit"
#define USER_ID "user_id"
#define QUESTION_MARK '?'

Network::Network()
{
	Admin* NewUser = new Admin("", "admin", "admin", 0, 0, false, &Amount);
	ListOfUsers.push_back(NewUser);
	Graph = new FilmRecommender;
}

Network::~Network()
{
	for(int Counter = 0; Counter < ListOfUsers.size(); Counter++)
		delete (ListOfUsers[Counter]);
	for(int Counter = 0; Counter < ListOfFilms.size(); Counter++)
		delete (ListOfFilms[Counter]);
	delete Graph;
}

std::vector<std::string> Network::GetWords(std::string CommandLine)
{
	std::vector<std::string> Words;

	int LetterCounter = 1;
	int FirstLetter = 0;

	std::string Word;

	while (LetterCounter <= CommandLine.size())
	{
		if (CommandLine[LetterCounter] == ' ' || LetterCounter == CommandLine.size())
		{
			Word = CommandLine.substr(FirstLetter, LetterCounter - FirstLetter);
			Words.push_back(Word);
			if (LetterCounter + 1 < CommandLine.size())
				FirstLetter = LetterCounter + 1;
		}
		LetterCounter++;
	}

	if ((Words.size() % 2) != 0)
	{
		throw BadRequest();
	}

	return Words;
}

void Network::Signup(std::string CommandLine)
{
	std::string Email = "";
	std::string Username = "";
	std::string Password = "";
	int Age = 0;
	bool IsPublisher = false;

	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersForSignup(CommandLine.substr(index + 1), Email, Username, Password, Age, IsPublisher);

	if (IsUsernameDuplicate(Username))
	{
		throw BadRequest();
	}

	if (IsPublisher == true)
	{
		Publisher* NewUser = new Publisher(Email, Username, Password, Age, GetUserID(), this->GetListOfFilms(), IsPublisher);
		ListOfUsers.push_back(NewUser);
		LoggedInUser = NewUser;
	}
	else
	{
		Customer* NewUser = new Customer(Email, Username, Password, Age, GetUserID(), IsPublisher);
		ListOfUsers.push_back(NewUser);
		LoggedInUser = NewUser;
	}
}

bool Network::IsUsernameDuplicate(std::string Username)
{
	for (int Counter = 0; Counter < ListOfUsers.size(); Counter++)
		if (Username == ListOfUsers[Counter]->GetUsername())
			return true;
	return false;
}

void Network::GetParametersForSignup(std::string CommandLine, std::string& Email, std::string& Username, std::string& Password,
	int& Age, bool& IsPublisher)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == USERNAME)
			Username = Words[Counter + 1];
		else if (Words[Counter] == PASSWORD)
			Password = Words[Counter + 1];
		else if (Words[Counter] == EMAIL)
			Email = Words[Counter + 1];
		else if (Words[Counter] == AGE)
			Age = stoi(Words[Counter + 1]);
		else if (Words[Counter] == PUBLISHER)
			if (Words[Counter + 1] == TRUE)
				IsPublisher = true;
			else
				IsPublisher = false;

	if (Email == "" || Username == "" || Password == "" || Age == 0)
		throw BadRequest();
	if (!IsEmailFormatCorrect(Email))
		throw BadRequest();
}

bool Network::IsEmailFormatCorrect(std::string EmailAddress)
{
	if (EmailAddress.size() < 1)
		return false;
	int index = EmailAddress.find('@');
	if (index < 1)
		return false;
	EmailAddress = EmailAddress.substr(index + 1);
	index = EmailAddress.find('.');
	if (index < 1)
		return false;
	EmailAddress = EmailAddress.substr(index + 1);
	if (EmailAddress.size() < 1)
		return false;
	return true;
}

void Network::Login(std::string CommandLine)
{
	std::string Username;
	std::string Password;

	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersForLogin(CommandLine.substr(index + 1), Username, Password);

	for (int Counter = 0; Counter < ListOfUsers.size(); Counter++)
		if (Username == ListOfUsers[Counter]->GetUsername() && Password == ListOfUsers[Counter]->GetPasswrord())
		{
			LoggedInUser = ListOfUsers[Counter];
			return;
		}
	throw BadRequest();
}

void Network::GetParametersForLogin(std::string CommandLine, std::string& Username, std::string& Password)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == USERNAME)
			Username = Words[Counter + 1];
		else if (Words[Counter] == PASSWORD)
			Password = Words[Counter + 1];

	if (Username == "" || Password == "")
		throw BadRequest();
}

int Network::GetUserID()
{
	UserID++;
	return (UserID - 1);
}

int Network::GetLastUserID()
{
	return (UserID - 1);
}

int Network::GetFilmID()
{
	if (LoggedInUser == NULL || !LoggedInUser->IsPublisher())
		return 0;
	FilmID++;
	return (FilmID - 1);
}

int Network::GetLastFilmID()
{
	return (FilmID - 1);
}

User* Network::GetLoggedInUser()
{
	return LoggedInUser;
}

std::vector<Film*>* Network::GetListOfFilms()
{
	return &ListOfFilms;
}

std::vector<User*> Network::GetUsers()
{
	return ListOfUsers;
}

std::vector<Film*> Network::GetEligibleFilms(std::string FilmName, int FilmMinRate, int FilmMinYear, int FilmPrice,
	int FilmMaxYear, std::string FilmDirector)
{
	std::vector<Film*>ChosenFilms;
	for (int Counter = 0; Counter < ListOfFilms.size(); Counter++)
		if (FilmName == ListOfFilms[Counter]->GetName() || FilmName == "")
			if (FilmMinRate <= ListOfFilms[Counter]->GetRate() || FilmMinRate == -1)
				if (FilmMinYear <= ListOfFilms[Counter]->GetYear() || FilmMinYear == 0)
					if (FilmPrice == ListOfFilms[Counter]->GetPrice() || FilmPrice == -1)
						if (ListOfFilms[Counter]->GetYear() <= FilmMaxYear || FilmMaxYear == 0)
							if (FilmDirector == ListOfFilms[Counter]->GetDirector() || FilmDirector == "")
								if (ListOfFilms[Counter]->IsAvailable())
									ChosenFilms.push_back(ListOfFilms[Counter]);
	return ChosenFilms;
}

void Network::Search(std::string CommandLine)
{
	std::string FilmName = "";
	int FilmMinRate = -1;
	int FilmMinYear = 0;
	int FilmPrice = -1;
	int FilmMaxYear = 0;
	std::string FilmDirector = "";

	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersSearch(CommandLine.substr(index + 1), FilmName, FilmMinRate, FilmMinYear, FilmPrice, FilmMaxYear, FilmDirector);

	std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
	std::vector<Film*>ChosenFilms = GetEligibleFilms(FilmName, FilmMinRate, FilmMinYear, FilmPrice, FilmMaxYear, FilmDirector);
	for (int IDCounter = 1; IDCounter <= GetLastFilmID(); IDCounter++)
		for (int Counter = 0; Counter < ChosenFilms.size(); Counter++)
			if (IDCounter == ChosenFilms[Counter]->GetFilmID())
			{
				Film* ChosenFilm = ChosenFilms[Counter];
				std::cout << (Counter + 1) << ". " << IDCounter << " | " << ChosenFilm->GetName() << " | " 
					<< ChosenFilm->GetLength() << " | " << ChosenFilm->GetPrice() << " | " << std::setprecision(2) << ChosenFilm->GetRate() 
					<< " | " << ChosenFilm->GetYear() << " | " << ChosenFilm->GetDirector() << std::endl;
			}
}

void Network::GetParametersSearch(std::string CommandLine, std::string& FilmName, int& FilmMinRate, int& FilmMinYear, int& FilmPrice,
	int& FilmMaxYear, std::string& FilmDirector)
{
	std::vector<std::string> Words = GetWords(CommandLine);
	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == NAME)
			FilmName = Words[Counter + 1];
		else if (Words[Counter] == MIN_RATE)
			FilmMinRate = stoi(Words[Counter + 1]);
		else if (Words[Counter] == MIN_YEAR)
			FilmMinYear = stoi(Words[Counter + 1]);
		else if (Words[Counter] == PRICE)
			FilmPrice = stoi(Words[Counter + 1]);
		else if (Words[Counter] == MAX_YEAR)
			FilmMaxYear = stoi(Words[Counter + 1]);
		else if (Words[Counter] == DIRECTOR)
			FilmDirector = Words[Counter + 1];
}

void Network::PurchaseFilm(std::string Command)
{
	int FilmID = 0;

	int index = Command.find(QUESTION_MARK);
	if (Command[index + 1] == ' ')
		index++;
	GetParameterForFindFilm(Command.substr(index + 1), FilmID);

	if (FilmID == 0)
		throw BadRequest();

	Film* ChosenFilm = FindFilm(FilmID);
	if (!LoggedInUser->DoesHaveThisFilm(ChosenFilm))
	{
		Amount += LoggedInUser->GiveMoney(ChosenFilm->GetPrice());
		LoggedInUser->AddFilm(ChosenFilm);
		GetMoneyForPublisher(ChosenFilm);
		std::string NewNotification = "User " + LoggedInUser->GetUsername() + " with id " + std::to_string(LoggedInUser->GetUserID())
		 + " buy your film " + ChosenFilm->GetName() + " with id " + std::to_string(ChosenFilm->GetFilmID()) + ".";
		FindPublisher(ChosenFilm)->GetNotification(NewNotification);
		Graph->AddPurchasedFilm(ChosenFilm->GetFilmID(), LoggedInUser->GetListOfOwnedFilm(ChosenFilm->GetFilmID()));
	}
}

User* Network::FindPublisher(Film* PublisherFilm)
{
	for (int Counter = 0; Counter < ListOfUsers.size(); Counter++)
		if (ListOfUsers[Counter]->IsFilmForUser(PublisherFilm))
			return ListOfUsers[Counter];
}

void Network::GetMoneyForPublisher(Film* ChosenFilm)
{
	User* FilmPublisher = FindPubliser(ChosenFilm->GetPubisherID());
	ListOfAmount[FilmPublisher] = CalculatePublisherMoney(ChosenFilm);
}

int Network::CalculatePublisherMoney(Film* ChosenFilm)
{
	std::string Condition = ChosenFilm->GetCondition();
	int Price = ChosenFilm->GetPrice();
	if (Condition == "Weak")
		return (Price * WEAK);
	else if (Condition == "Average")
		return (Price * AVERAGE);
	else
		return (Price * STRONG);

}

User* Network::FindPubliser(int UserID)
{
	for (int Counter = 0; Counter < ListOfUsers.size(); Counter++)
		if (UserID == ListOfUsers[Counter]->GetUserID())
			return ListOfUsers[Counter];
}

void Network::GetParameterForFindFilm(std::string CommandLine, int& FilmID)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == FILM_ID)
			FilmID = stoi(Words[Counter + 1]);

	if (FilmID == 0)
		throw NotFound();
}

Film* Network::FindFilm(int FilmID)
{
	Film* ChosenFilm = NULL;

	for (int Counter = 0; Counter < ListOfFilms.size(); Counter++)
		if (FilmID == ListOfFilms[Counter]->GetFilmID() && ListOfFilms[Counter]->IsAvailable())
			ChosenFilm = ListOfFilms[Counter];

	if (ChosenFilm == NULL)
		throw NotFound();

	return ChosenFilm;
}

void Network::RateFilm(std::string Command)
{
	int FilmID = 0;
	int Score = 0;

	int index = Command.find(QUESTION_MARK);
	if (Command[index + 1] == ' ')
		index++;
	GetParameterForRateFilm(Command.substr(index + 1), FilmID, Score);

	Film* ChosenFilm = FindFilm(FilmID);

	if (LoggedInUser->DoesHaveThisFilm(ChosenFilm))
	{
		ChosenFilm->AddRate(Score, LoggedInUser->GetUserID());
		std::string NewNotification = "User " + LoggedInUser->GetUsername() + " with id " + std::to_string(LoggedInUser->GetUserID())
		 + " rate your film " + ChosenFilm->GetName() + " with id " + std::to_string(ChosenFilm->GetFilmID()) + ".";
		FindPublisher(ChosenFilm)->GetNotification(NewNotification);
	}
	else
		throw PermissionDenied();
}

void Network::GetParameterForRateFilm(std::string CommandLine, int& FilmID, int& Score)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == FILM_ID)
			FilmID = stoi(Words[Counter + 1]);
		else if (Words[Counter] == SCORE)
			Score = stoi(Words[Counter + 1]);

	if (Score < 1 && 10 < Score)
		throw BadRequest();
	
	if (FilmID == 0)
		throw BadRequest();
}

void Network::GivePublisherMoney()
{
	int Money = ListOfAmount[LoggedInUser];
	ListOfAmount[LoggedInUser] = 0;
	Amount -= Money;
	LoggedInUser->AddCredit(Money);
}

void Network::AddCredit(std::string CommandLine)
{
	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersAddCredit(CommandLine.substr(index + 1));
}

void Network::GetParametersAddCredit(std::string CommandLine)
{
	int Money = -1;

	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == AMOUNT)
			Money = stoi(Words[Counter + 1]);

	if (Money < 0)
		throw BadRequest();

	LoggedInUser->AddCredit(Money);
}

void Network::ShowPublishedFilms(std::string CommandLine)
{
	std::string FilmName = "";
	int FilmMinRate = -1;
	int FilmMinYear = 0;
	int FilmPrice = -1;
	int FilmMaxYear = 0;
	std::string FilmDirector = "";

	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersShowPublishedFilms(CommandLine.substr(index + 1), FilmName, FilmMinRate, FilmMinYear, FilmPrice, FilmMaxYear, FilmDirector);

	LoggedInUser->ShowPublishedFilms(GetLastFilmID(), FilmName, FilmMinRate, FilmMinYear, FilmPrice, FilmMaxYear, FilmDirector);
}

void Network::GetParametersShowPublishedFilms(std::string CommandLine, std::string& FilmName, int& FilmMinRate, int& FilmMinYear,
	int& FilmPrice, int& FilmMaxYear, std::string& FilmDirector)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == NAME)
			FilmName = Words[Counter + 1];
		else if (Words[Counter] == MIN_RATE)
			FilmMinRate = stoi(Words[Counter + 1]);
		else if (Words[Counter] == MIN_YEAR)
			FilmMinYear = stoi(Words[Counter + 1]);
		else if (Words[Counter] == PRICE)
			FilmPrice = stoi(Words[Counter + 1]);
		else if (Words[Counter] == MAX_YEAR)
			FilmMaxYear = stoi(Words[Counter + 1]);
		else if (Words[Counter] == DIRECTOR)
			FilmDirector = Words[Counter + 1];
}

void Network::ShowPurchasedFilms(std::string CommandLine)
{
	std::string FilmName = "";
	int FilmMinRate = -1;
	int FilmMinYear = 0;
	int FilmPrice = -1;
	int FilmMaxYear = 0;
	std::string FilmDirector = "";

	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersShowPurchasedFilms(CommandLine.substr(index + 1), FilmName, FilmMinRate, FilmMinYear, FilmPrice, FilmMaxYear, FilmDirector);

	LoggedInUser->ShowPurchasedFilms(GetLastFilmID(), FilmName, FilmMinRate, FilmMinYear, FilmPrice, FilmMaxYear, FilmDirector);
}

void Network::GetParametersShowPurchasedFilms(std::string CommandLine, std::string& FilmName, int& FilmMinRate, int& FilmMinYear,
	int& FilmPrice, int& FilmMaxYear, std::string& FilmDirector)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == NAME)
			FilmName = Words[Counter + 1];
		else if (Words[Counter] == MIN_RATE)
			FilmMinRate = stoi(Words[Counter + 1]);
		else if (Words[Counter] == MIN_YEAR)
			FilmMinYear = stoi(Words[Counter + 1]);
		else if (Words[Counter] == PRICE)
			FilmPrice = stoi(Words[Counter + 1]);
		else if (Words[Counter] == MAX_YEAR)
			FilmMaxYear = stoi(Words[Counter + 1]);
		else if (Words[Counter] == DIRECTOR)
			FilmDirector = Words[Counter + 1];
}

void Network::Comment(std::string CommandLine)
{
	int FilmID = 0;
	std::string Content = "";
	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersComment(CommandLine.substr(index + 1), FilmID, Content);

	Film* ChosenFilm = FindFilm(FilmID);
	ChosenFilm->AddComment(Content, LoggedInUser->GetUserID());
	std::string NewNotification = "User " + LoggedInUser->GetUsername() + " with id " + std::to_string(LoggedInUser->GetUserID()) +
	 " comment on your film " + ChosenFilm->GetName() + " with id " + std::to_string(ChosenFilm->GetFilmID()) + ".";
	FindPublisher(ChosenFilm)->GetNotification(NewNotification);
}

void Network::GetParametersComment(std::string CommandLine, int& FilmID, std::string& Content)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == CONTENT)
			Content = Words[Counter + 1];
		else if (Words[Counter] == FILM_ID)
			FilmID = stoi(Words[Counter + 1]);

	if (FilmID == 0 || Content == "")
		throw BadRequest();
}

void Network::ReplyComment(std::string CommandLine)
{
	int FilmID = 0;
	int CommentID = 0;
	std::string Content = "";
	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersReplyComment(CommandLine.substr(index + 1), FilmID, CommentID, Content);

	LoggedInUser->ReplyComment(FilmID, CommentID, Content);

	Film* ChosenFilm = FindFilm(FilmID);

	std::string NewNotification = "Publisher " + LoggedInUser->GetUsername() + " with id " + std::to_string(LoggedInUser->GetUserID()) + 
	" reply to your comment.";
	
	for (int Counter = 0; Counter < ListOfUsers.size(); Counter++)
		if (ListOfUsers[Counter]->GetUserID() == ChosenFilm->FindUserIDForComment(CommentID))
			ListOfUsers[Counter]->GetNotification(NewNotification);
}

void Network::GetParametersReplyComment(std::string CommandLine, int& FilmID, int&CommentID, std::string& Content)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == CONTENT)
			Content = Words[Counter + 1];
		else if (Words[Counter] == FILM_ID)
			FilmID = stoi(Words[Counter + 1]);
		else if (Words[Counter] == COMMENT_ID)
			CommentID = stoi(Words[Counter + 1]);

	if (FilmID == 0 || CommentID == 0 || Content == "")
		throw BadRequest();
}

void Network::ShowUnreadNotifications(std::string CommandLine)
{
	LoggedInUser->ShowUnreadNotifications();
}

void Network::ShowAllNotifications(std::string CommandLine)
{
	int Limit = 0;

	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersShowAllNotifications(CommandLine.substr(index + 1), Limit);

	LoggedInUser->ShowAllNotifications(Limit);
}

void Network::GetParametersShowAllNotifications(std::string CommandLine, int&  Limit)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == LIMIT)
			Limit = stoi(Words[Counter + 1]);
	
	if (Limit == 0)
		throw BadRequest();
}

void Network::RegisterFilm(std::string CommandLine)
{
	std::string Name = "";
	int Year = 0;
	int Length = 0;
	int Price = -1;
	std::string Summary = "";
	std::string Director = "";

	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersForRegister(CommandLine.substr(index + 1), Name, Year, Length, Price, Summary, Director);

	if (LoggedInUser->IsPublisher())
	{
		Film* NewFilm = new Film(LoggedInUser->GetUserID(), GetFilmID(), Name, Year, Length, Price, Summary, Director);
		LoggedInUser->RegisterFilm(NewFilm);
		Graph->AddFilm();
	}
	else
		throw PermissionDenied();
}

void Network::GetParametersForRegister(std::string CommandLine, std::string& Name, int& Year, int& Length, int& Price,
	std::string& Summary, std::string& Director)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == NAME)
			Name = Words[Counter + 1];
		else if (Words[Counter] == YEAR)
			Year = stoi(Words[Counter + 1]);
		else if (Words[Counter] == LENGTH)
			Length = stoi(Words[Counter + 1]);
		else if (Words[Counter] == PRICE)
			Price = stoi(Words[Counter + 1]);
		else if (Words[Counter] == SUMMARY)
			Summary = Words[Counter + 1];
		else if (Words[Counter] == DIRECTOR)
			Director = Words[Counter + 1];

	if (Name == "" || Year == -1 || Length == 0 || Price == -1 || Summary == "" || Director == "")
		throw BadRequest();
}

void Network::DeleteFilm(std::string CommandLine)
{
	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersForDelete(CommandLine.substr(index + 1));
}

void Network::GetParametersForDelete(std::string CommandLine)
{
	int FilmID = 0;
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == FILM_ID)
			FilmID = stoi(Words[Counter + 1]);
	
	if (FilmID == 0)
		throw BadRequest();

	Film* DeleteFilm = FindFilm(FilmID);
	LoggedInUser->DeleteFilm(DeleteFilm);
}

void Network::ShowDetailsOfFilm(std::string CommandLine)
{
	int FilmID = 0;
	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersForShowDetail(CommandLine.substr(index + 1), FilmID);

	Film* ChosenFilm = FindFilm(FilmID);
	ChosenFilm->ShowDetails();
	RecommendFilms(FilmID, Graph->GetRecommendation(FilmID));
}

void Network::GetParametersForShowDetail(std::string CommandLine, int& FilmID)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == FILM_ID)
			FilmID = stoi(Words[Counter + 1]);

	if (FilmID == 0)
		throw BadRequest();
}

void Network::RecommendFilms(int FilmID, std::vector<int> ListOfRecommendedFilms)
{
	std::vector<Film*> RecommendedFilms; 
	for (int Counter = 0; Counter < ListOfRecommendedFilms.size(); Counter++)
		{
			try
			{
				Film* ChosenFilm = FindFilm(ListOfRecommendedFilms[Counter]);
				if (ChosenFilm->IsAvailable() && (!LoggedInUser->DoesHaveThisFilm(ChosenFilm)) 
					&& (ChosenFilm->GetFilmID() != FilmID))
				RecommendedFilms.push_back(ChosenFilm);
			}
			catch (const NotFound& error)
			{
				continue;
			}
		}

	std::cout << "Recommendation Film" << std::endl;
	std::cout << "#. Film Id | Film Name | Film Length | Film Director" << std::endl;
	for (int Counter = 0; (Counter < RecommendedFilms.size() && Counter < 4); Counter++)
	{
		Film* ChosenFilm = RecommendedFilms[Counter];
		std::cout << (Counter + 1) << ". " << ChosenFilm->GetFilmID() << " | " << ChosenFilm->GetName() << " | " << 
			ChosenFilm->GetLength() << " | " << ChosenFilm->GetDirector() << std::endl;
	}
}

void Network::DeleteComment(std::string CommandLine)
{
	int FilmID = 0;
	int CommentID = 0;
	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersForDeleteComment(CommandLine.substr(index + 1), FilmID, CommentID);

	Film* ChosenFilm = FindFilm(FilmID);

	LoggedInUser->DeleteComment(ChosenFilm, CommentID);
}

void Network::GetParametersForDeleteComment(std::string CommandLine, int& FilmID, int& CommentID)
{
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == FILM_ID)
			FilmID = stoi(Words[Counter + 1]);
		else if (Words[Counter] == COMMENT_ID)
			CommentID = stoi(Words[Counter + 1]);

	if (FilmID == 0 || CommentID == 0)
		throw BadRequest();
}

void Network::EditFilmInformation(std::string Command)
{
	int index = Command.find(QUESTION_MARK);
	if (Command[index + 1] == ' ')
		index++;
	GetParametersForEdit(Command.substr(index + 1));
}

void Network::GetParametersForEdit(std::string CommandLine)
{
	std::vector<std::string> Words = GetWords(CommandLine);
	int FilmID = 0;

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == FILM_ID)
			FilmID = stoi(Words[Counter + 1]);
	
	LoggedInUser->EditFilmInformation(FilmID, Words);
}

void Network::Follow(std::string CommandLine)
{
	int index = CommandLine.find(QUESTION_MARK);
	if (CommandLine[index + 1] == ' ')
		index++;
	GetParametersForFollow(CommandLine.substr(index + 1));
}

void Network::GetParametersForFollow(std::string CommandLine)
{
	int ID = 0;
	std::vector<std::string> Words = GetWords(CommandLine);

	for (int Counter = 0; Counter < Words.size(); Counter++)
		if (Words[Counter] == USER_ID)
			ID = stoi(Words[Counter + 1]);

	if (ID == 0)
		throw BadRequest();

	if (UserID == ID)
		throw PermissionDenied();

	for (int Counter = 0; Counter < ListOfUsers.size(); Counter++)
		if (ID == ListOfUsers[Counter]->GetUserID() && ListOfUsers[Counter]->IsPublisher())
		{
			LoggedInUser->Follow(ID, ListOfUsers[Counter]);
			return;
		}
	throw NotFound();
}

void Network::ShowFollowers()
{
	LoggedInUser->ShowFollowers(GetLastUserID());
}

void Network::Logout()
{
	if (LoggedInUser == NULL)
		throw BadRequest();
	LoggedInUser = NULL;
}

void Network::GetMoney()
{
	LoggedInUser->GetMoney();
}