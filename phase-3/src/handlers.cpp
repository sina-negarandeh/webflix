#include "handlers.hpp"

using namespace std;

DeleteHandler::DeleteHandler(CommandHandler& InputNetworkCommandHandler)
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

Response *DeleteHandler::callback(Request *req) {
  try
  {
    if (req->getSessionId() == to_string(-1))
        throw exception();
    NetworkCommandHandler->GetNetwork()->SetLoggedInUser(stoi(req->getSessionId()));
    string FilmID = req->getQueryParam("filmid");
    string Command = "POST delete_films ? film_id " + FilmID;
    cout << Command << endl;
    NetworkCommandHandler->Run(Command);
  }
  catch (const std::exception& Error)
  {
    Response *res = Response::redirect("/404");
    return res;
  }
  Response *res = Response::redirect("/home");
  return res;
}

BuyHandler::BuyHandler(CommandHandler& InputNetworkCommandHandler)
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

Response *BuyHandler::callback(Request *req) {
  try
  {
    if (req->getSessionId() == to_string(-1))
        throw exception();
    NetworkCommandHandler->GetNetwork()->SetLoggedInUser(stoi(req->getSessionId()));
    string FilmID = req->getQueryParam("filmid");
    string Command = "POST buy ? film_id " + FilmID;
    NetworkCommandHandler->Run(Command);
  }
  catch (const std::exception& Error)
  {
    Response *res = Response::redirect("/denied‬‬");
    return res;
  }
  Response *res = Response::redirect("/profile");
  return res;
}

SignupHandler::SignupHandler(CommandHandler& InputNetworkCommandHandler)
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

Response *SignupHandler::callback(Request *Req)
{
  try
  {
    string Username = Req->getBodyParam("username");
    string Password = Req->getBodyParam("password");
    string Confirm = Req->getBodyParam("confirm");
    if (Password != Confirm)
      throw exception();
    int Age = stoi(Req->getBodyParam("age"));
    string Email = Req->getBodyParam("email");
    string Publisher = Req->getBodyParam("Publisher");
    if(Publisher == "")
      Publisher = "false";
    else
      Publisher = "true";
    string Command = "POST signup ? username " + Username + " password " + Password + " age " + to_string(Age) + " email " +
     Email + " publisher " + Publisher;
    NetworkCommandHandler->Run(Command);
  }
  catch (const std::exception& Error)
  {
    Response *res = Response::redirect("/badrequest");
    return res;
  }
  Response *res = Response::redirect("/home");
  res->setSessionId(to_string(NetworkCommandHandler->GetSessionID()));
  return res; 
}

LoginHandler::LoginHandler(CommandHandler& InputNetworkCommandHandler)
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

Response *LoginHandler::callback(Request *req) {
  try
  {
    string Username = req->getBodyParam("username");
    string Password = req->getBodyParam("password");
    string Command = "POST login ? username " + Username + " password " + Password;
    NetworkCommandHandler->Run(Command);
  }
  catch (const std::exception& Error)
  {
    Response *res = Response::redirect("/badrequest");
    return res;
  }
  Response *res = Response::redirect("/home");
  res->setSessionId(to_string(NetworkCommandHandler->GetSessionID()));
  return res;
}

ShowHomeHandler::ShowHomeHandler(CommandHandler& InputNetworkCommandHandler, string filePath) : TemplateHandler(filePath) 
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

