#include "GUI.h"
#include <windows.h>
#include "Exceptions.h"
#include <QShortcut>

void GUI::add_item()
{
	try {
		QString title = title_edit->text();
		QString genre = genre_edit->text();
		QString trailer = trailer_edit->text();
		QString likes = likes_edit->text();
		QString year = year_edit->text();

		int nr_year = std::stoi(year.toStdString());
		int nr_likes = std::stoi(likes.toStdString());

		this->service.addMovie(title.toStdString(), genre.toStdString(), trailer.toStdString(), nr_likes, nr_year);

		title_edit->clear();
		genre_edit->clear();
		trailer_edit->clear();
		likes_edit->clear();
		year_edit->clear();

		this->populate_list();
	}
	catch (std::exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void GUI::add_watchlist()
{
	try {
		Movie m = this->current_array[0];
		this->watchlist_array.push_back(m);
		this->service.addToWatchList(m.getTitle(), m.getGenre(), m.getTrailer(), m.getLikes(), m.getYearOfRelease());
		this->populate_watchlist();
	}
	catch (std::exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void GUI::update_item()
{
	auto movie = this->movies_array[movies_list->currentRow()];

	QString title = title_edit->text();
	QString genre = genre_edit->text();
	QString trailer = trailer_edit->text();
	QString likes = likes_edit->text();
	QString year = year_edit->text();

	int nr_year = std::stoi(year.toStdString());
	int nr_likes = std::stoi(likes.toStdString());

	this->service.serviceUpdateMovie(title.toStdString(), title.toStdString(), genre.toStdString(), trailer.toStdString(), nr_likes, nr_year);

	movies_list->clearSelection();
	title_edit->clear();
	genre_edit->clear();
	trailer_edit->clear();
	likes_edit->clear();
	year_edit->clear();
	this->populate_list();
}

void GUI::remove_item()
{

	try {
		auto movie = this->movies_array[movies_list->currentRow()];
		this->service.serviceRemoveMovie(movie.getTitle());
		movies_list->clearSelection();
		title_edit->clear();
		genre_edit->clear();
		trailer_edit->clear();
		likes_edit->clear();
		year_edit->clear();
		this->populate_list();
	}
	catch (std::exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void GUI::just_delete()
{
	auto movie = this->watchlist_array[watchlist_list->currentRow()];
	this->service.removeFromWatchList(movie.getTitle());
	movies_list->clearSelection();
	this->populate_watchlist();
}

void GUI::delete_and_like()
{
	auto movie = this->watchlist_array[watchlist_list->currentRow()];
	this->service.removeFromWatchList(movie.getTitle());
	movies_list->clearSelection();
	this->populate_watchlist();
	this->service.serviceUpdateMovie(movie.getTitle(), movie.getTitle(), movie.getGenre(), movie.getTrailer(), movie.getLikes() + 1, movie.getYearOfRelease());
	this->populate_list();
}

void GUI::get_item()
{
	auto movie = this->movies_array[this->movies_list->currentRow()];
	this->title_edit->setText(QString::fromStdString(movie.getTitle()));
	this->genre_edit->setText(QString::fromStdString(movie.getGenre()));
	this->trailer_edit->setText(QString::fromStdString(movie.getTrailer()));
	this->likes_edit->setText(QString::fromStdString(std::to_string(movie.getLikes())));
	this->year_edit->setText(QString::fromStdString(std::to_string(movie.getYearOfRelease())));

}

void GUI::search_genre()
{
	this->current->clear();
	this->current_array.clear();
	QString genre = genre_to_search_edit->text();
	this->genre_array = this->service.getGenreList(genre.toStdString());
	this->watchlist_iterator = this->genre_array.begin();

	QString item_in_list = QString::fromStdString((*watchlist_iterator).toString());
	auto* item = new QListWidgetItem{ item_in_list };
	this->current->addItem(item);
	this->current_array.push_back(*watchlist_iterator);
	//ShellExecuteA(NULL, "open", current_array[0].getTrailer().c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void GUI::next_movie()
{
	this->current->clear();
	this->current_array.clear();
	if (watchlist_iterator < genre_array.end() - 1)
		watchlist_iterator++;
	QString item_in_list = QString::fromStdString((*watchlist_iterator).toString());
	auto* item = new QListWidgetItem{ item_in_list };
	this->current->addItem(item);
	this->current_array.push_back(*watchlist_iterator);
	//ShellExecuteA(NULL, "open", current_array[0].getTrailer().c_str(), NULL, NULL, SW_SHOWNORMAL);

}

void GUI::open_location()
{
	this->service.open_location();
}

void GUI::save_filename()
{

	QString save = csv_edit->text();

	this->service.set_filename_watchlist(save.toStdString());

	csv_edit->clear();

}

void GUI::populate_list()
{
	if (this->movies_list->count() > 0) {
		this->movies_list->clear();
		this->movies_array.clear();
	}

	for (auto& m : this->service.getMovies()) {
		QString item_in_list = QString::fromStdString(m.toString());
		auto* item = new QListWidgetItem{ item_in_list };
		this->movies_list->addItem(item);
		this->movies_array.push_back(m);
	}
}

void GUI::populate_watchlist()
{
	if (this->watchlist_list->count() > 0) {
		this->watchlist_list->clear();
		this->watchlist_array.clear();
	}

	for (auto& m : this->service.getWatchList()) {
		QString item_in_list = QString::fromStdString(m.toString());
		auto* item = new QListWidgetItem{ item_in_list };
		this->watchlist_list->addItem(item);
		this->watchlist_array.push_back(m);
	}
}

void GUI::undo_operation()
{
	try {
		this->service.undo();
		this->populate_list();
	}
	catch (std::exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	
}

void GUI::redo_operation()
{
	try {
		this->service.redo();
		this->populate_list();
	}
	catch (std::exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void GUI::admin_mode() {
	
	auto* admin_window = new QWidget;
	auto* layout_admin = new QHBoxLayout{ admin_window };
	this->tab_widget->addTab(admin_window, "Admin");

	auto* left_side = new QWidget;
	layout_admin->addWidget(left_side);
	auto* leftVbox = new QVBoxLayout(left_side);

	auto* movies_list_name = new QLabel{ "Movies list" };
	leftVbox->addWidget(movies_list_name);
	this->movies_list = new QListWidget;
	this->movies_list->setSelectionMode(QAbstractItemView::SingleSelection);
	leftVbox->addWidget(this->movies_list);

	auto* right_side = new QWidget;
	layout_admin->addWidget(right_side);
	auto* right_vbox = new QVBoxLayout(right_side);

	auto* movie_data_widget = new QWidget;
	auto* fields_form = new QFormLayout{ movie_data_widget };
	right_vbox->addWidget(movie_data_widget);

	this->title_edit = new QLineEdit;
	auto* title_label = new QLabel("Title: ");
	fields_form->addRow(title_label, this->title_edit);

	this->genre_edit = new QLineEdit;
	auto* genre_label = new QLabel("Genre: ");
	fields_form->addRow(genre_label, this->genre_edit);

	this->trailer_edit = new QLineEdit;
	auto* trailer_label = new QLabel("Trailer: ");
	fields_form->addRow(trailer_label, this->trailer_edit);

	this->likes_edit = new QLineEdit;
	auto* likes_label = new QLabel("Likes: ");
	fields_form->addRow(likes_label, this->likes_edit);

	this->year_edit = new QLineEdit;
	auto* year_of_release_label = new QLabel("Year of release: ");
	fields_form->addRow(year_of_release_label, this->year_edit);

	auto* buttons_layout = new QHBoxLayout;
	this->add_button = new QPushButton("Add");
	this->update_button = new QPushButton("Update");
	this->delete_button = new QPushButton("Delete");
	buttons_layout->addWidget(this->add_button);
	buttons_layout->addWidget(this->update_button);
	buttons_layout->addWidget(this->delete_button);
	right_vbox->addLayout(buttons_layout);

	auto* undo_redo_buttons_layout = new QHBoxLayout;
	this->undo_button = new QPushButton("Undo");
	this->redo_button = new QPushButton("Redo");
	this->mylist_mvc_button = new QPushButton{ "Mylist MVC" };
	undo_redo_buttons_layout->addWidget(this->undo_button);
	undo_redo_buttons_layout->addWidget(this->redo_button);
	undo_redo_buttons_layout->addWidget(this->mylist_mvc_button);
	right_vbox->addLayout(undo_redo_buttons_layout);

	QPalette pal = add_button->palette();
	pal.setColor(QPalette::Button, QColor(Qt::red));
	add_button->setAutoFillBackground(true);
	add_button->setPalette(pal);
	add_button->update();

	pal = update_button->palette();
	pal.setColor(QPalette::Button, QColor(Qt::red));
	update_button->setAutoFillBackground(true);
	update_button->setPalette(pal);
	update_button->update();

	pal = delete_button->palette();
	pal.setColor(QPalette::Button, QColor(Qt::red));
	delete_button->setAutoFillBackground(true);
	delete_button->setPalette(pal);
	delete_button->update();

	QLinearGradient gradient = QLinearGradient(contentsRect().topLeft(), contentsRect().center());
	gradient.setColorAt(0.0, QColor(100, 100, 100));

	QPalette p = palette();
	p.setBrush(QPalette::Window, QBrush(gradient));
	setPalette(p);


	this->myview = new MoviesTableView{ this->service };

}

void GUI::user_mode() {

	auto* user_window = new QWidget;
	auto* layout_user = new QHBoxLayout{ user_window };
	this->tab_widget->addTab(user_window, "User");

	auto* left_side = new QWidget;
	layout_user->addWidget(left_side);
	auto* leftVbox = new QVBoxLayout(left_side);

	auto* movie_data_widget = new QWidget;
	auto* fields_form = new QFormLayout{ movie_data_widget };
	leftVbox->addWidget(movie_data_widget);

	this->genre_to_search_edit = new QLineEdit;
	auto* genre_label = new QLabel("Genre: ");
	fields_form->addRow(genre_label, this->genre_to_search_edit);

	this->search_button = new QPushButton("Search");
	fields_form->addWidget(this->search_button);


	auto* current_movie = new QLabel{ "Current movie" };
	leftVbox->addWidget(current_movie);
	this->current = new QListWidget;
	leftVbox->addWidget(this->current);

	auto* buttons_layout = new QHBoxLayout;
	this->add_watchlist_button = new QPushButton("Add");
	buttons_layout->addWidget(this->add_watchlist_button);

	this->next_button = new QPushButton("Next");
	buttons_layout->addWidget(this->next_button);
	leftVbox->addLayout(buttons_layout);


	auto* right_side = new QWidget;
	layout_user->addWidget(right_side);
	auto* rightVbox = new QVBoxLayout(right_side);


	auto* save_to_file_widget = new QWidget;
	auto* to_file_form = new QFormLayout{ save_to_file_widget };
	leftVbox->addWidget(save_to_file_widget);

	this->csv_edit = new QLineEdit;
	auto* csv_label = new QLabel("Save to CSV: ");
	to_file_form->addRow(csv_label, this->csv_edit);

	this->html_edit = new QLineEdit;
	auto* html_label = new QLabel("Save to HTML: ");
	to_file_form->addRow(html_label, this->html_edit);

	this->save_button = new QPushButton("Save");
	to_file_form->addWidget(this->save_button);


	auto* movies_list_name = new QLabel{ "Watchlist" };
	rightVbox->addWidget(movies_list_name);
	this->watchlist_list = new QListWidget;
	this->watchlist_list->setSelectionMode(QAbstractItemView::SingleSelection);
	rightVbox->addWidget(this->watchlist_list);


	this->location_button = new QPushButton("Open location");
	rightVbox->addWidget(this->location_button);

	auto* buttons_layout_to_del = new QHBoxLayout;
	this->delete_watchlist_button = new QPushButton("Just delete");
	buttons_layout_to_del->addWidget(this->delete_watchlist_button);
	this->delete_watchlist_like_button = new QPushButton("Delete and like");

	buttons_layout_to_del->addWidget(this->delete_watchlist_like_button);
	rightVbox->addLayout(buttons_layout_to_del);
	

}

GUI::GUI(Service &s) :service(s)
{

	this->tab_widget = new QTabWidget;
	auto* parent_layout = new QVBoxLayout{ this };
	parent_layout->addWidget(this->tab_widget);


	this->admin_mode();
	this->user_mode();

	connect(this->movies_list, &QListWidget::itemSelectionChanged, this, &GUI::get_item);
	connect(this->add_button, &QPushButton::clicked, this, &GUI::add_item);
	connect(this->update_button, &QPushButton::clicked, this, &GUI::update_item);
	connect(this->delete_button, &QPushButton::clicked, this, &GUI::remove_item);
	connect(this->search_button, &QPushButton::clicked, this, &GUI::search_genre);
	connect(this->next_button, &QPushButton::clicked, this, &GUI::next_movie);
	connect(this->add_watchlist_button, &QPushButton::clicked, this, &GUI::add_watchlist);
	connect(this->location_button, &QPushButton::clicked, this, &GUI::open_location);
	connect(this->delete_watchlist_button, &QPushButton::clicked, this, &GUI::just_delete);
	connect(this->delete_watchlist_like_button, &QPushButton::clicked, this, &GUI::delete_and_like);
	connect(this->save_button, &QPushButton::clicked, this, &GUI::save_filename);
	connect(this->undo_button, &QPushButton::clicked, this, &GUI::undo_operation);
	connect(this->redo_button, &QPushButton::clicked, this, &GUI::redo_operation);
	connect(this->mylist_mvc_button, &QPushButton::clicked, [this]() {
		auto* window = new QWidget;
		auto* tableView = new QTableView;
		tableView->setModel(this->myview);
		tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		window->setMinimumWidth(tableView->width());
		auto* Vbox = new QVBoxLayout{ window };
		Vbox->addWidget(tableView);
		window->show();
		});

	auto undo_sc = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	connect(undo_sc, &QShortcut::activated, [this]() {
		this->undo_operation();
		});
	auto redo_sc = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
	connect(redo_sc, &QShortcut::activated, [this]() {
		this->redo_operation();
		});

	this->populate_list();
}