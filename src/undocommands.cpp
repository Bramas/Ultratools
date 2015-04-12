#include "undocommands.h"
#include "uLyrics.h"


AddWordCommand::AddWordCommand(Lyrics * lyrics, const Word & word) :
    _lyrics(lyrics),
    _word(word)
{

}

void AddWordCommand::redo()
{
    _lyrics->addWord(_word);
}

void AddWordCommand::undo()
{
    _lyrics->removeWord(_word);
}