map<string, string> ShowHomeHandler::handle(Request *req) {
  map<string, string> context;
  try
  {
    if (req->getSessionId() == to_string(-1))
        throw exception();
    NetworkCommandHandler->GetNetwork()->SetLoggedInUser(stoi(req->getSessionId()));
    std::vector<Film*> ListOfFilms = *NetworkCommandHandler->GetNetwork()->GetListOfFilms();
    for (int Counter = 0; (unsigned)Counter < ListOfFilms.size(); Counter++)
    {
      if (ListOfFilms[Counter]->IsAvailable() && (NetworkCommandHandler->GetNetwork()->GetLoggedInUser()->GetMoney() > ListOfFilms[Counter]->GetPrice()) && ListOfFilms[Counter]->IsAvailable() && !(NetworkCommandHandler->GetNetwork()->GetLoggedInUser()->DoesHaveThisFilm(ListOfFilms[Counter])))
        context[to_string(Counter)] = "<a href=/detail?filmid=" + to_string(ListOfFilms[Counter]->GetFilmID()) + ">" + "Name: " +
         ListOfFilms[Counter]->GetName() + " Length: " + to_string(ListOfFilms[Counter]->GetLength()) + " Price: " + 
         to_string(ListOfFilms[Counter]->GetPrice()) + " Rate: " +
          to_string(ListOfFilms[Counter]->GetRate()) + " Year: " + to_string(ListOfFilms[Counter]->GetYear()) + " Director: " +
           ListOfFilms[Counter]->GetDirector() + "</a>";
      else
        context[to_string(Counter)] = "";
    }
    context["size"] = to_string(ListOfFilms.size());

    int size = 0;
    if (NetworkCommandHandler->GetNetwork()->GetLoggedInUser()->IsPublisher())
    {
      std::vector<Film*> ListOfFilms = NetworkCommandHandler->GetNetwork()->GetLoggedInUser()->GetListPublisherFilms();
      size = ListOfFilms.size();
      context["director"] = req->getQueryParam("name");
      for (int Counter = 0; (unsigned)Counter < ListOfFilms.size(); Counter++)
        {
          if ((context["director"] == ListOfFilms[Counter]->GetDirector() || context["director"] == "") && ListOfFilms[Counter]->IsAvailable())
            {
              context[to_string(Counter + stoi(context["size"]))] = "<a href=/detail?filmid=" + to_string(ListOfFilms[Counter]->GetFilmID()) +
               ">" + "Name: " + ListOfFilms[Counter]->GetName() + " Length: " + to_string(ListOfFilms[Counter]->GetLength()) + " Price: " + 
               to_string(ListOfFilms[Counter]->GetPrice()) + " Rate: " +
                to_string(ListOfFilms[Counter]->GetRate()) + " Year: " + to_string(ListOfFilms[Counter]->GetYear()) +
                 " Director: " + ListOfFilms[Counter]->GetDirector() + "</a>" + " <a href=/delete?filmid=" +
                  to_string(ListOfFilms[Counter]->GetFilmID()) + ">Remove</a>";
            }
            else
              context[to_string(Counter + stoi(context["size"]))] = "";
        }
    }
    context["endsize"] = to_string(size);
  }
  catch (const std::exception& Error)
  {
    throw;
  }
  return context;
}

RegisterHandler::RegisterHandler(CommandHandler& InputNetworkCommandHandler)
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

Response *RegisterHandler::callback(Request *req) {
  try
  {
    if (req->getSessionId() == to_string(-1))
      throw exception();
    NetworkCommandHandler->GetNetwork()->SetLoggedInUser(stoi(req->getSessionId()));
    string Name = req->getBodyParam("name");
    int Length = stoi(req->getBodyParam("length"));
    int Price = stoi(req->getBodyParam("price"));
    int Year = stoi(req->getBodyParam("year"));
    string Director = req->getBodyParam("director");
    string Summary = req->getBodyParam("summary");
    string Command = "POST films ? name " + Name + " year " + to_string(Year) + " length " + to_string(Length) + " price " +
     to_string(Price) + " summary " + Summary + " director " + Director;
    NetworkCommandHandler->Run(Command);
  }
  catch (const std::exception& Error)
  {
    Response *res = Response::redirect("/denied‬‬");
    return res;
  }
  Response *res = Response::redirect("/home");
  return res;
}

LogoutHandler::LogoutHandler(CommandHandler& InputNetworkCommandHandler)
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

Response *LogoutHandler::callback(Request *req) {
  try
  {
    NetworkCommandHandler->GetNetwork()->SetLoggedInUser(stoi(req->getSessionId()));
    NetworkCommandHandler->GetNetwork()->Logout();
  }
  catch (const std::exception& Error)
  {
    Response *res = Response::redirect("badrequest");
    return res;
  }
  Response *res = Response::redirect("/login");
  res->setSessionId(to_string(-1));
  return res;
}

ProfileHandler::ProfileHandler(CommandHandler& InputNetworkCommandHandler, string filePath) : TemplateHandler(filePath) 
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

map<string, string> ProfileHandler::handle(Request *req) {
  map<string, string> context;
  NetworkCommandHandler->GetNetwork()->SetLoggedInUser(stoi(req->getSessionId()));
  std::vector<Film*> ListOfFilms = NetworkCommandHandler->GetNetwork()->GetLoggedInUser()->GetListOfUserFilms();
  for (int Counter = 0; (unsigned)Counter < ListOfFilms.size(); Counter++)
  {
    context[to_string(Counter)] = "Name: " + ListOfFilms[Counter]->GetName() + " Length: " + to_string(ListOfFilms[Counter]->GetLength()) +
     " Price: " +to_string(ListOfFilms[Counter]->GetPrice()) + " Rate: " +
      to_string(ListOfFilms[Counter]->GetRate()) + " Year: " + to_string(ListOfFilms[Counter]->GetYear()) + " Director: " +
       ListOfFilms[Counter]->GetDirector();
  }
  context["size"] = to_string(ListOfFilms.size());
  try
  {
    if (req->getSessionId() == to_string(-1))
      throw exception();
    context["amount"] = "0";
    context["amount"] = to_string(NetworkCommandHandler->GetNetwork()->GetMoney());
    string value = req->getQueryParam("money");
    int Amount = 0;
    if(value != "")
      Amount = stoi(value);
    string Command = "POST money ? amount " + to_string(Amount);
    NetworkCommandHandler->Run(Command);
  }
  catch (const std::exception& Error)
  {
    throw;
  }
  return context;
}

