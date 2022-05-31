#include "MoviesTableView.h"

MoviesTableView::MoviesTableView(Service& _service, QObject* parent)
	:service{ _service }, QAbstractTableModel{ parent }
{
}

int MoviesTableView::rowCount(const QModelIndex& parent) const
{
	return this->service.getWatchList().size();
}

int MoviesTableView::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant MoviesTableView::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();

	auto movies = this->service.getWatchList();

	Movie movie = movies[row];
	if (role == Qt::DisplayRole) {
		
		if (col == 0) {
			return QString::fromStdString(movie.getTitle());
		}
		else if (col == 1) {
			return QString::fromStdString(movie.getGenre());
		}
		else if (col == 2) {
			return QString::fromStdString(movie.getTrailer());
		}
		else if (col == 3) {
			return QString::fromStdString(std::to_string(movie.getLikes()));
		}
		else if (col == 4) {
			return QString::fromStdString(std::to_string(movie.getYearOfRelease()));
		}

	}

	return QVariant{};
}

void MoviesTableView::propagate()
{
	emit layoutChanged();
}
