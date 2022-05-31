#include "WatchList.h"
#include "Exceptions.h"
#include "Validator.h"

WatchList::WatchList()
{
}

WatchList::~WatchList()
{
}

void WatchList::add(const Movie & movie)
{
	Validator::validate_movie_add_watchlist(this, movie.getTitle());
	this->watch_list.push_back(movie);
}

void WatchList::remove(std::string name)
{
	Validator::validate_movie_remove_watchlist(this, name);
	for (auto movie = this->watch_list.begin(); movie != this->watch_list.end(); movie++) {
		if (movie->getTitle() == name) {
			this->watch_list.erase(movie);
			break;
		}
	}
}

std::vector<Movie> WatchList::getAll()
{
	return this->watch_list;
}

bool WatchList::movie_exists(std::string name)
{
	for (auto &movie : this->watch_list) {
		if (movie.getTitle() == name)
			return 1;
	}
	return 0;
}
