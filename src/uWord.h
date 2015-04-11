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

#ifndef WORD_H
#define WORD_H

#include "uSetting.h"


class Lyrics;

class Word
{
public:
    typedef enum Type { Default = 7, Normal = 1, Free = 2, Gold = 4, Separator = 8 } Type;

    Word(Lyrics * parent,int time,int length, int pitch, Word::Type type = Word::Normal);


    int setTime(int newTime, bool definitly = true);
    int getTime(void) const  { return getTime1(); }
    int getTime1(void) const { return _time; }
    int getTime2(void) const { return _time + _length; }

    int setLength(int newlength, bool definitly = true);
    int getLength(void) const;
    int setPitch(int newPitch, bool definitly = true);
    int getPitch(void) const;

    void setOctaveOffset(int newOctave, bool definitly = true);
    int getOctaveOffset(void) const;

    void setGold(bool newGold=true);
    bool isGold(void) const { return _type & Word::Gold; }
    bool isFree(void) const { return _type & Word::Free; }
    void setFree(bool in=true);
    bool isSeparator() const { return _type & Word::Separator; }
    Lyrics * getParent() { return _parent; }
    void setParent(Lyrics * par);

    void setText(QString text);
    QString getText(void) const { return _text; }
    void setSelected(bool selected = true) { _selected = selected; }
    bool isSelected(void) const { return _selected; }

    bool hasBeenModified(void) { return _oTime!=_time || _oPitch!=_pitch || _oLength!=_length; }



    int getOTime() const { return _oTime; }
    int getOPitch() const { return _oPitch; }
    int getOLength() const { return _oLength; }

    void hold(void);

    void setOver(quint8 n) { _over = n; }
    quint8 getOver(void) const { return _over; }


    bool equal(const Word& t2) const
    {
        return (this->getLength()  ==t2.getLength()
                && this->getPitch()==t2.getPitch()
                && this->getTime() ==t2.getTime()
                && this->getText() ==t2.getText());
    }
    bool operator==(const Word& t2) const
    {
        return this->equal(t2);
    }
    bool operator!=(const Word& t2) const
    {
        return !this->equal(t2);
    }


    static bool wordLessThanPtr(const Word * a,const Word * b);

private:

    bool _selected;
    Lyrics * _parent;

    quint8 _over;
    int _oTime;
    int _oPitch;
    int _oLength;

    Word::Type _type;
    int _time;
    int _length;
    int _pitch;
    int _octaveOffset;
    QString _text;






public:
    static QPair<int,int> rangeTime(QList<Word*> * wlist);
    static int minIndexOfWords(QList<Word*>,QList<Word*>);
    static int maxIndexOfWords(QList<Word*>,QList<Word*>);
    static int indexOfWord(const QList<Word*> & list, Word * word);


};




#endif // WORD_H
