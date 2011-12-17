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
#include "updatealgepap.h"

UpdateAlgePap::UpdateAlgePap(QString Dir,int* languageindex) :
    QWidget(NULL)
{
    //Initialize data
    initializedata(Dir,languageindex);
    //Initialize GUI
    initializegui();
    //load Settings
    loadsettings();
}

void UpdateAlgePap::initializedata(QString Dir,int* languageindex) {
    DirPath = Dir;
    this->languageindex = languageindex;
    updatealgepapwindowlabel[0] = "Update databases";
    updatealgepapwindowlabel[1] = QString::fromUtf8("تحديث قاعدة البيانات");
    settings = new QSettings("AlgePap","UpdateAlgePap");
    llabel[0] = "Last Updat : " + settings->value("Update/LastUpdate","Never").toString();
    llabel[1] =  QString::fromUtf8("أخر تحديث : ") + settings->value("Update/LastUpdatear",QString::fromUtf8("أبدا")).toString();
    delete(settings);
    blabel[0] = "Update";
    blabel[1] = QString::fromUtf8("تحديث");
}

void UpdateAlgePap::initializegui() {
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setWindowIcon(QIcon(QPixmap(DirPath+"/DATA/icons/algepap.png")));
    QVBoxLayout* layoutt = new QVBoxLayout();
    l = new QLabel(this);
    layoutt->addWidget(l);
    b = new QPushButton(this);
    layoutt->addWidget(b);
    setLayout(layoutt);;
    //Connect Signals
    languageChange(*languageindex);
    connect(b,SIGNAL(clicked()),this,SLOT(updatedata()));
}

void UpdateAlgePap::loadsettings() {
    settings = new QSettings("AlgePap","AlgePap",this);
    languageChange(*languageindex);
    resize(settings->value("updatealgepap/size",QSize(300,150)).toSize());
    QRect available_geom = QDesktopWidget().availableGeometry();
    QRect current_geom = frameGeometry();
    setGeometry(settings->value("updatealgepap/geometry",QRect(available_geom.width() / 2 - current_geom.width() / 2,
                                                      available_geom.height() / 2 - current_geom.height() / 2,
                                                      current_geom.width(),
                                                      current_geom.height())).toRect());
    delete settings;
}

void UpdateAlgePap::languageChange(int index) {
    setWindowTitle(updatealgepapwindowlabel[index]);
    l->setText(llabel[index]);
    b->setText(blabel[index]);
}

void UpdateAlgePap::savesettings() {
    settings = new QSettings("AlgePap","AlgePap",this);
    settings->setValue("updatealgepap/size",size());
    if(isVisible())
        settings->setValue("updatealgepap/geometry",geometry());
    delete settings;
}

QFile linkweb;
QFile linkdownload;

