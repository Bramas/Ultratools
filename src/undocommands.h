#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QUndoCommand>

#include "uWord.h"

class Lyrics;

class AddWordCommand : public QUndoCommand
{
public:
    AddWordCommand(Lyrics * lyrics, const Word & word);

    void undo();
    void redo();

private:
    Lyrics * _lyrics;
    Word _word;
};

#endif // UNDOCOMMANDS_H
