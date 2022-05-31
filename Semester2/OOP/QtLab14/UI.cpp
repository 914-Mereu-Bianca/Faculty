#include "UI.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>
#include <windows.h>
#include "Validator.h"
#include "Exceptions.h"

UI::UI(Service &s)
	:service{ s }
{
}

void UI::admin_commands() {
	std::cout << "\n      As an administrator you can:		\n\n";
	std::cout << "  Type the following commands to use the app:\n";
	std::cout << " add - to add a movie\n";
	std::cout << " remove - to remove a movie\n";
	std::cout << " update - to add a movie\n";
	std::cout << " list - to display all movies\n";
	std::cout << " exit - to exit the app \n\n";
}

void UI::user_commands() {
	std::cout << "\n      As a user you can:		\n\n";
	std::cout << "  Type the following commands to use the app:\n";
	std::cout << " watch list - to see the movies by genre\n";
	std::cout << " list - to display all movies\n";
	std::cout << " delete - to delete a movie\n";
	std::cout << " location - opens the location of the watch list\n";
	std::cout << " exit - to exit the app \n\n";
}

void UI::start()
{

	std::string command;

	std::cout << "Choose how to run the program: ";
	while (std::getline(std::cin, command)) {

		if (command == "admin")
			administrator_mode();

		else if (command == "user") {
			user_mode();
		}
		else if (command == "exit")
			break;
		else {
			std::cout << "Try again\n";
		}
		std::cout << "Choose how to run the program: ";
	}

	
}

void UI::administrator_mode() {

	admin_commands();
	std::cout << "Enter a command: ";
	std::string command;
	while (std::getline(std::cin, command)) {

		if (command == "add") {

			std::string title, genre, trailer, likes, year_of_release;
			std::cout << "Enter the title: ";
			std::getline(std::cin, title);

			std::cout << "Enter the genre: ";
			std::getline(std::cin, genre);

			std::cout << "Enter the trailer: ";
			std::getline(std::cin, trailer);

			std::cout << "Enter the number of likes: ";
			std::cin >> likes;

			std::cout << "Enter the year of release: ";
			std::cin >> year_of_release;
			std::getline(std::cin, command);

			try {
				Validator::validate_movie(likes, year_of_release);
				int int_likes = stoi(likes);
				int int_year = stoi(year_of_release);
				service.addMovie(title, genre, trailer, int_likes, int_year);
				std::cout << "The movie is succesfuly added";
			}
			catch (ValueError &ve) {
				std::cout << ve.what() << '\n';
			}

		}
		else if (command == "list") {
			for (const auto &movie : this->service.getMovies()) {
				std::cout << std::setw(15) << std::left << movie.getTitle() << std::setw(15) << std::left << movie.getGenre();
				std::cout << std::setw(50) << std::left << movie.getTrailer() << std::setw(15) << std::left << movie.getLikes();
				std::cout << std::setw(15) << movie.getYearOfRelease() << '\n';
			}

		}
		else if (command == "remove") {
			std::cout << "Enter the name of the movie you want to delete: ";
			std::getline(std::cin, command);
			try {
				service.serviceRemoveMovie(command);
				std::cout << "The movie has been removed\n";
			}
			catch (ValueError &ve) {
				std::cout << ve.what() << '\n';
			}
		}
		else if (command == "update") {
			 try {
				std::cout << "Enter the name of the movie you want to update: ";
				std::getline(std::cin, command);

				Movie movie = service.getMovie(command);

				std::cout << movie.getTitle() << "    " << movie.getGenre() << "    " << movie.getTrailer() << "        ";
				std::cout << movie.getLikes() << "        " << movie.getYearOfRelease() << '\n';

				std::string title, genre, trailer, likes, year_of_release;
				std::cout << "Enter the new title: ";
				std::getline(std::cin, title);

				std::cout << "Enter the new genre: ";
				std::getline(std::cin, genre);

				std::cout << "Enter the new trailer: ";
				std::getline(std::cin, trailer);

				std::cout << "Enter the new number of likes: ";
				std::cin >> likes;

				std::cout << "Enter the new year of release: ";
				std::cin >> year_of_release;
				std::string emptline;
				std::getline(std::cin, emptline); 

				Validator::validate_movie(likes, year_of_release);
				int int_likes = stoi(likes);
				int int_year = stoi(year_of_release);
				service.serviceUpdateMovie(command, title, genre, trailer, int_likes, int_year);

				std::cout << "The movie has been updated\n";
			}
			 catch (ValueError &ve) {
				 std::cout << ve.what() << '\n';
			}

		}

		else if (command == "exit")
			return;
		else
			std::cout << "Try again\n";

		std::cout << "\nEnter a command: ";
	}
}


void UI::user_mode() {
	user_commands();
	std::cout << "Enter a command: ";
	std::string command;
	while (std::getline(std::cin, command)) {
		if (command == "watch list") {
			std::cout << "Enter a genre: ";
			std::getline(std::cin, command);

			auto movies = this->service.getGenreList(command);
			if (movies.size() == 0)
				movies = this->service.getMovies();

			while (1) {

				for (const auto &movie : movies) {
					std::cout << "\t" << std::setw(15) << std::left << movie.getTitle() << std::setw(15) << std::left << movie.getGenre();
					std::cout << std::setw(50) << std::left << movie.getTrailer() << std::setw(15) << std::left << movie.getLikes();
					std::cout << std::setw(15) << movie.getYearOfRelease() << '\n';

					ShellExecuteA(NULL, "open", (movie.getTrailer()).c_str(), NULL, NULL, SW_SHOWNORMAL);

					std::cout << "Do you want to add this movie to the watch list? ";
					std::getline(std::cin, command);
					if (command == "yes") {
						try {
							this->service.addToWatchList(movie.getTitle(), movie.getGenre(), movie.getTrailer(), movie.getLikes(), movie.getYearOfRelease());
						}
						catch (ValueError &ve){
							std::cout << ve.what() << "\n";
						}
					}
				}
				std::cout << "You reach the end of the list. If you want to continue from the begin enter 'next': ";
				std::getline(std::cin, command);
				if (command != "next")
					break;
			}

		}
		else if (command == "list") {

			for (const auto &movie : this->service.getWatchList()) {
				std::cout << std::setw(15) << std::left << movie.getTitle() << std::setw(15) << std::left << movie.getGenre();
				std::cout << std::setw(50) << std::left << movie.getTrailer() << std::setw(15) << std::left << movie.getLikes();
				std::cout << std::setw(15) << movie.getYearOfRelease() << '\n';
			}
		}
		else if (command == "delete") {
			std::cout << "\nEnter the name of the movie you want to erase: ";
			std::getline(std::cin, command);
			if (this->service.existMovieWatchList(command)) {
				std::cout << "\nDid you like the movie? ";
				std::string rasp;
				std::getline(std::cin, rasp);
				if (rasp == "yes") {
					Movie movie = this->service.getMovie(command);
					this->service.serviceUpdateMovie(command, command, movie.getGenre(), movie.getTrailer(), movie.getLikes() + 1, movie.getYearOfRelease());
					movie.setLikes(movie.getLikes() + 1);
					this->service.removeFromWatchList(command);
				}
				else {
					this->service.removeFromWatchList(command);
				}

			}
			else {
				std::cout << "\nYou don't have the movie " << command << " saved in watch list\n";
			}
		}
		else if (command == "location") {
			this->service.open_location();
		}

		else if (command == "exit")
			break;

		std::cout << "\nEnter a command: ";
	}
}