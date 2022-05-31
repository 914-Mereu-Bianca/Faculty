#include "Exceptions.h"

ValueError::ValueError(const char * message) {
	this->message = message;
}

const char *ValueError::what() const noexcept {
	return this->message;
}

RepositoryError::RepositoryError(const char *message) {
	this->message = message;
}

const char *RepositoryError::what() const noexcept {
	return this->message;
}

UndoError::UndoError(const char* message)
{
	this->message = message;
}

const char* UndoError::what() const noexcept
{
	return this->message;
}
