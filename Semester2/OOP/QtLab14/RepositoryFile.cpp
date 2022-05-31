#include "RepositoryFile.h"
#include <fstream>

RepositoryFile::RepositoryFile() {
	{}
}

RepositoryFile::RepositoryFile(const std::string & file)
{
	this->filename = file;
	this->read_from_file();
}

RepositoryFile::~RepositoryFile() {
	{} 
}

void RepositoryFile::add(const Movie &movie) {
	Repository::add(movie);
	std::vector<Movie> list = this->getAll();
	list.push_back(movie);
	this->save_to_file();
}

void RepositoryFile::update(std::string oldMovie, const Movie &newMovie) {
	Repository::update(oldMovie, newMovie);
	std::vector<Movie> list = this->getAll();
	for (auto &movie : list) {
		if (movie.getTitle() == oldMovie) {
			movie.setTitle(newMovie.getTitle());
			movie.setGenre(newMovie.getGenre());
			movie.setTrailer(newMovie.getTrailer());
			movie.setLikes(newMovie.getLikes());
			movie.setYearOfRelease(newMovie.getYearOfRelease());
		}
	}
	this->save_to_file();
}

void RepositoryFile::remove(std::string name) {
	Repository::remove(name);
	std::vector<Movie> list = this->getAll();
	for (auto movie = list.begin(); movie != list.end(); movie++) {
		if (movie->getTitle() == name) {
			list.erase(movie);
			break;
		}
	}
	this->save_to_file();
}

std::string RepositoryFile::get_file_name() {
	return this->filename;
}

void RepositoryFile::set_file_name(const std::string &file_name_to_set) {
	this->filename = file_name_to_set;
	this->read_from_file();
}

void RepositoryFile::save_to_file()
{
	std::ofstream file(this->filename);

	for (int i = 0; i < this->arr.size(); i++)
		if (this->arr.size() - 1 == i)
			file << this->arr[i];
		else
			file << this->arr[i] << '\n';

	file.close();
}

void RepositoryFile::read_from_file()
{
	std::ifstream file(this->filename);

	Movie m;
	while (file >> m)
		this->arr.push_back(m);

	file.close();

}
