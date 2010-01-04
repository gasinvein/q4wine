/***************************************************************************
 *   Copyright (C) 2008, 2009, 2010 by Malakhov Alexey                     *
 *   brezerk@gmail.com                                                     *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 ***************************************************************************/

#ifndef WINEPROCCESWIDGET_H
#define WINEPROCCESWIDGET_H

#include "config.h"
#include "memory"

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QVBoxLayout>
#include <QTableView>
#include <QTableWidget>
#include <QLabel>
#include <QTimer>
#include <QInputDialog>
#include <QStandardItemModel>
#ifdef DEBUG
#include <QDebug>
#endif

#include "wizard.h"

#include <q4wine-lib/main.h>

class WineProccesWidget : public QWidget
{
Q_OBJECT
public:
	explicit WineProccesWidget(QString themeName, QWidget *parent = 0);

signals:

public slots:
	void stopTimer(void);
	void startTimer(void);

private:
	QString themeName;

	std::auto_ptr<QTimer> timer;
	std::auto_ptr<QStandardItemModel> model;

	//! This is need for libq4wine-core.so import.
	QLibrary libq4wine;
	typedef void *CoreLibPrototype (bool);
	CoreLibPrototype *CoreLibClassPointer;
	std::auto_ptr<corelib> CoreLib;

	void createActions();
	QIcon loadIcon(QString iconName);

	std::auto_ptr<QTableView> procTable;
	std::auto_ptr<QLabel> lblInfo;

	std::auto_ptr<QMenu> menu;
	std::auto_ptr<QAction> procKillSelected;
	std::auto_ptr<QAction> procKillWine;
	std::auto_ptr<QAction> procRefresh;
	std::auto_ptr<QAction> procRenice;

private slots:
	void getWineProccessInfo(void);
	void customContextMenuRequested(const QPoint &pos);
	void itemClicked(const QModelIndex &);

	void procKillSelected_Click(void);
	void procKillWine_Click(void);
	void procRenice_Click(void);
};

#endif // WINEPROCCESVIEW_H
