#include "Test.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "Repository.h"
#include "Service.h"
#include "Validator.h"
#include "Comparator.h"
#include "RepositoryFile.h"
#include "RepositoryCSV.h"
#include "WatchList.h"

#include "Exceptions.h"
#include <algorithm>

/*
void test_add_service_movie() {

	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);

	s.addMovie("TitluFilm", "Gen", "Trailer", 5, 1997);

	auto movie = s.getMovies();
	assert(movie[1].getTitle() == "TitluFilm" && movie[1].getGenre() == "Gen" && movie[1].getTrailer() == "Trailer" && movie[1].getLikes() == 5
		&& movie[1].getYearOfRelease() == 1997);

	s.serviceRemoveMovie("TitluFilm");

}

void test_update_service_movie() {

	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);

	s.addMovie("TitluFilm", "Gen", "Trailer", 5, 1997);

	s.serviceUpdateMovie("TitluFilm", "TitluFilm2", "Gen2", "Trailer2", 0, 0);

	auto movie = s.getMovies();

	assert(movie[1].getTitle() == "TitluFilm2" && movie[1].getGenre() == "Gen2" && movie[1].getTrailer() == "Trailer2" && movie[1].getLikes() == 0
		&& movie[1].getYearOfRelease() == 0);

	s.serviceRemoveMovie("TitluFilm2");

}


void test_remove_service_movie() {

	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);

	s.addMovie("TitluFilm1", "Gen", "Trailer", 5, 1997);
	s.addMovie("TitluFilm2", "Gen", "Trailer", 5, 1997);
	s.addMovie("TitluFilm3", "Gen", "Trailer", 5, 1997);
	s.serviceRemoveMovie("TitluFilm2");
	try {
		s.serviceRemoveMovie("a"); // check the case in which the movie doesn't exist
		assert(false);
	}
	catch (ValueError &ve) {
		std::string what = ve.what();
		assert(what == "The movie doesn't exist");
	}

	std::vector<Movie> movies = s.getMovies();
	assert(movies.size() == 3); // with the movie that already is there
	s.serviceRemoveMovie("TitluFilm1");
	s.serviceRemoveMovie("TitluFilm3");

}

void test_genre_movies() {

	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);

	s.addMovie("TitluFilm", "Gen", "Trailer", 4, 1997);

	Movie movie = s.getMovie("TitluFilm");
	std::string g = "Gen";
	auto movies = s.getGenreList(g);

	assert(s.existMovie("a") == 0);
	assert(movie.getTitle() == movies[0].getTitle());

	s.serviceRemoveMovie("TitluFilm");
}


void test_serviceUser_add() {
	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);

	s.addToWatchList("Titlu", "Gen", "Trailer", 19, 1995);

	auto movie = s.getWatchList();
	
	assert(movie[0].getTitle() == "Titlu" && movie[0].getGenre() == "Gen" && movie[0].getTrailer() == "Trailer" && movie[0].getLikes() == 19
		&& movie[0].getYearOfRelease() == 1995);
	
	s.removeFromWatchList("Titlu");
}

void test_serviceUser_remove() {

	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);

	s.addToWatchList("Titlu", "Gen", "Trailer", 1995, 19);

	s.serviceRemoveMovie("Titlu");
	auto movies = s.getWatchList();

	assert(movies.size() == 0); // the one that always remains in file

}

void test_serviceUser_existsMovie() {

	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);

	s.addToWatchList("Titlu2", "Gen", "Trailer", 1995, 19);
	s.addToWatchList("Titlu", "Gen", "Trailer", 1995, 19);

	assert(s.existMovieWatchList("Titlu") == 1);

	s.serviceRemoveMovie("Titlu");

}

void test_validator() {

	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);
	Validator v;

	s.addMovie("a", "b", "c", 1, 1);

//	assert(v.validate_movie_add(s, "a") == 0);
//	assert(v.validate_movie_add(s, "b") == 1);

//	assert(v.validate_number("90") == 1);
//	assert(v.validate_number("grd") == 0);

	s.serviceRemoveMovie("a");

}


void test_comp() {

	std::string filename = "test_file.txt";
	Repository *r = new RepositoryFile(filename);
	std::string filename2 = "test_file.csv";
	WatchList *r_user = new RepositoryCSV(filename2);
	Service s(r, r_user);

	CompareByTitle<Movie> cbt;
	CompareByYear<Movie> cby;

	s.addMovie("d", "gen1", "link1", 1, 1);
	s.addMovie("g", "gen2", "link2", 2, 0);
	s.addMovie("e", "gen3", "link3", 0, 13);

	auto movies = s.getMovies();

	std::sort(movies.begin(), movies.end(), cbt);

	assert(movies[0].getTitle() == "d");

	std::sort(movies.begin(), movies.end(), cby);

	assert(movies[0].getYearOfRelease() == 0);

	s.serviceRemoveMovie("d");
	s.serviceRemoveMovie("g");
	s.serviceRemoveMovie("e");

}
*/

void test_all()
{
	/*test_add_service_movie();
	test_update_service_movie();
	test_remove_service_movie();
	test_genre_movies();
	test_comp();*/
	//test_serviceUser_add();
	//test_serviceUser_remove();
	//test_serviceUser_existsMovie();
	//test_validator();
}