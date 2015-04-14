/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Quentin Bramas <quentin@bramas.fr> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Quentin Bramas
 *
 * "LICENCE BEERWARE" (Révision 42):
 * Quentin Bramas <quentin@bramas.fr> a créé ce fichier. Tant que vous conservez cet avertissement,
 * vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
 * que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
 * retour. Quentin Bramas
 * ----------------------------------------------------------------------------
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
