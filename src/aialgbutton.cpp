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
#include "aialgbutton.h"

#include <iostream>
using namespace std;

Aialgbutton::Aialgbutton(QObject *parent) :
        QObject(parent)
{
    paperbutton = NULL;
    next = NULL;
}

Aialgbutton* Aialgbutton::setup(QWidget *par, int ind, QString name, QString link, QString downloadlink, QString Dir) {
    Aialgbutton* t = new Aialgbutton(par);
    t->next = NULL;
    t->algepapdirectory = Dir;
    t->papername = name;
    t->paperlink = link;
    t->paperdownloadlink = downloadlink;
    t->paperbutton = new QPushButton(par);
    t->paperbutton->setGeometry(QRect(0,0,156,56));
    t->paperbutton->setIconSize(QSize(150,50));
    t->paperbutton->setIcon(QIcon(QPixmap(Dir+"/DATA/icons/papers/"+t->papername+"on.jpeg")));
    t->paperbutton->setStyleSheet("background-color: blue");
    t->paperbutton->setObjectName(t->papername);
    ind--;
    int lin = (ind / 4);
    int col = ind - (ind / 4) * 4;
    t->paperbutton->move(QPoint(20+col*165,20+lin*65));
    t->paperbutton->installEventFilter(par);
    t->paperbutton->show();
    return t;
}

void Aialgbutton::Add(Aialgbutton* tmp) {
    Aialgbutton* t = this;
    while(t->next != NULL)
        t = t->next;
    t->next = tmp;
    t = NULL;
}

Aialgbutton* Aialgbutton::Item(int i) {
    if(i > count() || i < 0)
        return NULL;
    Aialgbutton* tmp = this;
    for(int j = 1;j <= i;j++)
        tmp = tmp->next;
    return tmp;
}

int Aialgbutton::Item(QString test) {
    int position(0);
    Aialgbutton* tmp = this;
    bool found(true);
    while(found && tmp->next != NULL) {
        position++;
        tmp = tmp->next;
        if(tmp->paperbutton->objectName() == test)
            found = false;
    }
    if(!found)
        return position;
    else
        return 0;
}

int Aialgbutton::count(void) {
    Aialgbutton* t = this;
    int i(0);
    while(t->next != NULL) {
        t = t->next;
        i++;
    }
    return i;
}

void Aialgbutton::DelItem() {
    Aialgbutton* tmp1 = Item(count()-1);
    Aialgbutton* tmp2 = Item(count());
    tmp1->next = NULL;
    tmp2->paperbutton->hide();
    delete tmp2;
}

void Aialgbutton::Delete() {
    while(next != NULL)
        DelItem();
}

QString Aialgbutton::name(void) {
    return papername;
}

QString Aialgbutton::link(void) {
    return paperlink;
}

QString Aialgbutton::downloadlink(void) {
    return paperdownloadlink;
}

void Aialgbutton::setname(QString tmp) {
    papername = tmp;
}

void Aialgbutton::setlink(QString tmp) {
    paperlink = tmp;
}

void Aialgbutton::setdownloadlink(QString tmp) {
    paperdownloadlink = tmp;
}

void Aialgbutton::Load(QWidget* parent, QString Dir) {
    //Load paper data
    QFile file(Dir+"/DATA/newspapers/information/newspapersdata");
    Delete();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    int ind(0);
    QString tmpupdate = QString::fromUtf8(file.readLine());
    while(!file.atEnd()) {
        QString name = "",link = "",downloadlink = "";
        int i = 0;
        if(!file.atEnd()) {
            i++;
            name = QString::fromUtf8(file.readLine());
        }
        if(!file.atEnd()) {
            i++;
            link = QString::fromUtf8(file.readLine());
        }
        if(!file.atEnd()) {
            i++;
            downloadlink = QString::fromUtf8(file.readLine());
        }
        if(i == 3) {
            ind++;
            name.remove("\n");
            link.remove("\n");
            downloadlink.remove("\n");
            //Setting button paper
            Add(setup(parent,ind,name,link,downloadlink,Dir));
            //End setting button paper
        }
    }
    file.close();
    //End Load paper data
    setbrowseconnect();
}

void Aialgbutton::browse() {
    QProcess browse;
    QString browser;
    browse.start(algepapdirectory+"/DATA/bin/browse");
    while(browse.waitForFinished()) {
        browser = browse.readAll();
    }
    browse.close();
    if(!browser.isEmpty()) {
        browser.remove("\n");
        browse.startDetached(browser,QStringList(paperlink));
        while(browse.waitForFinished())
            sleep(1);
        browse.close();
    }
}

void Aialgbutton::setbrowseconnect(void) {
    for(int i = 1;i <= count();i++)
        connect(Item(i)->paperbutton,SIGNAL(clicked()),Item(i),SLOT(browse()));
}
