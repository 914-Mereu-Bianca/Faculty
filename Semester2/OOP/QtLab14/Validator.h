#pragma once
#include "Repository.h"
#include "Service.h"
#include "WatchList.h"

class Validator {

public:
	
	static void validate_movie_add(Repository *repo, const std::string name);

	static void validate_movie_add_watchlist(WatchList *wl, const std::string name);

	static void validate_movie(std::string number1, std::string number2);

	static void validate_movie_update(Repository *repo, std::string name);

	static void validate_movie_remove(Repository *repo, std::string name);

	static void validate_movie_remove_watchlist(WatchList *wl, std::string name);

	static void validate_movie_user_exists(Repository *repo, std::string name);

	static void validate_movie_user_add(Repository *repo, std::string name);

	static void validate_not_empty(Repository *repo, std::string name);
};