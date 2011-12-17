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
#ifndef ALGEPAP_H
#define ALGEPAP_H

#include "aialgbutton.h"

#include <QWidget>
#include <QString>
#include <QEvent>
#include <QObject>
#include <QCloseEvent>
#include <QMenu>

class AlgePap : public QWidget {
    Q_OBJECT
public:
    //Functions
    AlgePap(QWidget *parent, QString DirPath);
    ~AlgePap();

    //Variables
    QString DirPath;
    Aialgbutton* buttons;

protected:
    bool eventFilter(QObject* watched, QEvent* event);

private:

private slots:

};

#endif // ALGEPAP_H
