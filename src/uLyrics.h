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
#include "undocommands.h"

class WordSelection;
class Lyrics;


class Lyrics : public QObject
{
    Q_OBJECT

signals:

    void hasBeenModified(void);
public slots:

    void doublePresicion();

public:

    class WordIterator;

    Lyrics(QWidget * parent=0);
    void parseLine(QString &line);
    void parseCode(QString &code);

    void modified(QString sender) {
        Q_UNUSED(sender);
        //_modified=true; emit hasBeenModified();
    }
    bool isModified() {
        return !_history.isClean();
        //return _modified;
                      }
    void setModified(bool b=true) {
        if(!b)
        {
            _history.setClean();
        }
        //if(b==true) modified(); else _modified=false;
    }


    const QMultiMap<int, Word>& words(void) const { return _words; }

    int getPitchMax(void);
    int getPitchMin(void);
    void setGap(qreal in) { modified("setGap"); _gap = (in < 0 ? 0 : in); }
    qreal getGap(void) { return _gap; }
    void setBpm(double in) { _bpm = in; }
    qreal getBpm(void) { return _bpm; }

    Word addSeparator(int time);
    void removeWord(const Word &w);
    void addWord(const Word &w, QString actionText="");

    QMap<int, Word>::const_iterator find(const Word &w);

    Lyrics::WordIterator wordBegin();
    Lyrics::WordIterator wordEnd();

    const QUndoStack & history() const { return this->_history; }

    bool contains(const Word &w) { return _words.contains(w.getTime(), w); }

     QList<Word> sentencesOfWord(const Word &w) const;

     /*!
      * \brief setDelay apply a delay to all words after time from
      * \param delay the delay to apply
      * \param from the time from which we apply the delay
      * \return the delay that is effectively applied. It may differ from the given delay because we cannot move words before gap or before a word with a time smaller than from
      */
     int setDelay(int delay, int from=0);


     qreal timeToBeat(quint64 time)
     {
         return (time/1000.0) * _bpm/15.0;
     }
     quint64 beatToMsc(int n)
     {
          return _gap + (n)*1000.0 * 15.0/_bpm;
     }

     void undo() { _history.undo(); }
     void redo() { _history.redo(); }

    void createEditGroup() { ++_editGroup; }


private:

    void emitModified() {
        emit hasBeenModified();
    }

    void reallyRemoveWord(const Word &w);
    void reallyAddWord(const Word &w);

     // Undo commands
     class AddDeleteWord;
     class SetWordType;
     class SetDelay;
     class ChangeText;

     Word & wordRef(const Word & w);

    QWidget * parent;
    QMultiMap<int, Word> _words;

    QUndoStack _history;

    int  pitchMax, pitchMin;
    qreal _gap;
    qreal _bpm;

    int _editGroup;

    QList<WordSelection*> _selections;
    friend class WordSelection;
};



class Lyrics::WordIterator
{
public:
    WordIterator(Lyrics * lyrics, QMap<int, Word>::iterator it) : _it(it), _lyrics(lyrics) { }

    // Only expose mutable property that does not change the order within the map
    void setText(QString text);


    // Reimplement operator the same way const_iterator does
    inline const Word &value() const { return _it.value(); }
    inline const Word &operator*() const { return _it.value(); }
    inline const Word *operator->() const { return _it.operator->(); }
    inline bool operator==(const WordIterator &o) const { return _it == o._it; }
    inline bool operator!=(const WordIterator &o) const { return _it != o._it; }

    inline WordIterator &operator++() {
        ++_it;
        return *this;
    }
    inline WordIterator operator++(int) {
        WordIterator r = *this;
        ++_it;
        return r;
    }
    inline WordIterator &operator--() {
        --_it;
        return *this;
    }
    inline WordIterator operator--(int) {
        WordIterator r = *this;
        --_it;
        return r;
    }
    inline WordIterator operator+(int j) const
    { WordIterator r = *this; if (j > 0) while (j--) ++r; else while (j++) --r; return r; }
    inline WordIterator operator-(int j) const { return operator+(-j); }
    inline WordIterator &operator+=(int j) { return *this = *this + j; }
    inline WordIterator &operator-=(int j) { return *this = *this - j; }




private:
    QMap<int, Word>::iterator _it;
    Lyrics * _lyrics;
};


class Lyrics::AddDeleteWord : public QUndoCommand
{
public:
    AddDeleteWord(Lyrics * lyrics, const Word & word, bool add, QString text = "");

    void undo();
    void redo();
    int id() const { return 1; }
    int editGroup() const { return _editGroup; }

    bool mergeWith(const QUndoCommand *other);

private:
    Lyrics * _lyrics;
    QList<QPair<bool, Word> > _words;
    int _editGroup;
};


class Lyrics::SetWordType : public QUndoCommand
{
public:
    SetWordType(Lyrics * lyrics, const Word & word, Word::Type type);

    void undo();
    void redo();
    int id() const { return 2; }
    int editGroup() const { return _editGroup; }
    bool mergeWith(const QUndoCommand *other);

private:

    typedef struct WordType {
        Word word;
        Word::Type oldType;
        Word::Type newType;
    } WordType;

    Lyrics * _lyrics;
    QList<WordType> _words;
    int _editGroup;
};


class Lyrics::SetDelay : public QUndoCommand
{
public:
    SetDelay(Lyrics * lyrics, int delay, int from);

    void undo();
    void redo();
    int id() const { return 3; }
    int editGroup() const { return _editGroup; }
    bool mergeWith(const QUndoCommand *other);

private:

    int _delay, _from;
    int _editGroup;

    Lyrics * _lyrics;
};

class Lyrics::ChangeText : public QUndoCommand
{
public:
    ChangeText(Lyrics * lyrics, const Word &word, const QString &text);

    void undo();
    void redo();
    int id() const { return 4; }
    int editGroup() const { return _editGroup; }
    bool mergeWith(const QUndoCommand *other);

private:

    typedef struct WordText {
        Word word;
        QString oldText;
        QString newText;
    } WordType;

    Lyrics * _lyrics;
    QList<WordText> _words;
    int _editGroup;
};
#endif // LYRICS_H
