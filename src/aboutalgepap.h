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
#ifndef ABOUTALGEPAP_H
#define ABOUTALGEPAP_H

#include <QtGui/QAction>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QDesktopWidget>
#include <QApplication>

class AboutAlgePap : public QWidget
{
    Q_OBJECT

public:
    explicit AboutAlgePap(QString Dir);
    ~AboutAlgePap();

private:
    QString DirPath;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_4;
    QWidget *tab_2;
    QLabel *label_5;
    QWidget *tab_3;
    QLabel *label_6;
    QWidget *tab_4;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;

};

#endif // ABOUTALGEPAP_H
