#pragma once

#include "Service.h"
#include <QtCore/QAbstractTableModel>
#include <QtWidgets/QTableView>

class MoviesTableView : public QAbstractTableModel {

private:
	Service& service;

public:

    explicit MoviesTableView(Service& _service, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex& parent)const override;

    [[nodiscard]] int columnCount(const QModelIndex& parent)const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, int role)const override;

    void propagate();

};