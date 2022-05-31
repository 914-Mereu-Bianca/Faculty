#include "Validator.h"
#include <iostream>
#include <cstring>
#include <ctype.h>
#include <algorithm>
#include <string.h>
#include <utility>
#include "Exceptions.h"

void Validator::validate_movie_add(Repository *repo, const std::string name)
{
	if (repo->movie_exists(name) == 1)
		throw ValueError("This movie already exists");
}

void Validator::validate_movie_add_watchlist(WatchList * wl, const std::string name)
{
	if (wl->movie_exists(name) == 1)
		throw ValueError("This movie already exists");
}

void Validator::validate_movie(std::string number1, std::string number2)
{
	if (number1.empty() || !std::all_of(number1.begin(), number1.end(), ::isdigit)) {
		throw ValueError("The number of likes is incorrect");
	}
	if (number2.empty() || !std::all_of(number2.begin(), number2.end(), ::isdigit)) {
		throw ValueError("The year of realease is incorrect");
	}

}

void Validator::validate_movie_update(Repository *repo, std::string name)
{
	if (repo->movie_exists(name) == 0)
		throw ValueError("The movie doesn't exist");
}

void Validator::validate_movie_remove(Repository *repo, std::string name)
{
	if (repo->movie_exists(name) == 0)
		throw ValueError("The movie doesn't exist");
}

void Validator::validate_movie_remove_watchlist(WatchList * wl, std::string name)
{
	if (wl->movie_exists(name) == 0)
		throw ValueError("The movie doesn't exist");
}

void Validator::validate_movie_user_exists(Repository *repo, std::string name)
{
	if (repo->movie_exists(name) == 0)
		throw ValueError("The movie doesn't exist");
}

void Validator::validate_movie_user_add(Repository *repo, const std::string name)
{
	if (repo->movie_exists(name) != 1)
		throw ValueError("This movie already exists");
}

void Validator::validate_not_empty(Repository * repo, std::string name)
{
	//if 
}
