#pragma once
#include <string>

class Movie {

private:

	std::string title;
	std::string genre;
	int year_of_release;
	int likes;
	std::string trailer;
	int last_operation;


public:

	Movie();

	Movie(std::string _title, std::string _genre, int _year_of_release, int _likes, std::string _trailer);

	Movie(const Movie &movie);

	// returns the title of the movie
	std::string getTitle() const;

	// returns the genre of the movie
	std::string getGenre() const;

	// returns the trailer of the movie
	std::string getTrailer() const;

	// returns the number of likes of the movie
	int getLikes() const;

	// returns the year of release of the movie
	int getYearOfRelease() const;

	// sets the title to the one in the parameters
	void setTitle(std::string _title);

	// sets the genre to the one in the parameters
	void setGenre(std::string _genre);

	// sets the trailer to the one in the parameters
	void setTrailer(std::string _trailer);

	// sets the likes to the one in the parameters
	void setLikes(int _likes);

	// sets the year of release to the one in the parameters
	void setYearOfRelease(int _year);

	//bool operator==(const Movie);

	std::string toString();

	void set_last_operation(int lo);
	int get_last_operation();

	friend std::istream& operator>>(std::istream& is, Movie& m);
	friend std::ostream& operator<<(std::ostream& os, const Movie& m);

};