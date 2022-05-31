#include <string>
#include <iostream>
#include "Service.h"
#include "Repository.h"
#include "UI.h"
#include "Test.h"
#include "Validator.h"
#include "Exceptions.h"
#include "RepositoryFile.h"
#include "RepositoryCSV.h"
#include "WatchList.h"
#include "RepositoryHTML.h"
#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Undo.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Repository* r = new RepositoryFile("file.txt");

	WatchList *wlist = new RepositoryCSV("watchlist.csv");
	std::vector<std::shared_ptr<UndoAction>> undo;
	std::vector<std::shared_ptr<UndoAction>> redo;
	Service s(r, wlist, undo, redo);

	GUI gui(s);
	gui.show();
	return a.exec();
}
