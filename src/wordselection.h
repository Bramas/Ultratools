#ifndef WORDSELECTION_H
#define WORDSELECTION_H

#include <QMap>
#include <QPoint>
#include "uWord.h"
class Lyrics;

class WordSelection
{
public:

    WordSelection();
    WordSelection(Lyrics * lyrics);
    ~WordSelection();

    bool isNull() { return _lyrics; }
    void add(const Word & word);
    void remove(const Word & word);
    int count() const { return _selectedWords.count(); }
    bool isEmpty() const { return _selectedWords.isEmpty(); }
    bool contains(const Word & w) const { return _selectedWords.contains(w); }
    Word first() { return _selectedWords.begin().key(); }
    Word last() { return (_selectedWords.end() - 1).key(); }
    const QMap<Word, int> & words() const { return _selectedWords; }

    int firstIndex();
    int lastIndex();


    // functions that modify the lyrics
    void setType(Word::Type type);
    void deleteSelectedWords();
    void merge();
    QPoint translate(int addTime, int addPitch);
    int expandLeft(int add);
    int expandRight(int add);

private:

    void insertAndSelect(const Word & w);
    QMap<Word, int> takeSelectedWords();
    Lyrics * _lyrics;
    QMap<Word, int> _selectedWords;



};

inline WordSelection& operator<<(WordSelection& ws, const Word & word)
{
    ws.add(word);
    return ws;
}

#endif // WORDSELECTION_H