void UpdateAlgePap::updatedata() {

    updatemessage[0] << "Update failed, verify your Internet connexion ...";
    updatemessage[1] << QString::fromUtf8("فشل التحديث، تحقق من اتصال الانترنت ...");

    updatemessage[0] << "Your databases are up to date ...";
    updatemessage[1] << QString::fromUtf8("قاعدة البيانات حديثة ...");

    updatemessage[0] << " : was updated with succeed.\n";
    updatemessage[1] << QString::fromUtf8(" : تم تحديثها بنجاح.\n");

    updatemessage[0] << " : not updated (shucksums failed).\n";
    updatemessage[1] << QString::fromUtf8(" : لم يتم تحديثها (تشفير الملف خاطئ).\n");

    updatemessage[0] << " : not updated (connexion failed).\n";
    updatemessage[1] << QString::fromUtf8("لم يتم تحديثها (الاتصال فشل).\n");

    if(!checkupdate()) {
        QMessageBox::information(this, updatealgepapwindowlabel[*languageindex],
                 updatemessage[*languageindex].at(0));
        return;
    }

    if(!linkdownload.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    if(linkdownload.atEnd()) {
        QMessageBox::information(this, updatealgepapwindowlabel[*languageindex],
                 updatemessage[*languageindex].at(1));
        iniVisible();
        return;
    }
    QString listresult("");
    QString loc, scope[2], link, hash;
        bool update(true);
    while(!linkdownload.atEnd()) {
        loc = scope[0] = scope[1] = link = hash = "";
        loc = QString::fromUtf8(linkdownload.readLine());
        scope[0] = QString::fromUtf8(linkdownload.readLine());
        link = QString::fromUtf8(linkdownload.readLine());
        hash = QString::fromUtf8(linkdownload.readLine());
        scope[1] = QString::fromUtf8(linkdownload.readLine());
        loc.remove("\n");
        scope[0].remove("\n");
        scope[0].remove("downloadscript/Dnd");
        scope[0].remove("information/Dni");
        link.remove("\n");
        hash.remove("\n");
        scope[1].remove("\n");
        QString linkupdate = "wget -t5 \""+link+"\" --output-document \""+DirPath+"/TMP/"+scope[0]+"\"";
        if(!system(linkupdate.toAscii().constData())) {
            QFile tmp(DirPath+"/TMP/"+scope[0]);
            if(!tmp.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QByteArray array = tmp.readAll();
            tmp.close();
            QString newhash(QCryptographicHash::hash(array,QCryptographicHash::Sha1).toHex());
            if(newhash == hash) {
                QString commandmv = "mv -f \""+DirPath+"/TMP/"+scope[0]+"\" \""+DirPath+loc+"\"";
                system(commandmv.toAscii().constData());
                listresult+=scope[*languageindex] + updatemessage[*languageindex][2];
            }
            else {
                listresult+=scope[*languageindex] + updatemessage[*languageindex][3];
                update = false;
            }
        }
        else {
            listresult+=scope[*languageindex] + updatemessage[*languageindex][4];
            update = false;
        }
    }
    l->setText(listresult);
    if(update) {
        settings = new QSettings("AlgePap","UpdateAlgePap");
        settings->setValue("Update/LastUpdate",QDate::currentDate().toString());
        settings->setValue("Update/LastUpdatear",QDate::currentDate().toString());
        delete(settings);
    }
}

QString UpdateAlgePap::getkey(QString path) {
    QFile keyvalue(path);
    if(!keyvalue.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";
    QString toreturn = QString::fromUtf8(keyvalue.readLine());
    keyvalue.close();
    return toreturn;
}

bool UpdateAlgePap::checkupdate() {
    //setting keys of existings files
    settings = new QSettings("AlgePap","UpdateAlgePap");
    directory.setPath(DirPath+"/DATA/newspapers/downloadscript");
    QStringList list = directory.entryList();
    for(int i = 2;i < list.count();i++)
        settings->setValue("downloadscript/Dnd"+list.at(i),
                           getkey(directory.path()+"/"+list.at(i)));
    settings->setValue("information/Dninewspapersdata",getkey(DirPath+"/DATA/newspapers/information/newspapersdata"));
    settings->setValue("information/Dninewspapersdataar",getkey(DirPath+"/DATA/newspapers/information/newspapersdataar"));
    //getting keys in web
    list.clear();
    QString linkupdate = "wget -t3 \"https://docs.google.com/document/d/1s0-6xfegMZWrTcdwJcf7zQPDzVblIdRDWSbTPSAOncY/export?format=txt&id=1s0-6xfegMZWrTcdwJcf7zQPDzVblIdRDWSbTPSAOncY&token=AC4w5Vgc6SGsKhrbXlGT0d2JwODk-XHK4Q:1303608416000&authkey=CMjSiN4G&tfe=yn_215\" --output-document \""+DirPath+"/TMP/AlgePapUpdate\"";
    linkweb.setFileName(DirPath+"/TMP/AlgePapUpdate");
    linkdownload.setFileName(DirPath+"/TMP/linkdownload");
    if(!system(linkupdate.toAscii().constData())) {
        if(!linkweb.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;
        if(!linkdownload.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
        QString loc = QString::fromUtf8(linkweb.readLine());
        loc = QString::fromUtf8(linkweb.readLine());
        while(!linkweb.atEnd() && loc != "END") {
            QString scope = QString::fromUtf8(linkweb.readLine());
            QString link = QString::fromUtf8(linkweb.readLine());
            QString key = QString::fromUtf8(linkweb.readLine());
            QString hash = QString::fromUtf8(linkweb.readLine());
            QString namear = QString::fromAscii(linkweb.readLine());
            scope.remove("\n");
            if(key != settings->value(scope,"").toString()) {
                linkdownload.write(loc.toAscii().constData());
                linkdownload.write(scope.toAscii().constData());
                linkdownload.write("\n");
                linkdownload.write(link.toAscii().constData());
                linkdownload.write(hash.toAscii().constData());
                linkdownload.write(namear.toAscii().constData());
            }
            loc = QString::fromUtf8(linkweb.readLine());
        }
        linkweb.close();
        linkdownload.close();
        delete settings;
        return true;
    }
    else
        return false;
}

void UpdateAlgePap::iniVisible() {
    if(isVisible()) {
        settings = new QSettings("AlgePap","UpdateAlgePap");
        llabel[0] = "Last Updat : " + settings->value("Update/LastUpdate","Never").toString();
        llabel[1] =  QString::fromUtf8("أخر تحديث : ") + settings->value("Update/LastUpdatear",QString::fromUtf8("أبدا")).toString();
        delete(settings);
        l->setText(llabel[*languageindex]);
    }
}
