#include "Move.h"
#include <iostream>

using namespace std;

bool operator== (const SortableMove& lhs_in, const SortableMove& rhs_in)
{
  if(lhs_in.net_score == rhs_in.net_score)
  {
    return true; 
  }
  else
  {
    return false;
  }
}

bool operator< (const SortableMove& lhs_in, const SortableMove& rhs_in)
{
  if(lhs_in.net_score < rhs_in.net_score)
  {
    return true;
  }
  else
  {
    return false;
  }
}