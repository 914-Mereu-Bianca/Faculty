#pragma once
#include <vector>
#include "Movie.h"

class Repository {

protected:
	std::vector<Movie> arr;

public:

	//Repository();
	// return all of the elements from repo
	virtual std::vector<Movie> getAll();

	// adds a movie to the repo
	virtual void add(const Movie &newMovie);

	// returns the size of the repo vector
	//virtual int repoSize();

	// returns 0 if the name of the movie is not in the repo array
	virtual bool movie_exists(std::string name);

	// removes a movie that has the same name from the parameters
	virtual void remove(std::string name);

	// updates a movie from the position given in the parameters with the new movie
	virtual void update(std::string oldMovie, const Movie &newMovie);

	virtual std::string get_file_name();

	virtual void set_file_name(const std::string &file_name_to_set);

	virtual ~Repository() = default;

	Movie getMovie(std::string name);

};