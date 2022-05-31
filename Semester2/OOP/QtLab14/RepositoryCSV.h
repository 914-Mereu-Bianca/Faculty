#pragma once
#include "RepositoryFile.h"
#include "Repository.h"
#include <string>
#include <vector>
#include "WatchList.h"

class RepositoryCSV : public WatchList {
private:
	std::string filename;
	

public:
	RepositoryCSV();
	RepositoryCSV(const std::string &file);
	~RepositoryCSV();
	
	void add(const Movie &movie) override;

	void remove(std::string name) override;

	void save_to_file() override;
	void set_file_name(const std::string &filename) override;
	void open_location_watch_list() override;

};