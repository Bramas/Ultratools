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


#ifndef LYRICS_H
#define LYRICS_H


#include <QMultiMap>
#include "uWord.h"

class WordSelection;

class Lyrics : public QObject
{
    Q_OBJECT

signals:

    void hasBeenModified(void);
public slots:

    void doublePresicion();

public:


    Lyrics(QWidget * parent=0);
    void parseLine(QString &line);
    void parseCode(QString &code);

    void modified(QString sender="") { Q_UNUSED(sender); _modified=true; emit hasBeenModified(); }
    bool isModified() { return _modified; }
    void setModified(bool b=true) { if(b==true) modified(); else _modified=false; }


    const QMultiMap<int, Word>& words(void) const { return _words; }
    QMultiMap<int, Word>& words(void) { return _words; }

    int getPitchMax(void);
    int getPitchMin(void);
    void setGap(qreal in) { modified("setGap"); _gap = (in < 0 ? 0 : in); }
    qreal getGap(void) { return _gap; }
    void setBpm(float in) { _bpm = in; }
    qreal getBpm(void) { return _bpm; }

    Word addSeparator(int time);
    void removeWord(const Word &w);
    void addWord(const Word &w);

    QMap<int, Word>::const_iterator find(const Word &w);
    bool contains(const Word &w) { return _words.contains(w.getTime(), w); }

     QList<Word> separatorsOfWords(const QList<Word> &list) const;
     QList<Word> sentencesOfWord(const Word &w) const;

     bool setDelay(int delay, quint64 from=0);
     qreal timeToBeat(quint64 time)
     {
         return (time/1000.0) * _bpm/15.0f;
     }
     quint64 beatToMsc(int n)
     {
          return _gap + (n)*1000.0 * 15.0f/_bpm;
     }





private:
    QWidget * parent;
    QMultiMap<int, Word> _words;

    bool _modified;

    int  pitchMax, pitchMin;
    qreal _gap;
    qreal _bpm;

    QList<WordSelection*> _selections;
    friend class WordSelection;
};

#endif // LYRICS_H
