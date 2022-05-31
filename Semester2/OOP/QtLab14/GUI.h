#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QComboBox>
#include "Service.h"
#include "Movie.h"
#include "MoviesTableView.h"

class GUI : public QWidget {
	Q_OBJECT

private:
	Service service;
	QTabWidget* tab_widget;
	QListWidget* movies_list;
	std::vector<Movie> movies_array;
	QListWidget* watchlist_list;
	QListWidget* current;
	std::vector<Movie> watchlist_array;
	std::vector<Movie> genre_array;
	std::vector<Movie> current_array;
	std::vector<Movie>::iterator watchlist_iterator;
	QLineEdit* title_edit;
	QLineEdit* trailer_edit;
	QLineEdit* genre_edit;
	QLineEdit* genre_to_search_edit;
	QLineEdit* likes_edit;
	QLineEdit* year_edit;
	QLineEdit* csv_edit;
	QLineEdit* html_edit;
	QPushButton* update_button;
	QPushButton* delete_button;
	QPushButton* add_button;
	QPushButton* like_button;
	QPushButton* add_watchlist_button;
	QPushButton* next_button;
	QPushButton* save_button;
	QPushButton* search_button;
	QPushButton* location_button;
	QPushButton* delete_watchlist_button;
	QPushButton* delete_watchlist_like_button;
	QPushButton* undo_button;
	QPushButton* redo_button;
	QPushButton* mylist_mvc_button;
	MoviesTableView* myview;

public:

	GUI(Service &s);

	//void initialize_movie_list();

	void admin_mode();
	void user_mode();
	void add_item();
	void add_watchlist();
	void update_item();
	void remove_item();
	void just_delete();
	void delete_and_like();
	void get_item();
	void search_genre();
	void next_movie();
	void open_location();
	void save_filename();
	void populate_list();
	void populate_watchlist();
	void undo_operation();
	void redo_operation();

};