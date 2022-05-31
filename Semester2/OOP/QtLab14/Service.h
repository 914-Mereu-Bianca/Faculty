#pragma once
#include "Repository.h"
#include <vector>
#include "WatchList.h"
#include "Undo.h"
#include <memory>


class Service {

private:
	Repository *repository;
	WatchList *watch_list;

	std::vector<std::shared_ptr<UndoAction>> undo_action;
	std::vector<std::shared_ptr<UndoAction>> redo_action;

public:
	Service(Repository *r, WatchList *watch_list, std::vector<std::shared_ptr<UndoAction>> _undo_action, std::vector<std::shared_ptr<UndoAction>> _redo_action);
	Service(const Service& s);
	~Service();

	// This function creates a movie with the values from the parameters and adds it to the repository
	void addMovie(std::string title, std::string genre, std::string trailer, int likes, int year_of_release);

	// Returns the dyn vector from the repository
	std::vector<Movie> getMovies();

	// Returns the movie from the repo with the name from the parameters
	Movie getMovie(std::string nameMovie);

	// Removes the movie that has the name given in the parameter
	void serviceRemoveMovie(std::string nameMovie);

	// Updates the movie that has the name = nameMovie with the other parameters 
	void serviceUpdateMovie(std::string nameMovie, std::string title, std::string genre, std::string trailer, int likes, int year_of_release);

	// Returns a list that has only movies with the genre equal to the one from parametes
	std::vector<Movie> getGenreList(const std::string &genre) const;

	// This function creates a movie with the values from the parameters and adds it to the watch list
	void addToWatchList(std::string title, std::string genre, std::string trailer, int likes, int year_of_release);

	// Returns the dyn vector from the watch list
	std::vector<Movie> getWatchList();

	// Removes from the watch list the movie that has the name given in the parameter
	void removeFromWatchList(std::string nameMovie);

	// returns 1 if the movie is in the repo or 0 if it s not
	bool existMovie(std::string name);

	// returns 1 if the movie is in the watch list or 0 if it s not
	bool existMovieWatchList(std::string name);

	void set_filename(const std::string &filename);

	void set_filename_watchlist(const std::string &filename);

	void open_location();

	void undo();

	void redo();

};
