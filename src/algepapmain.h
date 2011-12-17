/*
    This file is part of algepap.

    algepap is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */
//###############################################################
//#								#
//# 		AlgePap program : Algerian newspapers		#
//#    	   http://djelfa.info/vb/showthread.php?t=559996 	#
//#			By : أخ المسلمين			#
//#								#
//###############################################################
#ifndef ALGEPAPMAIN_H
#define ALGEPAPMAIN_H

#include "algepap.h"
#include "aboutalgepap.h"
#include "downloadalgepap.h"
#include "updatealgepap.h"

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QEvent>
#include <QObject>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QComboBox>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QScrollArea>
#include <QSettings>
#include <QDir>
#include <QCryptographicHash>
#include <QThread>
#include <QTimer>

class AlgePapMain : public QMainWindow
{
Q_OBJECT
public:
    explicit AlgePapMain(QWidget *parent, QString DirPath);
    void setVisible(bool visible);
    void languageChange(int index);

    //Variables
    QString DirPath;
    QString algepapwindowtitle[2];
    QString minimizeactionlabel[2];
    QString restoreactionlabel[2];
    QString downloadactionlabel[2];
    QString updateactionlabel[2];
    QString englishactionlabel[2];
    QString arabicactionlabel[2];
    QString aboutactionlabel[2];
    QString quitactionlabel[2];
    int* languageindex;

protected:
    void closeEvent(QCloseEvent *event);

private:
    //Functions
    void createMessageGroupBox();
    void setupmain(QString Dir);
    void setupalgepapbrowse();
    void setupaction();
    void setupmenu();
    void setuptrayicon();
    void loadsettings();
    void savesettings();
    //Variables
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *downloadAction;
    QAction *updateAction;
    QAction *englishAction;
    QAction *arabicAction;
    QAction *aboutAction;
    QAction *quitAction;
    QComboBox *typeComboBox;
    QScrollArea* scrol;
    AlgePap* window;
    QSettings* settings;

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void download();
    void updateActionclick();
    void englishActionclick();
    void arabicActionclick();
    void aboutActionclick();
    void quit();

signals:

public slots:

};

#endif // ALGEPAPMAIN_H
