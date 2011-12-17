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
#include "downloadalgepap.h"

DownloadAlgePap::DownloadAlgePap(QString Dir, int* language) :
    QWidget(NULL)
{
    setupdownloadalgepap(Dir,language);
    setupdownloadalgepapwidget();
    loadsettings();
}

void DownloadAlgePap::setupdownloadalgepap(QString Dir,int* language) {
    setObjectName(QString::fromUtf8("DownloadAlgePap"));
    downloadalgepapwindowtitle[0] = "Download newspapers";
    downloadalgepapwindowtitle[1] = QString::fromUtf8("تحميل الجرائد");
    selectlabel[0] = "Select ALL";
    selectlabel[1] = QString::fromUtf8("تحديد الكل");
    clearlabel[0] = "Deselect All";
    clearlabel[1] = QString::fromUtf8("الغاء تحديد الكل");
    linelabellabel[0] = "Save to :";
    linelabellabel[1] = QString::fromUtf8("حفظ الى :");
    downloadlabel[0] = "Download";
    downloadlabel[1] = QString::fromUtf8("تحميل");
    wgetlabel[0] = "wget";
    wgetlabel[1] = QString::fromUtf8("ويڤات");
    gwgetlabel[0] = "gwget";
    gwgetlabel[1] = QString::fromUtf8("جيويڤات");
    kgetlabel[0] = "kget";
    kgetlabel[1] = QString::fromUtf8("كڤات");
    browserlabel[0] = "browser";
    browserlabel[1] = QString::fromUtf8("المتصفح");
    DirPath = Dir;
    languageindex = language;
    setWindowIcon(QIcon(QPixmap(DirPath+"/DATA/icons/algepap.png")));
}

QHBoxLayout* layoutt;
QHBoxLayout* leftdown;
QHBoxLayout* leftmid;
QHBoxLayout* leftup;

void DownloadAlgePap::setupdownloadalgepapwidget() {
    layoutt = new QHBoxLayout();
    QHBoxLayout* right = new QHBoxLayout();
    QVBoxLayout* left = new QVBoxLayout();
    leftdown = new QHBoxLayout();
    leftmid = new QHBoxLayout();
    leftup = new QHBoxLayout();
    select = new QPushButton(this);
    leftup->addWidget(select);
    clear = new QPushButton(this);
    leftup->addWidget(clear);
    left->addLayout(leftup);
    linelabel = new QLabel(this);
    leftmid->addWidget(linelabel);
    linedialog = new QLineEdit(this);
    leftmid->addWidget(linedialog);
    bdialog = new QToolButton(this);
    bdialog->setText("...");
    connect(bdialog,SIGNAL(clicked()),SLOT(bdialogclick()));
    leftmid->addWidget(bdialog);
    left->addLayout(leftmid);
    iconComboBox = new QComboBox;
    leftdown->addWidget(iconComboBox);
    connect(iconComboBox,SIGNAL(currentIndexChanged(int)),SLOT(setsavelocationenabled(int)));
    download = new QPushButton(this);
    connect(download,SIGNAL(clicked()),SLOT(downloadclick()));
    leftdown->addWidget(download);
    left->addLayout(leftdown);
    QSpacerItem* leftspace = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layoutt->addItem(leftspace);
    layoutt->addLayout(left);
    list = new QListWidget(this);
    right->addWidget(list);
    layoutt->addLayout(right);
    QSpacerItem* rightspace = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layoutt->addItem(rightspace);
    setLayout(layoutt);
    connect(select,SIGNAL(clicked()),SLOT(selectclick()));
    connect(clear,SIGNAL(clicked()),SLOT(clearclick()));
}

