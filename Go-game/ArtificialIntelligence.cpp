#include "ArtificialIntelligence.h"
#include "Game.h"
#include "Board.h"
#include "Search.h"
#include "History.h"
#include <cassert>
#include <iostream>

using namespace std;

float ArtificialIntelligence::calculateNetScore(const Board &board_in) const {
  char otherPlayer = getOtherPlayer(playerValue);
  int usScore = board_in.calculateScore(playerValue);
  int themScore = board_in.calculateScore(otherPlayer);
  int net = usScore - themScore;
  return (float)net;
}

MoveResult ArtificialIntelligence::getPlayResult(const Game &game_in, int row_in, int column_in) const 
{
  MoveResult aiMove;
  int pos;
  StonesRemoved playerCaptured;
  if (game_in.getBoard().isOnBoard(row_in, column_in)) {
    pos = game_in.getBoard().getAt(row_in, column_in);
    if (pos == BOARD_VALUE_EMPTY) {
      Board copied = game_in.getBoard();
      playerCaptured = copied.playStone(row_in, column_in, playerValue);
      if (game_in.isInHistory(copied))
      {
        aiMove.legal = false;
      }
      else{
        if (playerCaptured.us > 0) {
        aiMove.legal = false;
      } else {
        aiMove.legal = true;
        aiMove.netScore = calculateNetScore(copied);
        return aiMove;
      }
      }

    } else {
      aiMove.legal = false;
    }
  } else {
    aiMove.legal = false;
  }
  return aiMove;
}

bool ArtificialIntelligence::isInvariantTrue() const {
  if (isBoardValuePlayer(playerValue)) {
    return true;
  } else {
    return false;
  }
}

ArtificialIntelligence::ArtificialIntelligence(char us_value_in) {
  assert(isBoardValuePlayer(us_value_in));
  playerValue = us_value_in;
  assert(isInvariantTrue());
}

Move ArtificialIntelligence::chooseMove(const Game &game_in) const {
  int i, j, highestScoreMove, index;
  const int arraySize = (game_in.getBoard().getSize() * game_in.getBoard().getSize()) + 1;
  SortableMove AI_MOVES[arraySize];
  int moveCount = 0;
  MoveResult validMoves;

  SortableMove pass;
  pass.is_played = false;
  pass.net_score = calculateNetScore(game_in.getBoard()) + 0.5;
  AI_MOVES[0] = pass;

  for (i = 0; i < game_in.getBoard().getSize(); i++) {
    for (j = 0; j < game_in.getBoard().getSize(); j++) {
      validMoves = getPlayResult(game_in, i, j);
      if (validMoves.legal == true) {
        AI_MOVES[moveCount + 1].is_played = validMoves.legal;
        AI_MOVES[moveCount + 1].net_score = validMoves.netScore;
        AI_MOVES[moveCount + 1].row = i;
        AI_MOVES[moveCount + 1].column = j;
        moveCount++;
      }
    }
  }
  mySort(AI_MOVES, moveCount + 1);
  highestScoreMove = sortedFindLargest(AI_MOVES, moveCount + 1);
  index =
      binarySearchFirst(AI_MOVES, moveCount + 1, AI_MOVES[highestScoreMove]);
  int range = (moveCount + 1) - index;
  int chooseMove = index + (rand() % range);
  return AI_MOVES[chooseMove];
}
