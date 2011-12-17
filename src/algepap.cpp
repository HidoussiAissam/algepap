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
#include "algepap.h"

AlgePap::AlgePap(QWidget *parent, QString DirPath) :
    QWidget(parent)
{
    setMouseTracking(true);
    this->DirPath = DirPath;

    //////////////////////////////////
    buttons = new Aialgbutton(this);
    buttons->Load(this,DirPath);

    int lin = (buttons->count() / 4);
    if(buttons->count() % 4 != 0)
        lin++;
    int hi = 40 + lin*65;
    int wi = 50 + 4*165;
    setMinimumSize(wi,hi);
    setMaximumSize(wi,hi);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(DirPath+"/DATA/images/background/background.jpeg")));
    this->setPalette(palette);

}

AlgePap::~AlgePap()
{
}

bool AlgePap::eventFilter(QObject* watched, QEvent* event)
{
    QPushButton* btn = dynamic_cast<QPushButton*>(watched);
    Q_ASSERT(btn);
    if (event->type() == QEvent::Enter) {
        btn->setStyleSheet("background-color: yellow");
        setCursor(Qt::PointingHandCursor);
        return true;
    }
    else if (event->type() == QEvent::Leave) {
        btn->setStyleSheet("background-color: blue");
        setCursor(Qt::ArrowCursor);
        return true;
    }
    else
        return false;
}
