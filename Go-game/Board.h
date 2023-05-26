#pragma once
#include <string>

const int STAR_POINT_SPACING = 6;
const int BOARD_SIZE_MIN = 1;
const int BOARD_SIZE_MAX = 24;
const int BOARD_SIZE_DEFAULT = 19;

struct StonesRemoved
{
  int us;
  int them;
};
// Board
//
//  A Board consists of the an array representing the go board and 
//  functions used to the place pieces on the board as well as 
//  calculate score, print the boar and capture pieces. it also has 
//  constructors and a destructor.
//
//  Class Invariant:
//    <1> isBoardValueValid(ptr_gameBoard[i])
//    <2> boardPlaces == calculatePlaceCount()
//    <3> board_size < 24
//    <4> board_size > 1
//
class Board {
private:
  char* ptr_gameBoard;
  int board_size;
  int boardPlaces;
  int toIndex (int row_in, int column_in) const;
  int calculatePlaceCount () const;
  bool isAlignedForStarPoint(int index_in) const;
  void printRowNumber(int row_in) const;
  void printColumnLetters() const;
  int capturePlayer (char player_value_in);
  void copyData (const Board& board_in);
  void destroyData ();
  bool isInvariantTrue() const;

public:
  Board();
  //
//  Board
//
//  Purpose: To initialize meber variables of the board class when given a size as the parameter.
//  Parameter(s):
//    <1> size_in: This is the size of the board to be created.
//    ...
//  Precondition(s):
//    <1> size_in >=1  && size_in <= 24
//    ...
//  Returns: N/A
//  Side Effect: initializes the member variables of the class.
//
  Board (int size_in);
  Board (const Board& board_in);
  ~Board ();
  Board& operator= (const Board& board_in);
  bool operator== (const Board& board_in) const;
//
//  getSize
//
//  Purpose: this function returns the size of the board.
//  Parameter(s):
//    N/A
//  Precondition(s):
//    N/A
//    ...
//  Returns: The funtion returns the board size.
//  Side Effect: N/A.
//
  int getSize () const;
//
//  isOnBoard
//
//  Purpose: The function is called to determine whether the given position indicated by the parameters is on the board
//  Parameter(s):
//    <1> row_in: this is the row value of the position to be checked
//    <2> column_in: this is the column value of the position to be checked
//    ...
//  Precondition(s):
//   N/A
//    ...
//  Returns: A boolean indicating whether the given position is on the board.
//  Side Effect: N/A.
//
  bool isOnBoard (int row_in, int column_in) const;
//
//  getAt
//
//  Purpose: To get the particular character at a location on the board and save it in a variable.
//  Parameter(s):
//    <1> row_in: The row number to get the character from.
//    <2> column_in: The column number to get the character from.
//    ...
//  Precondition(s):
//    <1> isOnBoard(row_in, column_in)
//    ...
//  Returns: The function returns the value of the character at the position specified by the row_in and column_in.
//  Side Effect: N/A
//
  char getAt(int row_in, int column_in) const;
  void setAt(int row_in, int column_in, char value_in);
  int countWithValue(char value_in) const;
  int calculateScore (char us_value_in) const;
  void print() const;
  void load(const std::string &filename_in);
//
//  playStone
//
//  Purpose: To play a stone on the board and to capture stones is the required condition to capture is met.
//  Parameter(s):
//    <1> parameter1: The row number to place the stone at.
//    <2> column_in: The column number to place the stone at.
//    <3> us_value_in: The value of the character belonging to the player to be played on the board. 
//    ...
//  Precondition(s):
//    <1> isOnBoard(row_in,column_in)
//    <2> gameBoard[row_in][column_in] == BOARD_VALUE_EMPTY
//    <3> isBoardValuePlayer(us_value_in)
//    ...
//  Returns: The function retuns a struct containing two int member fields which contain the value of player stones captured and the value of the other players stones captured.
//  Side Effect: The function places a stone on the board.
//
  StonesRemoved playStone (int row_in, int column_in, char us_value_in);
  void replaceAll (char old_value_in, char new_value_in);
  void fillConnected (char old_value_in, char new_value_in, char neighbour_value_in);
  bool isANeighbourWithValue (int row_in, int column_in, char value_in) const;

};