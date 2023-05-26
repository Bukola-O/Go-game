#include "Board.h"
#include "BoardValue.h"
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;
int Board::toIndex (int row_in, int column_in) const
{
  assert(isOnBoard(row_in, column_in));
  return ((row_in * board_size) + column_in);
  
}

int Board::calculatePlaceCount() const
{
  return board_size * board_size;
}

bool Board::isAlignedForStarPoint(int index_in) const {
  assert(index_in >= 0);
  if ((index_in % STAR_POINT_SPACING) ==
      ((board_size / 2) % STAR_POINT_SPACING)) {
    return true;
  } else {
    return false;
  }
}

void Board::printRowNumber(int row_in) const { cout << setw(2) << row_in; }

void Board::printColumnLetters() const {
  cout << "   ";
  for (int i = 65; i < board_size + 65; i++)
  { 
    if( i > 72){
      if (i > 77)
      {
        cout << char(i + 2) << " ";
      }
      else
      {
        cout << char(i + 1) << " ";
      }
    }
    else
    {
      cout << char(i) << " ";
    }
  }
  cout << endl;
}

int Board::capturePlayer (char player_value_in)
{
  assert(isBoardValuePlayer(player_value_in));
  int i,  markedStones;
  for(i = 0; i < boardPlaces; i++)
  {
      if(ptr_gameBoard[i] == player_value_in)
      {
        ptr_gameBoard[i] =BOARD_VALUE_MARKED;
      }
    }
  fillConnected( BOARD_VALUE_MARKED, player_value_in, BOARD_VALUE_EMPTY);
  markedStones = countWithValue(BOARD_VALUE_MARKED);
  for(i = 0; i < boardPlaces; i++)
  {
      if(ptr_gameBoard[i] == BOARD_VALUE_MARKED)
      {
        ptr_gameBoard[i] = BOARD_VALUE_EMPTY;
      }
  }
  return markedStones;
}

void Board::copyData (const Board& board_in)
{
  assert(board_in.isInvariantTrue());
  assert(ptr_gameBoard == nullptr);
  board_size = board_in.board_size;
  boardPlaces = board_in.boardPlaces;
  ptr_gameBoard = new char[boardPlaces];
  for (int i = 0 ; i < boardPlaces ; i++)
  {
    ptr_gameBoard[i] = board_in.ptr_gameBoard[i];
  }
  
  assert(ptr_gameBoard != nullptr);
}

void Board::destroyData ()
{
  assert(ptr_gameBoard != nullptr);
  delete [] ptr_gameBoard;
  ptr_gameBoard = nullptr;
  assert(ptr_gameBoard == nullptr);
}

