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
#include "algepapmain.h"

DownloadAlgePap* downloadalgepap;
AboutAlgePap* aboutalgepap;
UpdateAlgePap* updatealgepap;

AlgePapMain::AlgePapMain(QWidget *parent, QString Dir) :
    QMainWindow(parent)
{
    setupmain(Dir);
    setupalgepapbrowse();
    setupaction();
    setupmenu();
    setuptrayicon();
    loadsettings();
}

//پ

void AlgePapMain::setupmain(QString Dir) {
    algepapwindowtitle[0] = "AlgePap";
    algepapwindowtitle[1] = QString::fromUtf8("ألـجـيــپاپ");
    minimizeactionlabel[0] = "Mi&mimize";
    minimizeactionlabel[1] = QString::fromUtf8("تصغير");
    restoreactionlabel[0] = "&Restore";
    restoreactionlabel[1] = QString::fromUtf8("استرجاع");
    downloadactionlabel[0] = "&Download";
    downloadactionlabel[1] = QString::fromUtf8("تحميل");
    updateactionlabel[0] = "&Update";
    updateactionlabel[1] = QString::fromUtf8("تحديث");
    englishactionlabel[1] = QString::fromUtf8("الانجليزية");
    arabicactionlabel[0] = "&Arabic";
    arabicactionlabel[1] = QString::fromUtf8("العربية");
    setObjectName(QString::fromUtf8("AlgePap"));
    aboutactionlabel[0] = "A&bout";
    aboutactionlabel[1] = QString::fromUtf8("حول البرنامج");
    quitactionlabel[0] = "&Quit";
    quitactionlabel[1] = QString::fromUtf8("خروج");
    englishactionlabel[0] = "&English";
    setMouseTracking(true);
    DirPath = Dir;
    setWindowFlags(windowFlags() & ~Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(QPixmap(DirPath+"/DATA/icons/algepap.png")));
    downloadalgepap = NULL;
    aboutalgepap = NULL;
    updatealgepap = NULL;
    languageindex = new int();
}

void AlgePapMain::setupalgepapbrowse() {
    window = new AlgePap(this,DirPath);
    scrol = new QScrollArea(this);
    scrol->setWidgetResizable(true);
    scrol->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrol->setWidget(window);
    setCentralWidget(scrol);
}

void AlgePapMain::setupaction() {
    minimizeAction = new QAction(this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    restoreAction = new QAction(this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    downloadAction = new QAction(this);
    connect(downloadAction, SIGNAL(triggered()), this, SLOT(download()));
    updateAction = new QAction(this);
    connect(updateAction, SIGNAL(triggered()), this, SLOT(updateActionclick()));
    englishAction = new QAction(this);
    connect(englishAction, SIGNAL(triggered()), this, SLOT(englishActionclick()));
    englishAction->setCheckable(true);
    arabicAction = new QAction(this);
    connect(arabicAction, SIGNAL(triggered()), this, SLOT(arabicActionclick()));
    arabicAction->setCheckable(true);
    aboutAction = new QAction(this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutActionclick()));
    quitAction = new QAction(this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));
}

