//Name: Bukola Oludiran
//Student Number: 200463860

#include <iostream>
#include <string>
#include <ctime>
#include "PlaceString.h"
//#include "Search.h"
#include "Board.h"
#include "BoardValue.h"
#include "Game.h"

using namespace std;

int getBoardSize();

int main()
{
  srand((unsigned int)(time(nullptr)));
  string name;
  int row_in;
  int column_in;
  
  
  cout << "Welcome to my Go game!" << endl;
  cout << "Enter your name: ";
  getline(cin, name);
  int size_in = getBoardSize();
  cout << "Hello " << name << " You will play black"<< endl;
  Game goGame(size_in);
  bool continue_loop = true;
  while (continue_loop)
  {
    goGame.printBoard();
    string move;
    Game newGame;
    cout << "What is your move? ";
    getline(cin, move);
    if (move == "quit")
    {
      continue_loop = false;
    }
    else if (move == "load")
    {
      goGame.printWinner();
      string filename;
      cout << "Enter the file name:  ";
      getline(cin, filename);
      newGame = Game(filename);
      goGame = newGame;
      
    }
    else if (move == "new")
    {
      goGame.printWinner();
      int sizeIn = getBoardSize();
      newGame = Game(sizeIn);
      goGame = newGame;
    }
    else if (move == "undo")
    {
      goGame.undo2Moves();
    }
    else
    {
     if (move == "pass")
     {
       goGame.blackPass();
       if(!goGame.whiteAi())
       {
         continue_loop = false;
       }
     }
     else
     {
       if (isPlaceStringWellFormed(move))
      {
        row_in = placeStringToRow(move);
        column_in = placeStringToColumn(move);
        goGame.blackPlay (row_in, column_in);
        bool whiteGame = goGame.whiteAi();
      }
      else
      {
       cout << move << " is ill-formed" << endl;
      }
    
    
    }
      }
   }  
  goGame.printBoard();
  cout << endl;
  goGame.printWinner ();
  
  cout << "Goodbye, " << name << endl;
  return 0;
}

int getBoardSize()
{
  int value = 0;
  while(value < BOARD_SIZE_MIN || value > BOARD_SIZE_MAX)
  {
    cout << "Please enter a value for the board size: ";
    cin >> value;
    if(value < BOARD_SIZE_MIN )
    {
      cout << "Value is too small. The value should be between 1 and 24 \n";
    }
    else if ( value > BOARD_SIZE_MAX)
    {
       cout << "Value is too big. The value should be between 1 and 24 \n";
    }
    cin.ignore();
  }
  return value;
}
