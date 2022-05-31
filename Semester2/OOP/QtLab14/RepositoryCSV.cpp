#include "RepositoryCSV.h"
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>

RepositoryCSV::RepositoryCSV() {
	{}
}

RepositoryCSV::RepositoryCSV(const std::string & file)
{
	this->filename = file;
}

RepositoryCSV::~RepositoryCSV() {
	{} 
}

void RepositoryCSV::add(const Movie & movie)
{
	WatchList::add(movie);
	this->save_to_file();
}

void RepositoryCSV::remove(std::string name)
{
	WatchList::remove(name);
	this->save_to_file();
}

void RepositoryCSV::save_to_file() {
	std::ofstream fout(this->filename);

	for (int i = 0; i < this->watch_list.size() - 1; i++) {
		fout << this->watch_list[i] << std::endl;
	}
	fout << this->watch_list[this->watch_list.size()-1];
	fout.close();
}

void RepositoryCSV::set_file_name(const std::string &filename) {
	this->filename = filename;
}

void RepositoryCSV::open_location_watch_list()
{
	std::string notepad_path = "C:/Users/Bia/Desktop/CSA/asm_tools/npp/notepad++.exe";
	ShellExecuteA(NULL, "open", notepad_path.c_str(), this->filename.c_str(), NULL, SW_NORMAL);
}

