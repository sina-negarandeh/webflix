#include "film_recommender.h"

void FilmRecommender::AddFilm()
{
	if (ListOfFilms.size())
	{
		for (int Counter = 0; Counter < ListOfFilms.size(); Counter++)
			ListOfFilms[Counter].push_back(0);
		std::vector<int> List(ListOfFilms.size() + 1, 0);
		ListOfFilms.push_back(List);
	}
	else
	{
		std::vector<int> List(1,0);
		ListOfFilms.push_back(List);
	}
}

std::vector<int > FilmRecommender::Sort(std::vector<int> Row)
{

		std::vector<int> Sorted;
			for (int Counter = 0; Counter < Row.size(); Counter++)
				Sorted.push_back(Counter + 1);

		for (int FirstCounter = Row.size() -1; 0 <= FirstCounter; FirstCounter--)
		{
			int Min = FirstCounter;
			for (int SecondCounter = FirstCounter - 1; 0 <= SecondCounter; SecondCounter--)
				if (Row[Min] > Row[SecondCounter])
				{
					int SecondTemp = Sorted[Min];
					Sorted[Min] = Sorted[SecondCounter];
					Sorted[SecondCounter] = SecondTemp;
				
					int Temp = Row[Min];
					Row[Min] = Row[SecondCounter];
					Row[SecondCounter] = Temp;

					Min = SecondCounter;
				}
		}
		
		for (int FirstCounter = Row.size() -1; 0 <= FirstCounter; FirstCounter--)
		{
			int Min = FirstCounter;
			for (int SecondCounter = FirstCounter - 1; 0 <= SecondCounter; SecondCounter--)
				if (Row[Min] == Row[SecondCounter] && Sorted[Min] < Sorted[SecondCounter])
				{
					int SecondTemp = Sorted[Min];
					Sorted[Min] = Sorted[SecondCounter];
					Sorted[SecondCounter] = SecondTemp;
				
					int Temp = Row[Min];
					Row[Min] = Row[SecondCounter];
					Row[SecondCounter] = Temp;

					Min = SecondCounter;
				}
		}
		return Sorted;
}

void SortByFrequency(std::vector<int>& Row, std::vector<int>& Sorted)
{
	
}

void SortByFilmID(std::vector<int>& Row, std::vector<int>& Sorted)
{
	
}

void FilmRecommender::AddPurchasedFilm(int FilmID, std::vector<int> Films)
{
	if(Films.size() == 0)
		return;
	else
		for (int Counter = 0; Counter < Films.size(); Counter++)
			{
				ListOfFilms[Films[Counter] - 1][FilmID - 1]++;
				ListOfFilms[FilmID - 1][Films[Counter] -1]++;
			}
}

std::vector<int> FilmRecommender::GetRecommendation(int FilmID)
{
		int Row = FilmID - 1;
		return Sort(ListOfFilms[Row]);
}