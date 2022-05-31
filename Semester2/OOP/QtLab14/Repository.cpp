#include "Repository.h"
#include "Validator.h"
#include <fstream>
#include "Exceptions.h"

std::vector<Movie> Repository::getAll()
{
	return this->arr;
}

void Repository::add(const Movie & newMovie)
{
	Validator::validate_movie_add(this, newMovie.getTitle());
	this->arr.push_back(newMovie);
}

void Repository::remove(std::string name)
{
	Validator::validate_movie_remove(this, name);
	for (auto movie = this->arr.begin(); movie != this->arr.end(); movie++) {
		if (movie->getTitle() == name) {
			this->arr.erase(movie);
			break;
		}
	}
}

void Repository::update(std::string oldMovie, const Movie & newMovie)
{
	Validator::validate_movie_update(this,oldMovie);
	for (auto &movie : this->arr) {
		if (movie.getTitle() == oldMovie) {
			movie.setTitle(newMovie.getTitle());
			movie.setGenre(newMovie.getGenre());
			movie.setTrailer(newMovie.getTrailer());
			movie.setLikes(newMovie.getLikes());
			movie.setYearOfRelease(newMovie.getYearOfRelease());
		}
	}

}

bool Repository::movie_exists(std::string name) {
	for (auto &movie : this->arr) {
		if (movie.getTitle() == name)
			return 1;
	}
	return 0;
}

void Repository::set_file_name(const std::string &file_name_to_set) {
	throw RepositoryError("Cannot open file.");
}

Movie Repository::getMovie(std::string name)
{
	for (auto &movie : this->arr) {
		if (movie.getTitle() == name) {
			return movie;
		}
	}
}

std::string Repository::get_file_name() {
	throw RepositoryError("Cannot open file.");
}



