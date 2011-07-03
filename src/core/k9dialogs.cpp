/***************************************************************************
 *   Copyright (C) 2007 by Jean-Michel   *
 *   jm_petit@laposte.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "k9dialogs.h"
#include "k9common.h"
#include <QDebug>
#include <QString>
#ifdef BACKLITE
#include <QDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QMessageBox>
#else
#include <KDialog>
#include <KFileDialog>
#include <KMessageBox>
#include <KFontDialog>
#endif
#include <QApplication>
#include "k9tools.h"


QWidget * k9MainWidget;
void k9Dialogs::setMainWidget(QWidget *_widget) {
    k9MainWidget=_widget;
}

QWidget* k9Dialogs::getMainWidget() {
    return k9MainWidget;
}



QString k9Dialogs::getOpenFileName (const QString &_initialDir,const QString &_filter,QWidget *_parent,const QString &_title) {
#ifdef BACKLITE
        return QFileDialog::getOpenFileName ( _parent,_title,_initialDir,_filter);
#else
        return KFileDialog::getOpenFileName (_initialDir,_filter, _parent,_title);
#endif
}

QString k9Dialogs::getSaveFileName (const QString &_initialDir,const QString &_filter,QWidget *_parent,const QString &_title) {
#ifdef BACKLITE
        return QFileDialog::getSaveFileName ( _parent,_title,_initialDir,_filter);
#else
        return KFileDialog::getSaveFileName (_initialDir,_filter, _parent,_title);
#endif
}

QString k9Dialogs::getExistingDirectory (const QString &_initialDir) {
#ifdef BACKLITE
        return QFileDialog::getExistingDirectory(0,i18n("select a directory"),_initialDir);
#else
        return KFileDialog::getExistingDirectory (_initialDir);
#endif
}

void k9Dialogs::error(const QString &_message,const QString &_title,const QStringList &_detail) {
    if (k9Tools::getBatchCopy()) {
        k9log::writeln(QString("Error : %1\n%2").arg(_message).arg(_detail.join("\n")));
        return;
    }

    QWidget *activeWindow=QApplication::activeWindow();
    if (activeWindow==0)
	activeWindow=k9MainWidget;


#ifdef BACKLITE
    QMessageBox message(QMessageBox::Critical,_title,_message,QMessageBox::Ok,activeWindow) ;
    if (!_detail.isEmpty())
        message.setDetailedText(_detail.join("\n\r"));
    message.exec();
#else
    KMessageBox::errorList(activeWindow,_message,_detail,_title);
#endif
}

void k9Dialogs::information(const QString &_message, const QString &_title) {
    if (k9Tools::getBatchCopy()) {
        k9log::writeln(QString("Information : %1").arg(_message));
        return;
    }

    QWidget *activeWindow=QApplication::activeWindow();
    if (activeWindow==0)
	activeWindow=k9MainWidget;
#ifdef BACKLITE
    QMessageBox::information ( activeWindow,_title, _message);
#else
    KMessageBox::information(activeWindow,_message,_title);
#endif
}
int k9Dialogs::warningContinueCancel(const QString &  _message,const QString & _title,const QStringList &_detail) {
    QWidget *activeWindow=QApplication::activeWindow();
    if (activeWindow==0)
	activeWindow=k9MainWidget;

#ifdef BACKLITE
    QMessageBox message(QMessageBox::Warning,_title,_message,QMessageBox::Ignore | QMessageBox::Cancel,activeWindow) ;
    if (!_detail.isEmpty())
        message.setDetailedText (_detail.join("\n\r"));

    return message.exec();
#else
    return KMessageBox::warningContinueCancelList(activeWindow,_message,_detail,_title);
#endif

}

bool k9Dialogs::getFont(QFont &font) {
#ifdef BACKLITE
    bool ok;
    QFont res=QFontDialog::getFont ( &ok,font,k9MainWidget);
    if (ok) {
        font=res;
        return true;
    } else
        return false;
#else
    int result= KFontDialog::getFont( font );
    if (result==KFontDialog::Accepted)
        return true;
    else
        return false;
#endif
}
