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


#ifndef UFILE_H
#define UFILE_H

#include <QFile>
class QMainWindow;
#include "uShowSentenceWydget.h"

class UFile : public QObject
{

    Q_OBJECT

signals:
void bpmChanged(int);
void gapChanged(float);
void hasBeenModified(bool);

public slots:

bool saveInFile(QString fileName="",bool autoSave=false);
void autoSave(QString fileName="");
void modified() {  emit hasBeenModified(true); _modified=true; }
void doublePrecision(void) { lyrics->doublePresicion(); setBpm(getBpm()*2); }

public:


    QString plainText();

    bool isModified() { return _modified || lyrics->isModified();  }
    QString getBAK() { return _fileName + "_BAK";  }

    void cleanBAK(void) { if(QFile::exists(getBAK()))
        {
            QFile::remove(getBAK());
        } };

    void setFileName(QString f);
    void editHeader(void);
    UFile(QMainWindow * parent);
    UFile(QMainWindow * parent, QString fileName);
    int getMax(void);

    QString getMp3Location(void) { return _fileName.section('/',0,-2) + "/" +_headMp3; };
    QString getFileName(void) { return _fileName; };

    qreal timeToBeat(quint64 time);
   // static qreal timeToBeat(quint64 time, Lyrics * l) { return (time/1000.0) * l->getBpm()/15.0f; };
    quint64 beatToMsc(int n);

    Lyrics *lyrics;
    QString sourceCode;


    QString _headMp3;
    QString _headVideo;
    QString _headAuthor;
    QString _headTitle;
    QString _headArtist;
    QString _headCover;
    QString _headBackground;
    QString _headGenre;
    QString _headEdition;
    QString _headLanguage;
    QString _headYear;
    float _headVideogap;
    float _headGap;
    float _headBpm;
    void setBpm(float n){ lyrics->setBpm(n); _headBpm=n; emit bpmChanged(n); };
    void setGap(float n){ lyrics->setGap(n); _headGap=n; emit gapChanged(n); };
    float getBpm(){  return _headBpm; }


    ~UFile(void);
private:

    void extractHead(void);
    QMainWindow * _parent;
    QString _fileName;
    int _hMax;
    bool _modified;





};

#endif // UFILE_H
