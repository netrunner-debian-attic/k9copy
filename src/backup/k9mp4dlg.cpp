//
// C++ Implementation:
//
// Description:
//
//
// Author: Jean-Michel PETIT <k9copy@free.fr>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "k9mp4dlg.h"
#include <qlabel.h>
#include <QProgressBar>
#include <qpainter.h>
#include <qlayout.h>
#include "k9drawimage.h"
#include "k9logview.h"
#include <kdialog.h>
#ifndef BACKLITE
#include <kstandarddirs.h>
#endif

k9MP4Dlg::k9MP4Dlg(QWidget* parent)
        : QDialog(parent) {
    Ui_MP4Dlg.setupUi(this);
    setModal(true);
    setWindowTitle(KDialog::makeStandardCaption(i18n("Encoding"),this));
    m_wimage=new k9DrawImage(Ui_MP4Dlg.image);
    QGridLayout *l=new QGridLayout(Ui_MP4Dlg.image);
    l->addWidget(m_wimage,0,0);
    l = new QGridLayout(Ui_MP4Dlg.tabLog);
    k9LogView *log=new k9LogView(Ui_MP4Dlg.tabLog);
    l->setSpacing(6);
    l->setMargin(0);
    l->addWidget(log, 0, 0, 1, 1);

    m_timer.start();
#ifndef BACKLITE
    Ui_MP4Dlg.bCancel->setGuiItem(KStandardGuiItem::Stop);
#else
    Ui_MP4Dlg.bCancel->setText(i18n("Stop"));
    Ui_MP4Dlg.bCancel->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
#endif
}

k9MP4Dlg::~k9MP4Dlg() {
}

/*$SPECIALIZATION$*/

void k9MP4Dlg::Cancel() {
    //QDialog::accept();
    emit sigCancel();
}

void k9MP4Dlg::setTitleLabel(QString _titleLabel) {
    Ui_MP4Dlg.lblTitle->setText(_titleLabel);
}


void k9MP4Dlg::setfps(QString _fps) {
    Ui_MP4Dlg.lblfps->setText(_fps);
}

void k9MP4Dlg::setremain(QString _remain) {
    if (m_timer.elapsed() >=1000) {
        Ui_MP4Dlg.lblRemain->setText(_remain);
        m_timer.restart();
    }
}

void k9MP4Dlg::setProgress(int _progress) {
    Ui_MP4Dlg.pbProgress->setValue(_progress);

}

void k9MP4Dlg::setbitrate(QString _bitrate) {
    Ui_MP4Dlg.lblbitrate->setText(_bitrate);
}

void k9MP4Dlg::setsize( QString _size) {
    Ui_MP4Dlg.lblsize->setText(_size);
    Ui_MP4Dlg.lbllabelSize->setHidden(_size.isEmpty());
}


void k9MP4Dlg::setImage(QString _fileName) {
    m_wimage->setImage(_fileName);
}