bool Board::isInvariantTrue() const {
  int i;
  bool return_value = false;
  if(board_size < 1)
  {
    return false;
  }
  if(board_size > 24)
  {
    return false;
  }
  if (boardPlaces != calculatePlaceCount())
  {
    return false;
  }
  if(ptr_gameBoard != nullptr)
  {
     for (i = 0; i < boardPlaces; i++) 
     {
       if (isBoardValueValid(ptr_gameBoard[i])){
        return_value = true;
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    return false;
  }
  
  return return_value;
}

Board::Board() {
  board_size = BOARD_SIZE_DEFAULT;
  boardPlaces = calculatePlaceCount();
  ptr_gameBoard = new char[boardPlaces];
  int i;
  for (i = 0; i < boardPlaces; i++) {
      ptr_gameBoard[i] = BOARD_VALUE_EMPTY;
    }
  assert(isInvariantTrue());
}

Board::Board (int size_in)
{
  assert(size_in >=1  && size_in <= 24);
  board_size = size_in;
  boardPlaces = calculatePlaceCount();
  ptr_gameBoard = new char[boardPlaces];
  int i;
  for (i = 0; i < boardPlaces ; i++) {
    ptr_gameBoard[i] = BOARD_VALUE_EMPTY;
   }
}

Board::Board (const Board& board_in)
{
  assert(board_in.isInvariantTrue());
  ptr_gameBoard = nullptr;
  copyData(board_in);
  assert(isInvariantTrue());
}

Board::~Board ()
{
  assert(isInvariantTrue());
  destroyData();
}

Board& Board::operator=(const Board& board_in)
{
  assert(isInvariantTrue());
  assert(board_in.isInvariantTrue());
  if (&board_in != this)
  {
    destroyData();
    copyData(board_in);
  }
  assert(isInvariantTrue());
  return *this;
}

bool Board::operator==(const Board& board_in) const
{
  assert(isInvariantTrue());
  assert(board_in.isInvariantTrue());
  if (board_size != board_in.board_size || boardPlaces != board_in.boardPlaces)
  {
    return false;
  }
  for(int i = 0; i < boardPlaces; i++)
  {
    if(ptr_gameBoard[i] != board_in.ptr_gameBoard[i])
    {
      return false;
    }
  }
  return true; 
}

int Board::getSize() const
{
  assert(isInvariantTrue());
  return board_size;
}

bool Board::isOnBoard (int row_in, int column_in) const
{
  if (row_in >= 0 && row_in < board_size && column_in >= 0 && column_in < board_size)
  {
    return true;
  }
  else
  {
    return false;
  }
}

char Board::getAt(int row_in, int column_in) const {
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  int index = toIndex(row_in , column_in);
  return ptr_gameBoard[index];
}

void Board::setAt(int row_in, int column_in, char value_in) {
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  assert(isBoardValueValid(value_in));
  int index = toIndex(row_in , column_in);
  ptr_gameBoard[index] = value_in;
  assert(isInvariantTrue());
}

int Board::countWithValue(char value_in) const {
  assert(isInvariantTrue());
  int boardCount = 0;
  int i;
  for (i = 0; i < boardPlaces; i++) {
      if (ptr_gameBoard[i] == value_in) {
        assert(isBoardValueValid(value_in));
        boardCount++;
      }
    }
  return boardCount;
}

int Board::calculateScore (char us_value_in) const
{
  assert(isInvariantTrue());
  assert(isBoardValuePlayer(us_value_in));
  char player2 = getOtherPlayer(us_value_in);
  Board copy = *this;
  copy.fillConnected(BOARD_VALUE_EMPTY, player2, player2);
  copy.fillConnected(BOARD_VALUE_EMPTY, us_value_in, us_value_in);
  return copy.countWithValue(us_value_in);
}

void Board::print() const {
  assert(isInvariantTrue());
  int i, j, pos1;
  printColumnLetters();
  for (i = 0; i < board_size; i++) {
    printRowNumber(i);
    cout << " ";
    for (j = 0; j < board_size; j++) {
      pos1 = getAt(i, j);
      if (pos1 == BOARD_VALUE_EMPTY && isAlignedForStarPoint(i) &&
          isAlignedForStarPoint(j)) {
        cout << '*' << " ";
      } else {
        cout << ptr_gameBoard[i*board_size+j] << " ";
      }
    }
    printRowNumber(i);
    cout << endl;
  }
  printColumnLetters();
}


void Board :: load (const string& filename_in)
{
	assert(isInvariantTrue());
	assert(filename_in != "");

	// open file with name filename_in
	// fin will read from that file
	// use fin like you use cin
	ifstream fin(filename_in);

	if(!fin)
	{
		cout << "Error: Could not open file \"" << filename_in << "\"" << endl;
		return;  // end function immediately
	}

	// read in the board size
	string line;
	int board_size_read;
	fin >> board_size_read;
	if(!fin)
	{
		cout << "Error: File \"" << filename_in << "\" does not start with board size" << endl;
		return;  // end function immediately
	}
	if(board_size_read > BOARD_SIZE_MAX)
	{
		cout << "Error: File \"" << filename_in << "\" has board size "
		     << board_size_read << ", but maximum is " << BOARD_SIZE_MAX << endl;
		return;  // end function immediately
	}
	if(board_size_read < BOARD_SIZE_MIN)
	{
		cout << "Error: File \"" << filename_in << "\" has board size "
		     << board_size_read << ", but minimum is " << BOARD_SIZE_MIN << endl;
		return;  // end function immediately
	}
	assert(fin);
	string dummy;
	getline(fin, dummy);  // throw away whatever else is on the line

	// replace this board with a new one of the correct size
	*this = Board(board_size_read);

	// read in board state
	bool is_print_error = true;
	for(int r = 0; r < board_size; r++)
	{
		string line;
		getline(fin, line);
		if(!fin)
		{
			if(is_print_error)
			{
				cout << "Error: Could not read line " << r
				     << " of file \"" << filename_in << "\"" << endl;
				cout << "       Replacing with '" << BOARD_VALUE_EMPTY << "'s" << endl;
				is_print_error = false;
			}
			line = string(BOARD_VALUE_EMPTY, board_size);  // set to '.'s
		}
		else if((int)(line.length()) < board_size)
		{
			if(is_print_error)
			{
				cout << "Error: Line " << r << " of file \"" << filename_in
				     << "\" only contains " << line.length()
				     << " / " << board_size << " characters" << endl;
				cout << "       Adding '" << BOARD_VALUE_EMPTY << "'s to end" << endl;
				is_print_error = false;
			}
			line += string(BOARD_VALUE_EMPTY, board_size);  // add '.'s
		}

		for(int c = 0; c < board_size; c++)
		{
			if(isBoardValueValid(line[c]))
				setAt(r, c, line[c]);
			else
			{
				setAt(r, c, BOARD_VALUE_EMPTY);
				if(is_print_error)
				{
					cout << "Error: Line " << r << ", character " << c
						 << " of file \"" << filename_in
						 << "\" is an invalid '" << line[c] << "' character" << endl;
					cout << "       Substituting '" << BOARD_VALUE_EMPTY << "'" << endl;
					is_print_error = false;
				}
			}
		}
	}

	assert(isInvariantTrue());
	// file will be closed automatically when fin goes out of scope
}
StonesRemoved Board::playStone (int row_in, int column_in, char us_value_in)
{
  assert(isInvariantTrue());
  assert(isOnBoard(row_in,column_in));
  int index = toIndex(row_in , column_in);
  assert(ptr_gameBoard[index] == BOARD_VALUE_EMPTY);
  assert(isBoardValuePlayer(us_value_in));
  int capturedPlayer;
  int usCapturedPlayer;
  StonesRemoved Captured;
  char player2;
  setAt(row_in, column_in, us_value_in);
  player2 = getOtherPlayer( us_value_in);
  capturedPlayer = capturePlayer(player2);
  usCapturedPlayer = capturePlayer(us_value_in);
  Captured.us = usCapturedPlayer;
  Captured.them = capturedPlayer;
  assert(isInvariantTrue());
  return Captured;
}

void Board::replaceAll (char old_value_in, char new_value_in)
{
  assert(isInvariantTrue());
  assert(isBoardValueValid(old_value_in) && isBoardValueValid(new_value_in));
  int i;
  for(i = 0; i < boardPlaces; i++)
  {
      if(ptr_gameBoard[i] == old_value_in)
      {
        ptr_gameBoard[i] = new_value_in;
      }
  }
  assert(isInvariantTrue());
}

void Board::fillConnected (char old_value_in, char new_value_in, char neighbour_value_in)
{
  assert(isInvariantTrue());
  assert(isBoardValueValid(old_value_in));
  assert(isBoardValueValid(new_value_in));
  assert(isBoardValueValid(neighbour_value_in));
  bool arrayChanged = true;
  while(arrayChanged)
  {
    int i, j;
    int boolChanged = 0;
    for(i = 0; i < board_size; i++)
      {
        for(j = 0; j < board_size; j++)
        {
          if((ptr_gameBoard[(i*board_size)+j] == old_value_in) && (isANeighbourWithValue(i, j, neighbour_value_in ) || isANeighbourWithValue(i, j, new_value_in )))
          {
            ptr_gameBoard[(i*board_size) + j] = new_value_in;
            boolChanged = 1;
          }
        }
      }
    if(boolChanged != 1)
    {
      arrayChanged = false;
    };
  }
  assert(isInvariantTrue());
}

bool Board::isANeighbourWithValue (int row_in, int column_in, char value_in) const
{
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  assert(isBoardValueValid(value_in));
  if (ptr_gameBoard[((row_in-1)*board_size) + column_in] == value_in && isOnBoard(row_in -1, column_in))
  {
    return true;
  }
  else if (ptr_gameBoard[((row_in+1)*board_size)+column_in] == value_in && isOnBoard(row_in+1, column_in))
  {
    return true;
  }
  else if (ptr_gameBoard[(row_in*board_size)+column_in-1] == value_in && isOnBoard(row_in, column_in-1))
  {
    return true;
  }
  else if (ptr_gameBoard[(row_in*board_size)+column_in+1] == value_in && isOnBoard(row_in,column_in+1))
  {
    return true;
  }
  else
  {
    return false;
  }
}

