#pragma once
#include "Move.h"
#include <string>
#include <climits>
using namespace std;

const int VALUE_NOT_FOUND = INT_MAX;

int linearSearch (const SortableMove data_in[], int count_in, const SortableMove& value_in);
int unsortedFindSmallest (const SortableMove data_in[], int count_in);
int unsortedFindLargest (const SortableMove data_in[], int count_in);
void mySort (SortableMove data_in[], int count_in);
bool isSorted (const SortableMove data_in[], int count_in);
int sortedFindSmallest (const SortableMove data_in[], int count_in);
int sortedFindLargest (const SortableMove data_in[], int count_in);
int binarySearch (const SortableMove data_in[], int count_in, const SortableMove& value_in);
int binarySearchFirst (const SortableMove data_in[], int count_in, const SortableMove& value_in);
 