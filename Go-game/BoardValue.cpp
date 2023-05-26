#include <cassert>
#include "BoardValue.h"

bool isBoardValueValid (char value_in)
{
  if (value_in == BOARD_VALUE_EMPTY || value_in == BOARD_VALUE_BLACK || value_in == BOARD_VALUE_WHITE || value_in == BOARD_VALUE_MARKED)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool isBoardValuePlayer (char value_in)
{
  if (value_in == BOARD_VALUE_BLACK || value_in == BOARD_VALUE_WHITE)
  {
    return true;
  }
  else
  {
    return false;
  }
}
char getOtherPlayer (char player_value_in)
{
  assert(isBoardValuePlayer( player_value_in));
  if(player_value_in == BOARD_VALUE_BLACK)
  {
    return BOARD_VALUE_WHITE;
  }
  else
  {
    return BOARD_VALUE_BLACK;
  }
}