void DownloadAlgePap::loadsettings() {
    settings = new QSettings("AlgePap","AlgePap",this);
    resize(settings->value("downloadalgepap/size",QSize(600,400)).toSize());
    QRect available_geom = QDesktopWidget().availableGeometry();
    QRect current_geom = frameGeometry();
    setGeometry(settings->value("downloadalgepap/geometry",QRect(available_geom.width() / 2 - current_geom.width() / 2,
                                                      available_geom.height() / 2 - current_geom.height() / 2,
                                                      current_geom.width(),
                                                      current_geom.height())).toRect());
    int svtmp(settings->value("downloadalgepap/index",0).toInt());
    if(linedialog->isEnabled())
        linedialog->setText(settings->value("downloadalgepap/savelocation",DirPath+"/Downloads").toString());
    //Load paper data
    QFile file(DirPath+"/DATA/newspapers/information/newspapersdata");
    QFile filear(DirPath+"/DATA/newspapers/information/newspapersdataar");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    if (!filear.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    while(list->count() > 0)
        list->clear();
    QString tmpupdate = QString::fromUtf8(file.readLine());
    tmpupdate = QString::fromUtf8(filear.readLine());
    while(!file.atEnd()) {
        QString name = "",link = "",downloadlink = "";
        name = QString::fromUtf8(file.readLine());
        link = QString::fromUtf8(file.readLine());
        downloadlink = QString::fromUtf8(file.readLine());
        name.remove("\n");
        downloadlink.remove("\n");
        if(downloadlink != "NotEnabled") {
            QString namear("");
            namear = QString::fromUtf8(filear.readLine());
            namear.remove("\n");
            downloadname[0][list->count()] = downloadlink;
            downloadname[1][list->count()] = name;
            downloadname[2][list->count()] = namear;
            QListWidgetItem* item = new QListWidgetItem(/*name*/);
            item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            if(settings->value("downloadalgepap/"+name,false).toBool())
                item->setCheckState(Qt::Checked);
            else
                item->setCheckState(Qt::Unchecked);
            list->addItem(item);
        }
    }
    file.close();
    filear.close();
    //End Load paper data    
    delete settings;
    languageChange(*languageindex);
    iconComboBox->setCurrentIndex(svtmp);
}

void DownloadAlgePap::languageChange(int index) {
    setWindowTitle(downloadalgepapwindowtitle[index]);
    select->setText(selectlabel[index]);
    clear->setText(clearlabel[index]);
    linelabel->setText(linelabellabel[index]);
    linelabel->adjustSize();
    layoutt->setDirection(index?QBoxLayout::RightToLeft:QBoxLayout::LeftToRight);
    leftdown->setDirection(index?QBoxLayout::RightToLeft:QBoxLayout::LeftToRight);
    leftmid->setDirection(index?QBoxLayout::RightToLeft:QBoxLayout::LeftToRight);
    leftup->setDirection(index?QBoxLayout::RightToLeft:QBoxLayout::LeftToRight);
    download->setText(downloadlabel[index]);
    int svtmp(iconComboBox->currentIndex());
    while(iconComboBox->count() > 0)
        iconComboBox->removeItem(iconComboBox->count() - 1);
    iconComboBox->setLayoutDirection(index?Qt::RightToLeft:Qt::LeftToRight);
    iconComboBox->addItem(QIcon(DirPath+"/DATA/icons/downloaders/wget.jpeg"), wgetlabel[index]);
    iconComboBox->addItem(QIcon(DirPath+"/DATA/icons/downloaders/gwget.jpeg"), gwgetlabel[index]);
    iconComboBox->addItem(QIcon(DirPath+"/DATA/icons/downloaders/kget.jpeg"), kgetlabel[index]);
    iconComboBox->addItem(QIcon(DirPath+"/DATA/icons/downloaders/browser.jpeg"), browserlabel[index]);
    iconComboBox->setCurrentIndex(svtmp);
    list->setLayoutDirection(index?Qt::RightToLeft:Qt::LeftToRight);
    for(int i = 0;i < list->count();i++)
        list->item(i)->setText(downloadname[index + 1][i]);
}

void DownloadAlgePap::savesettings() {
    settings = new QSettings("AlgePap","AlgePap",this);
    if(this->isVisible()) {
        settings->setValue("downloadalgepap/size",size());
        settings->setValue("downloadalgepap/geometry",geometry());
        settings->setValue("downloadalgepap/index",iconComboBox->currentIndex());
    }
    if(linedialog->isEnabled())
        settings->setValue("downloadalgepap/savelocation",linedialog->text());
    for(int i = 0;i < list->count();i++)
        if(list->item(i)->checkState() == Qt::Checked)
            settings->setValue("downloadalgepap/"+downloadname[1][i],true);
        else
            settings->setValue("downloadalgepap/"+downloadname[1][i],false);
    delete settings;
}

void DownloadAlgePap::selectclick() {
    for(int i = 0;i < list->count();i++)
        list->item(i)->setCheckState(Qt::Checked);
}

void DownloadAlgePap::clearclick() {
    for(int i = 0;i <list->count();i++)
        list->item(i)->setCheckState(Qt::Unchecked);
}

void DownloadAlgePap::downloadclick() {
    hide();
if(!IsNoItemChecked()) {
    //Create download script
    QFile file(DirPath+"/DATA/bin/downloadnewspapers");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;
    QString stringtmp;
    file.write("#!/bin/bash\n");
    file.write("#################################################################\n");
    file.write("#								#\n");
    file.write("# 		Download Algerian newspapers script		#\n");
    file.write("#    	   http://djelfa.info/vb/forumdisplay.php?f=210 	#\n");
    file.write("#			By : أخ المسلمين			#\n");
    file.write("#								#\n");
    file.write("#	This script is generated by the AlgePap	program		#\n");
    file.write("#		    Don't modify it manually			#\n");
    file.write("#################################################################\n");
    stringtmp="tmpfolder=\""+DirPath+"/TMP/tmp\"\n";
    file.write(stringtmp.toAscii().constData());
    stringtmp="cd "+DirPath+"/TMP\n";
    file.write(stringtmp.toAscii().constData());
    file.write("rm -f $tmpfolder\"link\"\n");
    for(int i = 0;i < list->count();i++) {
        if(list->item(i)->checkState() == Qt::Checked) {
            QFile filetmp(DirPath+"/DATA/newspapers/downloadscript/"+downloadname[1][i]);
            if (!filetmp.open(QIODevice::ReadOnly | QIODevice::Text))
                     return;
            QString tmpupdate = QString::fromUtf8(filetmp.readLine());
            while(!filetmp.atEnd()) {
                stringtmp = QString::fromUtf8(filetmp.readLine());
                file.write(stringtmp.toAscii().constData());
            }
            filetmp.close();
            stringtmp = "\nif [ \"$"+downloadname[1][i]+"_downloadlink\" != \"\" ]; then\n";
            file.write(stringtmp.toAscii().constData());
            stringtmp = "echo \""+downloadname[0][i]+"\" >> $tmpfolder\"link\"\n";
            file.write(stringtmp.toAscii().constData());
            stringtmp = "echo $"+downloadname[1][i]+"_downloadlink >> $tmpfolder\"link\"\n";
            file.write(stringtmp.toAscii().constData());
            file.write("fi\n");
        }
    }
    file.write("exit 0");
    file.close();
    //End Create download script
    //Lunch download script
    QProcess process(this);
    process.start(DirPath + "/DATA/bin/desktop");
    QString terminal;
    while(process.waitForFinished())
        terminal.append(process.readAll());
    if(terminal.contains("gnome-terminal"))
        terminal = "gnome-terminal";
    else if(terminal.contains("konsole"))
        terminal = "konsole";
    else
        return;

    stringtmp = terminal;
    if(terminal == "gnome-terminal")
        stringtmp+= " --disable-factory";
    stringtmp+=" --title \"AlgePap : getting links\" -e \""+DirPath+"/DATA/bin/downloadnewspapers\"";
    system(stringtmp.toAscii().constData());
    QFile file2(DirPath+"/TMP/tmplink");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    QStringList link;
    QStringList name;
    while(!file2.atEnd()) {
        QString linkdownload = "";
        QString linkname = "";
        linkname = QString::fromUtf8(file2.readLine());
        linkname.remove("\n");
        name << linkname;
        linkdownload = QString::fromUtf8(file2.readLine());
        linkdownload.remove("\n");
        link << linkdownload;
    }
    file2.close();
    if(!link.isEmpty()) {
        if(iconComboBox->currentIndex() == 0) {
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                     return;
            QString stringtmp;
            file.write("#!/bin/bash\n");
            file.write("#################################################################\n");
            file.write("#								#\n");
            file.write("# 		Download Algerian newspapers script		#\n");
            file.write("#    	   http://djelfa.info/vb/forumdisplay.php?f=210 	#\n");
            file.write("#			By : أخ المسلمين			#\n");
            file.write("#								#\n");
            file.write("#	This script is generated by the AlgePap	program		#\n");
            file.write("#		    Don't modify it manually			#\n");
            file.write("#################################################################\n");
            stringtmp = "savelocation="+linedialog->text()+"/\n";
            file.write(stringtmp.toAscii().constData());
            for(int i = 0;i < link.count();i++) {
                    stringtmp = "wget \""+link.at(i)+"\" --output-document $savelocation\""+name.at(i)+"\"\n";
                    file.write(stringtmp.toAscii().constData());
            }
            file.write("exit 0\n");
            file.close();
            QStringList stringlisttmp;
            if(terminal == "gnome-terminal")
                stringlisttmp << "--disable-factory";
            stringlisttmp << "--title" << "Download newspapers" << "-e" << DirPath+"/DATA/bin/downloadnewspapers";
            QProcess process(this);
            process.startDetached(terminal,stringlisttmp);
            while(process.waitForFinished())
                sleep(1);
        }
        else if(iconComboBox->currentIndex() == 3) {
            QProcess browse;
            QString browser;
            browse.start(DirPath+"/DATA/bin/browse");
            while(browse.waitForFinished()) {
                browser = browse.readAll();
            }
            browse.close();
            if(!browser.isEmpty()) {
                browser.remove("\n");
                browse.startDetached(browser,link);
                while(browse.waitForFinished())
                    sleep(1);
                browse.close();
            }
        }
        else if(iconComboBox->currentIndex() == 1) {
            QProcess process(this);
            link << "-d" << linedialog->text() << "-t";
            process.startDetached("gwget",link);
            while(process.waitForFinished())
                sleep(1);
        }
        else if(iconComboBox->currentIndex() == 2) {
            QProcess process(this);
            link << "--icon" << DirPath+"/DATA/icons/algepap.png";
            process.startDetached("kget",link);
            while(process.waitForFinished())
                sleep(1);
        }
    }
}
else {
    QString message[2];
    message[0] = "No newspaper is selected to download";
    message[1] = QString::fromUtf8("لم تقم بتحديد اي جريدة للتحميل");
    QMessageBox::information(this, downloadalgepapwindowtitle[*languageindex],
                          message[*languageindex]);
    showNormal();
}
}

void DownloadAlgePap::bdialogclick() {
    linedialog->setText(QFileDialog::getExistingDirectory(this, tr("Choose location to save the newspapers"),
                                                     DirPath+"/Downloads",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks));
}

bool DownloadAlgePap::IsNoItemChecked() {
    bool ret(true);
    for(int i = 0;i < list->count() && ret;i++) {
        if(list->item(i)->checkState() == Qt::Checked)
            ret = false;
    }
    return ret;
}

void DownloadAlgePap::setsavelocationenabled(int index) {
    if(index == 1 || index == 0) {
        linedialog->setEnabled(true);
        bdialog->setEnabled(true);
    }
    else {
        linedialog->setEnabled(false);
        bdialog->setEnabled(false);
    }
}

void DownloadAlgePap::closeEvent(QCloseEvent *event) {
    savesettings();
    event->accept();
}
