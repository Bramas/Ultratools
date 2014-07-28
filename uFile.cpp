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


#include "uFile.h"
#include "uDialog_fileheader.h"
#include <QStatusBar>
#include <QMessageBox>
#include "editorwindow.h"

#define DEFAULT_GAP 0
#define DEFAULT_BPM 360



UFile::UFile(QMainWindow * parent)
{
    _parent = parent;
    lyrics=new Lyrics(parent);
    sourceCode="";
    _hMax=0;
    _headGap = DEFAULT_GAP;
    setBpm(DEFAULT_BPM);
    _headMp3 = "";
    _headVideo = "";
    _headAuthor = "";
    _headTitle = "";
    _headArtist = "";
    _headCover = "";
    _headBackground = "";
    _headVideogap=0;


    lyrics->setGap(_headGap);
    lyrics->setBpm(_headBpm);


    connect(lyrics,SIGNAL(hasBeenModified()),this,SLOT(modified()));

    lyrics->setModified(false);
    _modified=false;


}

UFile::UFile(QMainWindow * parent, QString fileName)
{
    _parent = parent;
    lyrics=new Lyrics(parent);
    sourceCode="";
    _hMax=0;

    _headGap = DEFAULT_GAP;
    setBpm(DEFAULT_BPM);
    _headMp3 = "";
    _headVideo = "";
    _headAuthor = "";
    _headTitle = "";
    _headArtist = "";
    _headCover = "";
    _headBackground = "";
    _headVideogap=0;


    connect(lyrics,SIGNAL(hasBeenModified()),this,SLOT(modified()));

    int * range;

_fileName=fileName;


if(QFile::exists(getBAK()))
{
    QMessageBox msgBox(parent);

    msgBox.setInformativeText(tr("Une version Backup du fichier est disponnible (probablement du a un plantage ou a une mauvaise fermeture)"));
    msgBox.setText(tr("Voullez-vous récupéré la version Backup?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Yes)
    {
        fileName = getBAK();
    }
}


        QFile file(fileName);
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {


             QMessageBox::warning(_parent,tr("Erreur"),tr("Impossible d'ouvrir le fichier : ")+"\n"+fileName);
             return;
         }

        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine() + "\n";
            sourceCode += line;
        }

        lyrics->parseCode(sourceCode);

        _hMax = lyrics->getPitchMax();

        extractHead();

        lyrics->setGap(_headGap);
        lyrics->setBpm(_headBpm);


        lyrics->setModified(false);
        _modified = false;

}

bool UFile::saveInFile(QString fileName, bool autoSave)
{

    if(!autoSave)
    {
        if(!fileName.length())
        {
            fileName = _fileName;

        }

        _fileName = fileName;
    }


    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(_parent,tr("Erreur"),tr("Impossible d'ouvrir le fichier : ")+"\n"+fileName);

          return false;
     }

    QTextStream out(&file);

    out<<"#TITLE:"<<_headTitle<< "\n";
    out<<"#ARTIST:"<<_headArtist<< "\n";
    out<<"#LANGUAGE:"<<_headLanguage<< "\n";
    out<<"#EDITION:"<<_headEdition<< "\n";
    out<<"#GENRE:"<<_headGenre<< "\n";
    out<<"#YEAR:"<<_headYear<< "\n";
    out<<"#CREATOR:"<<_headAuthor<< "\n";
    out<<"#MP3:"<<_headMp3<< "\n";
    out<<"#VIDEO:"<<_headVideo<< "\n";
    out<<"#VIDEOGAP:"<<_headVideogap<< "\n";
    out<<"#BACKGROUND:"<<_headBackground<< "\n";
    out<<"#COVER:"<<_headCover<< "\n";
    out<<"#BPM:"<<_headBpm<< "\n";
    out<<"#GAP:"<<_headGap<< "\n";
   // out<<"#END:"<<_headEnd<< "\n";

foreach(Word * w,lyrics->words())
{
    if(w->isSeparator())
    {
        out<<"- "<<w->getTime1();
        if(w->getLength())
        {
            out<<" "<<w->getTime2();
        }
        out<<"\n";
        continue;
    }
    if(w->isFree())
        out<<"F ";
    else
    if(w->isGold())
        out<<"* ";
    else
        out<<": ";

    out<<w->getTime()<<" "<<w->getLength()<<" "<<w->getPitch()<<" "<<w->getText()<<"\n";
}

out<<"E\n";

file.close();

if(!autoSave)
{
    _modified = false;

    _modified = false;
    lyrics->setModified(false);
    emit hasBeenModified(false);

    cleanBAK();
}


_parent->statusBar()->showMessage(tr("Musique sauvegardée avec succés"),20000);

return true;
}

