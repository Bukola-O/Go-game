#pragma once
#include <string>
using namespace std;

const int INVALID_COORDINATE = -1;

int stringToInteger(const string &str_in);
int placeStringToRow(const string &str_in);
int placeStringToColumn(const string &str_in);
bool isPlaceStringWellFormed(const string &str_in);
