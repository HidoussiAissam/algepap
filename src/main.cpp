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
#include <QtGui/QApplication>
#include "algepapmain.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QProcess* algepapcheck = new QProcess(NULL);
    QByteArray* algepapcheckreturn = new QByteArray(NULL);
    int *j = new int(0);
    int *countofalgepapruned = new int(0);
    algepapcheck->start("/bin/ps -e");
    while(algepapcheck->waitForReadyRead()) {
        algepapcheckreturn->append(algepapcheck->readAll());
    }
    while ((*j = algepapcheckreturn->indexOf("algepap", *j)) != -1) {
        (*countofalgepapruned)++;
        ++(*j);
    }
    delete algepapcheck;
    delete algepapcheckreturn;
    delete j;

    //Q_INIT_RESOURCE(algepap);

    QApplication a(argc, argv);

    if(*countofalgepapruned > 1) {
        QMessageBox::information(0, QObject::tr("AlgePap"),
                              QObject::tr("Algepap is already runing .....         "));
        return 0;
    }
    delete countofalgepapruned;

    //checking user data status
    QDir* DATADIR = new QDir(QDir::home().path()+"/.algepap");
    if(!DATADIR->exists())
    {
        DATADIR->mkdir(DATADIR->path());
        if(!DATADIR->exists("/usr/share/algepap/DATA"))
            return 0;
        system(QString("cp -r /usr/share/algepap/DATA "+DATADIR->path()).toAscii().data());
        DATADIR->mkdir(DATADIR->path()+"/TMP");
    }

    QString* browse = new QString(DATADIR->path()+"/DATA/bin/browse");
    QString* downloadnews = new QString(DATADIR->path()+"/DATA/bin/downloadnewspapers");
    QString* desktop = new QString(DATADIR->path()+"/DATA/bin/desktop");
    chmod(browse->toLatin1().constData(),0755);
    chmod(downloadnews->toLatin1().constData(),0755);
    chmod(desktop->toLatin1().constData(),0755);
    delete browse;
    delete downloadnews;
    delete desktop;
    delete DATADIR;
    a.setApplicationVersion("1.0");
    a.setApplicationName("algepap");
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("AlgePap"),
                              QObject::tr("AlgePap couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);
    AlgePapMain *w = new AlgePapMain(NULL,QDir::home().path()+"/.algepap");
    w->show();
    return a.exec();
}
