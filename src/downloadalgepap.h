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
#ifndef DOWNLOADALGEPAP_H
#define DOWNLOADALGEPAP_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QDesktopWidget>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QFile>
#include <QComboBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QToolButton>
#include <QProcess>
#include <QSettings>
#include <QCloseEvent>
#include <QLabel>
#include <QMessageBox>

class DownloadAlgePap : public QWidget
{
Q_OBJECT
public:
    explicit DownloadAlgePap(QString DirPath, int* language);
    void languageChange(int index);
    void loadsettings();

protected:
    void closeEvent(QCloseEvent *event);

signals:

public slots:
    void clearclick();
    void selectclick();
    void downloadclick();
    void bdialogclick();
    void setsavelocationenabled(int);

private:
    //Variables
    QString DirPath;
    QListWidget* list;
    QPushButton *clear, *select, *download;
    QComboBox* iconComboBox;
    QToolButton* bdialog;
    QLineEdit* linedialog;
    QLabel* linelabel;
    QSettings* settings;
    int* languageindex;
    QString downloadalgepapwindowtitle[2];
    QString selectlabel[2];
    QString clearlabel[2];
    QString linelabellabel[2];
    QString downloadlabel[2];
    QString wgetlabel[2];
    QString gwgetlabel[2];
    QString kgetlabel[2];
    QString browserlabel[2];

    //Functions
    void setupdownloadalgepap(QString Dir, int* language);
    void setupdownloadalgepapwidget();
    void loadnewspaperdata();
    void savesettings();
    bool IsNoItemChecked();
    QString downloadname[3][50];

};

#endif // DOWNLOADALGEPAP_H
