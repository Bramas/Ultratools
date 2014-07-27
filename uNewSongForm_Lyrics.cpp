/****************************************************************************
**
** Author & Contact: Quentin BRAMAS ( contact@bramas.fr )
**
** This file is part of Ultratools.
**
** GNU General Public License Usage
** ExUlt is free software: you can redistribute it and/or modify it under the
** terms of General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** ExUlt is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** If you have questions regarding the use of this file, please contact
** Quentin BRAMAS (contact@bramas.fr).
**
****************************************************************************/


#include "uNewSongForm_Lyrics.h"
#include "ui_uNewSongForm_Lyrics.h"

UNewSongForm_Lyrics::UNewSongForm_Lyrics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UNewSongForm_Lyrics)
{
    ui->setupUi(this);
    connect(ui->commandLinkButton,SIGNAL(clicked()),this,SLOT(close()));
}

UNewSongForm_Lyrics::~UNewSongForm_Lyrics()
{
    delete ui;
}

QString UNewSongForm_Lyrics::getText()
{

     return ui->plainTextEdit->toPlainText();
}

void UNewSongForm_Lyrics::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
