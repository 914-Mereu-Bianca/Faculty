#include "RepositoryHTML.h"
#include <fstream>
#include <windows.h>

RepositoryHTML::RepositoryHTML()
{
}

RepositoryHTML::RepositoryHTML(const std::string & file)
{
	this->filename = file;
}

RepositoryHTML::~RepositoryHTML()
{
}

void RepositoryHTML::add(const Movie & movie)
{
	WatchList::add(movie);
	this->save_to_file();
}

void RepositoryHTML::remove(std::string name)
{
	WatchList::remove(name);
	this->save_to_file();
}

void RepositoryHTML::save_to_file()
{
	std::ofstream fout(this->filename);

	fout << "<!DOCTYPE html>\n"
		"<html>\n"
		"<head>\n"
		"\t<title>Watch list</title>\n"
		"</head>\n"
		"<body>\n"
		"<table border=\"1\">\n"
		"\t<tr>\n"
		"\t\t<td>Title</td>\n"
		"\t\t<td>Genre</td>\n"
		"\t\t<td>Year of release</td>\n"
		"\t\t<td>Number of likes</td>\n"
		"\t\t<td>Trailer</td>\n"
		"\t</tr>\n";
	for (auto& movie : this->watch_list) {
		fout << "\t<tr>\n";
		fout << "\t\t<td>" << movie.getTitle() << "</td>\n";
		fout << "\t\t<td>" << movie.getGenre() << "</td>\n";
		fout << "\t\t<td>" << movie.getYearOfRelease() << "</td>\n";
		fout << "\t\t<td>" << movie.getLikes() << "</td>\n";
		fout << "\t\t<td><a href=\"" << movie.getTrailer() << "\">Link</a></td>\n";
		fout << "\t</tr>\n";
	}
	fout << "\t\t</table>\n"
		"\t</body>\n"
		"</html>";
	fout.close();
}

void RepositoryHTML::set_file_name(const std::string & filename)
{
	this->filename = filename;
}

void RepositoryHTML::open_location_watch_list()
{
	ShellExecuteA(NULL, "open",("C:/Users/Bia/Desktop/proiecte faculta/Object Oriented Programming/Laboratory work/a8-9-914-Mereu-Bianca/Lab8-9/Lab8-9/"+(this->filename)).c_str(), NULL, NULL, SW_SHOWNORMAL);
}
