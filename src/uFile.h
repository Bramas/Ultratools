/* Copyright (c) 2015 Quentin Bramas
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef UFILE_H
#define UFILE_H

#include <QFile>
#include "uLyrics.h"
class QMainWindow;

class UFile : public QObject
{

    Q_OBJECT

signals:
void bpmChanged(int);
void gapChanged(double);
void hasBeenModified(bool);

public slots:

bool saveInFile(QString fileName="",bool autoSave=false);
void autoSave();
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

    QString getMp3Location(void) { return _fileName.section('/',0,-2) + "/" +_headMp3; }
    QString getFileName(void) { return _fileName; }


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
    double _headVideogap;
    double _headGap;
    double _headBpm;
    void setBpm(double n){ lyrics->setBpm(n); _headBpm=n; emit bpmChanged(n); modified(); };
    void setGap(double n){ lyrics->setGap(n); _headGap=n; emit gapChanged(n); modified(); };
    double getBpm(){  return _headBpm; }
    double getGap(){  return _headGap; }

    ~UFile(void);
private:

    void extractHead(void);
    QMainWindow * _parent;
    QString _fileName;
    int _hMax;
    bool _modified;





};

#endif // UFILE_H
