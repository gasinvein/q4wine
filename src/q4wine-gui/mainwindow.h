/***************************************************************************
 *   Copyright (C) 2008, 2009, 2010 by Malakhov Alexey                           *
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

/*!
 * \defgroup q4wine-gui Q4Wine GUI
 * \brief q4wine-gui pakage provide general GUI functions for q4wine.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QDir>
#include <QSizePolicy>
#include <QStringList>
#include <QTimer>
#include <QTableWidget>
#include <QTabWidget>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include <QToolBar>
#include <QIcon>
#include <QTreeWidgetItem>
#include <QMimeData>
#include <QDrag>
#include <QSplitter>

#include <ui_MainWindow.h>

#include "config.h"

#include "src/core/database/prefix.h"
#include "src/core/database/dir.h"
#include "src/core/database/icon.h"
#include "src/core/database/last_run_icon.h"
#include "src/core/database/image.h"

#include "xmlparser.h"

#include "iconlistwidget.h"
#include "prefixtreewidget.h"
#include "wineprocceswidget.h"
#include "prefixcontrolwidget.h"

#ifdef WITH_WINEAPPDB
#include "appdbwidget.h"
#endif

#include "wisitem.h"
#include "iconsview.h"
#include "wizard.h"
#include "process.h"
#include "winebinlauncher.h"
//#include "iconsettings.h"
#include "imagemanager.h"
//#include "prefixsettings.h"
#include "about.h"
#include "appsettings.h"
#include "run.h"

#include "registry.h"

#ifdef WITH_WINETRIKS
  #include "temporary/winetricks.h"
#endif

#include <stdlib.h>
#include <unistd.h>

#include <q4wine-lib/main.h>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
	public:
		MainWindow(int startState, QWidget * parent = 0, Qt::WFlags f = 0);
		// Icon copy\cyt structure

	public slots:
		void messageReceived(const QString message) const;
		void setcbPrefixesIndex(const QString text) const;

	private slots:

		//void StartDrug(QDragEnterEvent * event);

		void CoreFunction_ResizeContent(int tabIndex);

		void changeStatusText(QString text);

		/*
		 * Icon tray slots
		 */
		void trayIcon_Activate(QSystemTrayIcon::ActivationReason reason);

		/*
		 * Command buttons slots
		 */
		void cmdManagePrefixes_Click(void);
		void cmdCreateFake_Click(void);
		void cmdUpdateFake_Click(void);
		void cmdWinetricks_Click (void);
		void cmdTestWis_Click (void);
		void cmdClearFilter_Click (void);
		void cmdAppDBSearch_Click (void);

		void updateIconDesc(QString program, QString args, QString desc, QString console, QString desktop);

		//Main menu slots
		void mainExit_Click(void);
		void mainPrograms_Click(void);
		void mainImageManager_Click(void);
		void mainProcess_Click(void);
		void mainSetup_Click(void);
		void mainPrefix_Click(void);
		void mainAbout_Click(void);
		void mainAboutQt_Click(void);
		void mainExportIcons_Click(void);
		void mainRun_Click(void);
		void mainOptions_Click(void);
		void mainInstall_Click(void);
		void mainFirstSteps_Click(void);
		void mainFAQ_Click(void);
		void mainIndex_Click(void);
		void mainWebsite_Click(void);
		void mainDonate_Click(void);
		void mainBugs_Click(void);

	private:
		//! Custom Widgets
		//DragListWidget* lstIcons;
		std::auto_ptr<AppDBWidget> appdbWidget;

		//! This is need for libq4wine-core.so import;
		typedef void *CoreLibPrototype (bool);
			CoreLibPrototype *CoreLibClassPointer;
			std::auto_ptr<corelib> CoreLib;
		QLibrary libq4wine;

		//Classes
		Prefix db_prefix;
		Dir db_dir;
		Icon db_icon;
		Last_Run_Icon db_last_run_icon;
		Image db_image;

		// Tray icon
		std::auto_ptr<QSystemTrayIcon> trayIcon;
		std::auto_ptr<QMenu> trayIconMenu;

		void createTrayIcon();
		void setMeVisible(bool visible);

		// Settings functions
		void createMenuActions(void);
		void getSettings(void);

		void runAutostart(void);

	   /*! \brief This function updates all database connectd widgets to current state.
		*
		* \param  currentPrefix  Current user selected prefix id.
		*/
		void updateDtabaseConnectedItems(int currentPrefix = -1);

		//Events definition
		void resizeEvent (QResizeEvent);
		void clearTmp();

		std::auto_ptr<QSplitter> splitter;

	signals:
		void appdbWidget_startSearch(short int, QString);
		void updateDatabaseConnections(void);
		void setDefaultFocus(QString, QString);
		void stopProcTimer(void);
		void startProcTimer(void);

	protected:
		// Event filter
		bool eventFilter(QObject *obj, QEvent *event);
		void closeEvent(QCloseEvent *event);

		//Resource\theme loader
		QIcon loadIcon(QString iconName);

		QString HOME_PATH;
		QString ROOT_PATH;
		QString TEMP_PATH;

		QString DEFAULT_WINE_BIN, DEFAULT_WINE_SERVER, DEFAULT_WINE_LOADER, DEFAULT_WINE_LIBS;
		QString WRESTOOL_BIN, ICOTOOL_BIN;
		QString TAR_BIN, MOUNT_BIN, UMOUNT_BIN, SUDO_BIN, GUI_SUDO_BIN, NICE_BIN, RENICE_BIN, SH_BIN;
		QString CONSOLE_BIN, CONSOLE_ARGS;
		QString THEME_NAME;

		bool SHOW_TRAREY_ICON;
};

#endif


