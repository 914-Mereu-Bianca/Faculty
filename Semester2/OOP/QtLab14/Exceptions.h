//#pragma once
#include <exception>

class ValueError : public std::exception {

private:
	const char *message;

public:
	explicit ValueError(const char* message);
	[[std::nodiscard]] const char * what() const noexcept override;

};

class RepositoryError : public std::exception {
private:
	const char *message;
public:
	explicit RepositoryError(const char* message);
	[[std::nodiscard]] const char * what() const noexcept override;

};

class UndoError : public std::exception {
private:
	const char* message;
public:
	explicit UndoError(const char* message);
	[[std::nodiscard]] const char* what() const noexcept override;

};