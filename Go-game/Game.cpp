#include "Game.h"
#include "BoardValue.h"
#include <cassert>
#include <iostream>

using namespace std;

void Game::printRemoved(const StonesRemoved &removed_in) const {
  if (removed_in.them > 0) {
    cout << "Captured " << removed_in.them << " stones." << endl;
  }
  if (removed_in.us > 0) {
    cout << "Lost " << removed_in.us << " stones to suicide." << endl;
  }
}

Game::Game() : white(BOARD_VALUE_WHITE) {}
Game::Game(int size_in) : white(BOARD_VALUE_WHITE), go(size_in) {
  gameHistory.addAtHead(go);
}

Game::Game(const std::string &filename_in) : white(BOARD_VALUE_WHITE) {
  assert(filename_in != "");
  go.load(filename_in);
  gameHistory.addAtHead(go);
}

void Game::printBoard() const { go.print(); }

void Game::printWinner() const {
  int black_score_temp;
  int white_score_temp;
  float black_score;
  float white_score;
  black_score_temp = go.calculateScore(BOARD_VALUE_BLACK);
  white_score_temp = go.calculateScore(BOARD_VALUE_WHITE);

  black_score = black_score_temp;
  white_score = white_score_temp + 7.5;

  if (black_score > white_score) {
    cout << "Black won! black got " << black_score << " points white got "
         << white_score << " points." << endl;
  } else {
    cout << "White won! white got " << white_score << " points black got "
         << black_score << " points." << endl;
  }
}

const Board &Game::getBoard() const { return go; }

bool Game::isInHistory(const Board &board_in) const {
  if (gameHistory.isInList(board_in)) {
    return true;
  } else {
    return false;
  }
}

void Game::blackPass() {
  cout << "Black passed." << endl;
  gameHistory.addAtHead(go);
}

bool Game::blackPlay(int row_in, int column_in) {
  int pos;
  StonesRemoved playerCaptured;
  if (go.isOnBoard(row_in, column_in)) {
    pos = go.getAt(row_in, column_in);
    if (pos == BOARD_VALUE_EMPTY) {
      Board copied = go;
      playerCaptured = copied.playStone(row_in, column_in, BOARD_VALUE_BLACK);
      if (gameHistory.isAtLeast2Long()) {
        if (gameHistory.getSecond() == copied) {
          cout << "Forbidden: Ko rule" << endl;
          return false;
        }
      }
      if (isInHistory(copied)) {
        cout << "Forbidden: Superko rule" << endl;
        return false;
      }
      if (playerCaptured.us > 0) {
        cout << "Forbidden: Suicide rule" << endl;
        return false;
      } else {
        go = copied;
        cout << "Black placed a stone at row " << row_in << ", column "
             << column_in << endl;
        // cout << "White passed" <<endl;
        printRemoved(playerCaptured);
        gameHistory.addAtHead(go);
        return true;
      }

    } else {
      cout << "Forbidden: Place row " << row_in << " column " << column_in
           << " is not empty." << endl;
      return false;
    }
  } else {
    cout << "Forbidden: Place row " << row_in << " column " << column_in
         << " is outside board" << endl;
    return false;
  }
}

bool Game::whiteAi() {
  Move White_move = white.chooseMove(*this);
  if (White_move.is_played == false) {
    cout << "White passed" << endl;
    gameHistory.addAtHead(go);
    return false;
  } else {
    cout << "White placed a stone at row " << White_move.row << ", column "
         << White_move.column << "." << endl;
    StonesRemoved white_play =
        go.playStone(White_move.row, White_move.column, BOARD_VALUE_WHITE);
    printRemoved(white_play);
    gameHistory.addAtHead(go);
    return true;
  }
}
void Game::undo2Moves() {
  if (gameHistory.isAtLeast3Long()) {
    gameHistory.removeAtHead();
    gameHistory.removeAtHead();

    go = gameHistory.getFirst();
  } else {
    cout << "Forbidden: No more moves to undo" << endl;
  }
}