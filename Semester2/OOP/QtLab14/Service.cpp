#include "Service.h"
#include <vector>
#include <algorithm>
#include "Repository.h"
#include "Exceptions.h"
#include <memory>

Service::Service(Repository *r, WatchList *watch_list, std::vector<std::shared_ptr<UndoAction>> _undo_action, std::vector<std::shared_ptr<UndoAction>> _redo_action)
{
	this->repository = r;
	this->watch_list = watch_list;
	this->undo_action = _undo_action;
	this->redo_action = _redo_action;
}

Service::Service(const Service& s)
{
	this->repository = s.repository;
	this->watch_list = s.watch_list;
	this->undo_action = s.undo_action;
	this->redo_action = s.redo_action;
}

Service::~Service() {
	delete this->repository;
	delete this->watch_list;
}

void Service::addMovie(std::string title, std::string genre, std::string trailer, int likes, int year_of_release)
{
	Movie newMovie(title, genre, year_of_release, likes, trailer);
	repository->add(newMovie);
	this->undo_action.push_back(std::make_shared<UndoAdd>(*this->repository, newMovie));
	this->redo_action.clear();
}

std::vector<Movie> Service::getMovies() 
{
	return repository->getAll();
}

Movie Service::getMovie(std::string nameMovie) 
{
	std::vector<Movie> list = repository->getAll();
	for (auto &movie : list)
		if (movie.getTitle() == nameMovie)
			return movie;
}

void Service::serviceRemoveMovie(std::string nameMovie)
{
	Movie movie = this->getMovie(nameMovie);
	this->undo_action.push_back(std::make_shared<UndoRemove>(*this->repository, movie));
	this->redo_action.clear();

	repository->remove(nameMovie);
}

void Service::serviceUpdateMovie(std::string nameMovie, std::string title, std::string genre, std::string trailer, int likes, int year_of_release)
{
	Movie oldMovie = this->getMovie(nameMovie);
	Movie newMovie(title, genre, year_of_release, likes, trailer);
	
	this->undo_action.push_back(std::make_unique<UndoUpdate>(*this->repository, oldMovie, newMovie));
	this->redo_action.clear();

	repository->update(nameMovie, newMovie);

}

std::vector<Movie> Service::getGenreList(const std::string &genre) const 
{
	std::vector<Movie> movies = repository->getAll();

	std::vector<Movie> movies_list(movies.size());

	std::vector<Movie>::iterator it = copy_if(movies.begin(), movies.end(), movies_list.begin(),
		[&genre](Movie movie) {return genre == movie.getGenre(); });

	movies_list.resize(std::distance(movies_list.begin(), it));

	return movies_list;

}

void Service::addToWatchList(std::string title, std::string genre, std::string trailer, int likes, int year_of_release)
{
	Movie newMovie(title, genre, year_of_release, likes, trailer);
	watch_list->add(newMovie);
}

std::vector<Movie> Service::getWatchList()
{
	return this->watch_list->getAll();
}

void Service::removeFromWatchList(std::string nameMovie)
{
	watch_list->remove(nameMovie);
}

bool Service::existMovie(std::string name)
{
	return this->repository->movie_exists(name);
}

bool Service::existMovieWatchList(std::string name)
{
	return this->watch_list->movie_exists(name);
}

void Service::set_filename(const std::string &filename) {
	this->repository->set_file_name(filename);
	
}

void Service::set_filename_watchlist(const std::string &filename) {
	this->watch_list->set_file_name(filename);
}

void Service::open_location()
{
	this->watch_list->open_location_watch_list();
}

void Service::undo()
{

	if (undo_action.empty())
		throw UndoError("No more operations to undo");
	
	std::shared_ptr<UndoAction> last_action = move(this->undo_action.back());
	last_action->undo();
	this->undo_action.pop_back();
	this->redo_action.push_back(move(last_action));

}

void Service::redo()
{

	if (redo_action.empty())
		throw UndoError("No more operations to redo");

	std::shared_ptr<UndoAction> last_action = move(this->redo_action.back());
	last_action->redo();
	this->redo_action.pop_back();
	this->undo_action.push_back(move(last_action));
	
}