void AlgePapMain::setupmenu() {
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(downloadAction);
    trayIconMenu->addAction(updateAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(englishAction);
    trayIconMenu->addAction(arabicAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(aboutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
}

void AlgePapMain::setuptrayicon() {
    trayIcon = new QSystemTrayIcon(this);
    QIcon iconalgepap(QPixmap(DirPath+"/DATA/icons/algepap.png"));
    trayIcon->setIcon(iconalgepap);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void AlgePapMain::loadsettings() {
    settings = new QSettings("AlgePap","AlgePap",this);
    *languageindex = (settings->value("main/languageindex",0)).toInt();
    languageChange(*languageindex);
    englishAction->setChecked(*languageindex == 0?true:false);
    arabicAction->setChecked(*languageindex == 1?true:false);
    setMaximumSize(settings->value("main/size",QSize(50 + 4*165,42 + 6*65)).toSize());
    setMinimumSize(settings->value("main/size",QSize(50 + 4*165,42 + 6*65)).toSize());
    QRect available_geom = QDesktopWidget().availableGeometry();
    QRect current_geom = frameGeometry();
    setGeometry(settings->value("main/geometry",QRect(available_geom.width() / 2 - current_geom.width() / 2,
                                                      available_geom.height() / 2 - current_geom.height() / 2,
                                                      current_geom.width(),
                                                      current_geom.height())).toRect());
    scrol->resize(settings->value("main/size",QSize(50 + 4*165,42 + 6*65)).toSize());
    delete settings;
}

void AlgePapMain::languageChange(int index) {
    setWindowTitle(algepapwindowtitle[index]);
    minimizeAction->setText(minimizeactionlabel[index]);
    restoreAction->setText(restoreactionlabel[index]);
    downloadAction->setText(downloadactionlabel[index]);
    updateAction->setText(updateactionlabel[index]);
    englishAction->setText(englishactionlabel[index]);
    arabicAction->setText(arabicactionlabel[index]);
    aboutAction->setText(aboutactionlabel[index]);
    quitAction->setText(quitactionlabel[index]);
    trayIconMenu->setLayoutDirection(index?Qt::RightToLeft:Qt::LeftToRight);
}

void AlgePapMain::savesettings() {
    settings = new QSettings("AlgePap","AlgePap",this);
    settings->setValue("main/size",QSize(50 + 4*165,42 + 6*65));
    if(isVisible())
        settings->setValue("main/geometry",geometry());
    settings->setValue("main/languageindex",*languageindex);
    delete settings;
}


void AlgePapMain::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if(!this->isVisible())
            setVisible(true);
        break;
    default:
        ;
    }
}

void AlgePapMain::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    //maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(!visible);
    QWidget::setVisible(visible);
    if(aboutalgepap != NULL) {
        delete(aboutalgepap);
        aboutalgepap = NULL;
    }
}

void AlgePapMain::createMessageGroupBox()
{

    typeComboBox = new QComboBox;
    typeComboBox->addItem(tr("None"), QSystemTrayIcon::NoIcon);
    typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxInformation), tr("Information"),
            QSystemTrayIcon::Information);
    typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxWarning), tr("Warning"),
            QSystemTrayIcon::Warning);
    typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxCritical), tr("Critical"),
            QSystemTrayIcon::Critical);
    typeComboBox->setCurrentIndex(1);

}

void AlgePapMain::closeEvent(QCloseEvent *event)
{
    /*QMessageBox::information(this, tr("Algepap"),
         tr("The program will keep running in the "
            "system tray. To terminate the program, "
            "choose <b>Quit</b> in the context menu "
            "of the system tray entry."));*/
    hide();
    event->ignore();
}

void AlgePapMain::download() {
    if(downloadalgepap == NULL) {
        downloadalgepap = new DownloadAlgePap(DirPath,languageindex);
        downloadalgepap->show();
    }
    else
        downloadalgepap->show();
    setVisible(false);
}

void AlgePapMain::updateActionclick() {
    if(updatealgepap == NULL) {
        updatealgepap = new UpdateAlgePap(DirPath,languageindex);
        updatealgepap->show();
    }
    else {
        updatealgepap->show();
        updatealgepap->iniVisible();
    }
    setVisible(false);
}

void AlgePapMain::englishActionclick() {
    if(englishAction->isChecked()) {
        arabicAction->setChecked(false);
        *languageindex = 0;
        languageChange(*languageindex);
        if(downloadalgepap != NULL)
            downloadalgepap->languageChange(*languageindex);
        if(updatealgepap != NULL)
            updatealgepap->languageChange(*languageindex);
    }
    else
        englishAction->setChecked(true);
}

void AlgePapMain::arabicActionclick() {
    if(arabicAction->isChecked()) {
        englishAction->setChecked(false);
        *languageindex = 1;
        languageChange(*languageindex);
        if(downloadalgepap != NULL)
            downloadalgepap->languageChange(*languageindex);
        if(updatealgepap != NULL)
            updatealgepap->languageChange(*languageindex);
    }
    else
        arabicAction->setChecked(true);
}

void AlgePapMain::aboutActionclick() {
    if(aboutalgepap != NULL) {
        aboutalgepap->show();
    }
    else {
        aboutalgepap = new AboutAlgePap(DirPath);
        aboutalgepap->show();
    }
}

void AlgePapMain::quit() {
    savesettings();
    if(downloadalgepap != NULL) {
        downloadalgepap->close();
        delete(downloadalgepap);
    }
    if(aboutalgepap != NULL) {
        aboutalgepap->close();
        delete(aboutalgepap);
    }
    if(updatealgepap != NULL) {
        updatealgepap->close();
        delete(updatealgepap);
    }
    qApp->quit();
}
