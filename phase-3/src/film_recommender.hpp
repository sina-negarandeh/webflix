#ifndef FILM_RECOMMENDER_H

#define FILM_RECOMMENDER_H

#include <iostream>
#include <vector>
#include <string>

class FilmRecommender
{
public:
	void AddFilm();
	void AddPurchasedFilm(int FilmID, std::vector<int> Films);
	std::vector<int > Sort(std::vector<int> Row);
	void SortByFrequency(std::vector<int>& Row, std::vector<int>& Sorted);
	void SortByFilmID(std::vector<int>& Row, std::vector<int>& Sorted);
	std::vector<int> GetRecommendation(int FilmID);
private:
	std::vector<std::vector<int>> ListOfFilms;
};

#endif

