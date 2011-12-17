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
#ifndef AIALGBUTTON_H
#define AIALGBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QPixmap>
#include <QString>
#include <QFile>
#include <QProcess>

class Aialgbutton : public QObject
{
Q_OBJECT
public:
    //Functions
    explicit Aialgbutton(QObject *parent = 0);
    Aialgbutton* setup(QWidget* par, int ind, QString name, QString link, QString downloadlink, QString Dir);
    void Load(QWidget* parent, QString Dir);
    void Add(Aialgbutton* tmp);
    Aialgbutton* Item(int);
    int Item(QString test);
    void DelItem();
    void Delete();
    int count(void);
    QString name(void);
    QString link(void);
    QString downloadlink(void);
    void setname(QString);
    void setlink(QString);
    void setdownloadlink(QString);
    void setbrowseconnect(void);
    //variables
    QPushButton* paperbutton;
    Aialgbutton* next;
    QString algepapdirectory;

private:
    QString papername,paperlink,paperdownloadlink;

public slots:
    void browse();
};

#endif // AIALGBUTTON_H
