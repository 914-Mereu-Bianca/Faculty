#pragma once
#include "Repository.h"
#include <string>
#include <vector>
#include "WatchList.h"

class RepositoryHTML : public WatchList {
private:
	std::string filename;

public:
	RepositoryHTML();
	RepositoryHTML(const std::string &file);
	~RepositoryHTML();

	void add(const Movie &movie) override;

	void remove(std::string name) override;

	void save_to_file() override;
	void set_file_name(const std::string &filename) override;
	void open_location_watch_list() override;
};