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
