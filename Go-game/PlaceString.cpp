#include "PlaceString.h"
#include <string>

using namespace std;

int stringToInteger(const string &str_in) {
  if (str_in.length() == 0) {
    return INVALID_COORDINATE;
  }
  for (int i = 0; i < str_in.length(); i++) {
    if (str_in[i] < '0' || str_in[i] > '9') {
      return INVALID_COORDINATE;
    }
  }
  int sum = 0;
  for (int i = 0; i < str_in.length(); i++) {
    sum = sum * 10 + (str_in[i] - '0');
  }
  return sum;
}
int placeStringToRow(const string &str_in) {
  if (str_in.length() < 2) {
    return INVALID_COORDINATE;
  }
  string rowString = str_in.substr(1);
  int row = stringToInteger(rowString);
  return row;
}
int placeStringToColumn(const string &str_in) {
  int column;
  if (str_in[0] == 'I' || str_in[0] == 'O' || str_in.length() == 0 || str_in[0] > 'Z') {
    return INVALID_COORDINATE;
  }

  else if (str_in[0] > '@') {
    column = str_in[0] - 65;
    if (str_in[0] > 'I') {
      column = str_in[0] - 66;
      if (str_in[0] > 'O') {
        column = str_in[0] - 67;
      }
    }
    return column;
  } else {
    return INVALID_COORDINATE;
  }
}
bool isPlaceStringWellFormed(const string &str_in) {
  if (placeStringToColumn(str_in) != -1 && placeStringToRow(str_in) != -1) {
    return true;
  } else 
  {
    return false;
  }
}