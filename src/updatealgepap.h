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
#ifndef UPDATEALGEPAP_H
#define UPDATEALGEPAP_H

#include <QWidget>
#include <QPushButton>
#include <QSettings>
#include <QDir>
#include <QString>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDesktopWidget>
#include <QDate>

class UpdateAlgePap : public QWidget
{
    Q_OBJECT
public:
    explicit UpdateAlgePap(QString Dir,int* languageindex);
    QString llabel[2];
    QString blabel[2];
    QString updatealgepapwindowlabel[2];

    void languageChange(int index);
    void iniVisible();

signals:

public slots:
    void updatedata();

private:
    QString DirPath;
    QSettings* settings;
    QString getkey(QString path);
    QDir directory;
    QPushButton* b;
    QLabel* l;
    int* languageindex;
    QStringList updatemessage[2];

    void initializedata(QString Dir,int* languageindex);
    void initializegui();
    void loadsettings();
    void savesettings();
    bool checkupdate();

};

#endif // UPDATEALGEPAP_H
