#pragma once

#include <vector>
#include "Movie.h"
#include "Repository.h"

class UndoAction {
public:
	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual ~UndoAction() = default;

};

class UndoAdd : public UndoAction {

private:
	Repository& repo;
	Movie movie;

public:
	
	UndoAdd(Repository& r, Movie& m) : repo(r), movie(m) {}

	void undo() override { repo.remove(movie.getTitle()); }

	void redo() override { repo.add(movie); }

};

class UndoRemove : public UndoAction {

private:
	Repository& repo;
	Movie movie;

public:

	UndoRemove(Repository& r, Movie& m) : repo(r), movie(m) {}

	void undo() override { repo.add(movie); }

	void redo() override { repo.remove(movie.getTitle()); }

};

class UndoUpdate : public UndoAction {

private:
	Repository& repo;
	Movie old_movie, new_movie;

public:

	UndoUpdate(Repository& r, Movie& old_m, Movie& new_m ) : repo(r), old_movie(old_m), new_movie(new_m) {}

	void undo() override { repo.update(new_movie.getTitle(), old_movie); }

	void redo() override { repo.update(old_movie.getTitle(), new_movie); }

};