UFile::~UFile(void)
{
    cleanBAK();
}

void UFile::extractHead()
{

    QStringList sl = sourceCode.split("\n#");

    if(sl.count() == 0)  QMessageBox::warning(NULL,tr("Erreur"),tr("Problème pour parser le fichier"));

    QString str;
    foreach(str,sl)
    {
        QString temp = str.section(':',0,0);
        temp.remove('#');

            if(!temp.compare("TITLE"))
            {
                _headTitle = str.section(':',1,1);
                continue;
            }
           if(!temp.compare("ARTIST"))
            {
                _headArtist = str.section(':',1,1);
                  continue;
            }
            if(!temp.compare("VIDEO"))
           {
                _headVideo = str.section(':',1,1);
                continue;
            }
           if(!temp.compare("MP3"))
            {
                _headMp3 = str.section(':',1,1);
                continue;
            }
            if(!temp.compare("COVER"))
            {
                _headCover = str.section(':',1,1);
                continue;
            }
            if(!temp.compare("BACKGROUND"))
            {
                _headBackground = str.section(':',1,1);
                continue;
            }
            if(!temp.compare("GAP"))
            {
                _headGap = str.section(':',1,1).replace(',','.').toFloat();
                continue;
            }
            if(!temp.compare("VIDEOGAP"))
            {
                _headVideogap = str.section(':',1,1).replace(',','.').toFloat();
                continue;
            }
            if(!temp.compare("BPM"))
            {
                _headBpm = str.section(':',1,1).replace(',','.').toFloat();
                continue;
            }
            if(!temp.compare("AUTHOR") || !temp.compare("CREATOR"))
            {
                _headAuthor = str.section(':',1,1);
                continue;
            }
            if(!temp.compare("COVER"))
            {
                _headCover = str.section(':',1,1);
                continue;
            }
            if(!temp.compare("GENRE"))
            {
                _headGenre = str.section(':',1,1);
                continue;
            }
            if(!temp.compare("LANGUAGE"))
            {
                _headLanguage = str.section(':',1,1);
                continue;
            }
            if(!temp.compare("YEAR"))
            {
                _headYear = str.section(':',1,1);
                continue;
            }


    }



}

int UFile::getMax()
{
    return _hMax;
}
void UFile::editHeader()
{
        UDialog_fileHeader * edit = new UDialog_fileHeader(_parent,this);
        edit->show();

        modified();
}
qreal UFile::timeToBeat(quint64 time)
{
    return (time/1000.0) * _headBpm/15.0f;
}


quint64 UFile::beatToMsc(int n)
{
     return _headGap + (n)*1000.0 * 15.0f/_headBpm;
}

void UFile::setFileName(QString f)
{
    _fileName = f;
}
void UFile::autoSave(QString fileName)
{

    saveInFile(getBAK(),true);

}
QString UFile::plainText()
{
    QString plainString = "";

    plainString+="#TITLE:"+_headTitle+ "\n";
    plainString+="#ARTIST:"+_headArtist+ "\n";
    plainString+="#LANGUAGE:"+_headLanguage+ "\n";
    plainString+="#EDITION:"+_headEdition+ "\n";
    plainString+="#GENRE:"+_headGenre+ "\n";
    plainString+="#YEAR:"+_headYear+ "\n";
    plainString+="#CREATOR:"+_headAuthor+ "\n";
    plainString+="#MP3:"+_headMp3+ "\n";
    plainString+="#VIDEO:"+_headVideo+ "\n";
    plainString+="#VIDEOGAP:"+QString::number(_headVideogap)+ "\n";
    plainString+="#BACKGROUND:"+_headBackground+ "\n";
    plainString+="#COVER:"+_headCover+ "\n";
    plainString+="#BPM:"+QString::number(_headBpm)+ "\n";
    plainString+="#GAP:"+QString::number(_headGap)+ "\n";
   // plainString+="#END:"+_headEnd+ "\n";


foreach(Word * w, lyrics->words())
{
    if(w->isSeparator())
    {
        plainString+="- "+QString::number(w->getTime1());
        if(w->getLength())
        {
            plainString+=" "+QString::number(w->getTime2());
        }
        plainString+="\n";
        continue;
    }
    if(w->isFree())
        plainString+="F ";
    else
    if(w->isGold())
        plainString+="* ";
    else
        plainString+=": ";

    plainString+=QString::number(w->getTime())+" "+QString::number(w->getLength())+" "+QString::number(w->getPitch())+" "+w->getText()+"\n";
}

plainString+="E\n";

return plainString;
}
