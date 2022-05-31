#pragma once
#include "Repository.h"
#include <string>
#include <vector>

class RepositoryFile : public Repository {
protected:
	std::string filename;
	int size;
	
public:

	RepositoryFile();
	RepositoryFile(const std::string &file);
	virtual ~RepositoryFile() override;

	void add(const Movie &movie) override;

	void remove(std::string name) override;

	void update(std::string oldMovie, const Movie &newMovie) override;

	std::string get_file_name() override;

	void set_file_name(const std::string &file_name_to_set) override;

	void save_to_file();

	void read_from_file();

};