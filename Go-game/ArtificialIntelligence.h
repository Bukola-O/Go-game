#pragma once
#include "BoardValue.h"
#include "Board.h"
#include "Move.h"
class Game;

class Board;


struct MoveResult
{
  bool legal;
  float netScore;
};
//
//  ArtificialIntelligence
//
//  An ArtificialIntelligence instance compares the quality of 
//  different Moves and determines the best among them or choose one
//  among the best if there are multiple moves tied for best.
//
//  Class Invariant:
//    <1> isBoardValuePlayer(playerValue)
//    
//
class ArtificialIntelligence
{
  private:
  char playerValue;
  float calculateNetScore (const Board& board_in) const;
  MoveResult getPlayResult (const Game& game_in, int row_in, int column_in) const;
//
//  isInvariantTrue
//
//  Purpose: To check the state of the member variable before running a function.
//  Parameter(s):
//  
//    ...
//  Precondition(s):
//   
//    ...
//  Returns: A boolean determined by isBoardValuePlayer(playerValue) it returns true if isBoardValuePlayer(playerValue) returns true and false otherwise. 
//  Side Effect: N/A
//
  bool isInvariantTrue () const;

  public:
//
//  ArtificialIntelligence
//
//  Purpose: To initialize the member variable of the ArtificialIntelligence class.
//  Parameter(s):
//    <1> us_value_in : This is the value we initialize the member field with.
//    ...
//  Precondition(s):
//    <1> isBoardValuePlayer(us_value_in).
//    ...
//  Returns: N/A.
//  Side Effect: The function initializes the member field of the ArtificialIntelligence class.
//
  ArtificialIntelligence (char us_value_in);
//
//  chooseMove
//
//  Purpose: This function uses some logic to determine the best scoring move or choose one at random if there are moves tied for the best score.
//  Parameter(s):
//    <1> board_in: A board variable representing the board the function has to choose the best next move for.
//    ...
//  Precondition(s):
//    ...
//  Returns: It returns a Move variable after choosing a move.
//  Side Effect: N/A
//
  Move chooseMove (const Game& game_in) const;
};