DetailHandler::DetailHandler(CommandHandler& InputNetworkCommandHandler, string filePath) : TemplateHandler(filePath) 
{
  NetworkCommandHandler = &InputNetworkCommandHandler;
}

map<string, string> DetailHandler::handle(Request *req) {
  map<string, string> context;
  context["form"] = "";
  try
  {
    if (req->getSessionId() == to_string(-1))
      throw exception();
    NetworkCommandHandler->GetNetwork()->SetLoggedInUser(stoi(req->getSessionId()));
    string ID = req->getQueryParam("filmid");
    string Score = req->getQueryParam("score");
    string Comment = req->getQueryParam("comment");
    static string LastID;
    req->setQueryParam("filmid", ID);
    if (ID != "")
      LastID = ID;
    if(ID != "")
    {
      Film* ChosenFilm = NetworkCommandHandler->GetNetwork()->GetFilm(stoi(ID));
      context["name"] = ChosenFilm->GetName();
      context["length"] = to_string(ChosenFilm->GetLength());
      context["price"] = to_string(ChosenFilm->GetPrice());
      context["rate"] = to_string(ChosenFilm->GetRate());
      context["year"] = to_string(ChosenFilm->GetYear());
      context["director"] = ChosenFilm->GetDirector();
      context["summary"] = ChosenFilm->GetSummary();
      if ((NetworkCommandHandler->GetNetwork()->GetLoggedInUser()->DoesHaveThisFilm(ChosenFilm)))
      {
        context["form"] = "<form action=\"/detail?filmid=" + req->getQueryParam("filmid") + "\">" + "<span>" +
                "<input type=\"number\" name=\"score\" placeholder=\"Rate\" required=\"Rate\"/>" +
                "</span>" +
                "<input type=\"submit\" />" +
            "</form>" +
            "<form action=\"/detail\">" +
                "<span>" +
                "<input type=\"text\" name=\"comment\" placeholder=\"Comment\" required=\"Comment\"/>" +
                "</span>" +
                "<input type=\"submit\" />" +
            "</form>";
      }
    }
    context["buy"] = "<a href=/buy?filmid=" + ID  + ">Buy</a>";
    if (Score != "")
    {
      string Command = "POST rate ? film_id " + LastID + " score " + Score;
      NetworkCommandHandler->Run(Command);
    }
    if(ID != "")
    {
      string Command = "GET films ? film_id " + LastID;
      std::vector<Film*> RecommendedList = NetworkCommandHandler->GetNetwork()->ShowDetailsOfFilm(Command);
      context["size"] = to_string(RecommendedList.size());
      for (int Counter = 0; (unsigned)Counter < RecommendedList.size(); Counter++)
      {
        if (RecommendedList[Counter]->IsAvailable())
          context[to_string(Counter)] = "<a href=/detail?filmid=" + to_string(RecommendedList[Counter]->GetFilmID()) + ">" +
           "Name: " + RecommendedList[Counter]->GetName() + " Length: " + to_string(RecommendedList[Counter]->GetLength()) +
             " Director: " + RecommendedList[Counter]->GetDirector() + "</a>";
        else
          context[to_string(Counter)] = "";
      }
    }
    else
      context["size"] = to_string(0);
    if(Comment != "")
    {
      string Command = "POST comments ? film_id " + LastID + " content " + Comment;
      NetworkCommandHandler->Run(Command);
    }
    context["endsize"] = to_string(0);
    if(ID != "")
    {
      Film* ChosenFilm = NetworkCommandHandler->GetNetwork()->GetFilm(stoi(ID));
      std::vector<string> ListOfComments = ChosenFilm->GetComments();
      for (int Counter = 0; (unsigned)Counter < ListOfComments.size(); Counter++)
        context[to_string(Counter + stoi(context["size"]))] = ListOfComments[Counter];
      context["endsize"] = to_string(ListOfComments.size());
    }
  }
  catch (const std::exception& Error)
  {
    throw;
  }
  return context;
}


