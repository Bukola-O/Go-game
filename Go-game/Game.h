#pragma once
#include "Board.h"
#include "ArtificialIntelligence.h"
#include "History.h"

class Game
{
  private:
    Board go;
    ArtificialIntelligence white;
    History gameHistory;
    void printRemoved (const StonesRemoved& removed_in) const;
  
  public:
    Game ();
    Game (int size_in);
    Game (const std::string& filename_in);
    void printBoard () const;
    void printWinner () const;
    const Board& getBoard () const;
    bool isInHistory (const Board& board_in) const;
    void blackPass ();
    bool blackPlay (int row_in, int column_in);
    bool whiteAi ();
    void undo2Moves ();
};