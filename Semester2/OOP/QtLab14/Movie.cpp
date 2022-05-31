#include "Movie.h"
#include <fstream>

Movie::Movie()
	:title(""), genre(""), trailer("")
{
	this->year_of_release = 0;
	this->likes = 0;
	this->last_operation = 0;
}

Movie::Movie(std::string _title, std::string _genre, int _year_of_release, int _likes, std::string _trailer)
	: title(_title), genre(_genre), trailer(_trailer)
{
	this->year_of_release = _year_of_release;
	this->likes = _likes;
	this->last_operation = 0;
}

Movie::Movie(const Movie &movie)
	: title(movie.title), genre(movie.genre), trailer(movie.trailer)
{
	this->year_of_release = movie.year_of_release;
	this->likes = movie.likes;
	this->last_operation = movie.last_operation;
}

std::string Movie::getTitle() const
{
	return title;
}

std::string Movie::getGenre() const
{
	return genre;
}

std::string Movie::getTrailer() const
{
	return trailer;
}

int Movie::getLikes() const
{
	return likes;
}

int Movie::getYearOfRelease() const
{
	return year_of_release;
}

void Movie::setTitle(std::string _title)
{
	title = _title;
}

void Movie::setGenre(std::string _genre)
{
	genre = _genre;
}

void Movie::setTrailer(std::string _trailer)
{
	trailer = _trailer;
}

void Movie::setLikes(int _likes)
{
	likes = _likes;
}

void Movie::setYearOfRelease(int _year)
{
	year_of_release = _year;
}

std::string Movie::toString()
{
	return this->title +  " " + this->genre + "  " + std::to_string(this->likes) + "  " + std::to_string(this->year_of_release);
}

void Movie::set_last_operation(int lo)
{
	this->last_operation = lo;
}

int Movie::get_last_operation()
{
	return this->last_operation;
}

std::istream & operator>>(std::istream & is, Movie & m)
{
	if (is.eof())
		is.setstate(std::ios_base::failbit);
	else {
		std::string s;
		getline(is, m.title, ',');
		getline(is, m.genre, ',');
		getline(is, m.trailer, ',');
		std::string likes, year;
		getline(is, likes, ',');
		getline(is, year, '\n');
		int nr_likes = stoi(likes);
		m.setLikes(nr_likes);
		int nr_year = stoi(year);
		m.setYearOfRelease(nr_year);
	}
	return is;
}

std::ostream & operator<<(std::ostream & os, const Movie & m)
{
	os << m.getTitle() << ',' << m.getGenre() << ',' << m.getTrailer() << ',' << m.getLikes() << ',' << m.getYearOfRelease();
	return os;
}
