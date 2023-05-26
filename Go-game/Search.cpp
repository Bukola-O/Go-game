#include <string>
#include <cassert>
#include "Search.h"
using namespace std;

int linearSearch (const SortableMove data_in[], int count_in, const SortableMove& value_in)
{
  int return_value = VALUE_NOT_FOUND; 
 for (int i=0; i< count_in; i++)
 {
   if (data_in[i] == value_in)
   {
     return_value = i;
   }
 } 
  return return_value;
}
int unsortedFindSmallest (const SortableMove data_in[], int count_in)
{
  int min = 0;
  for ( int i=0; i < count_in; i++)
  {
    if (data_in[i] < data_in[min])
    {
      min = i;
    }
  }
  return min;
}
int unsortedFindLargest (const SortableMove data_in[], int count_in)
{
  int max = 0;
  for ( int i=0; i < count_in; i++)
  {
    if (data_in[max] < data_in[i])
    {
      max = i;
    }
  }
  return max;
}
void mySort (SortableMove data_in[], int count_in)
{
  // selection sort
  SortableMove temp;
  int min;
  for (int i = 0 ; i < count_in ; i++)
  {
    min = i;
    for (int j = i + 1 ; j < count_in ; j++)
    {
      if (data_in[j] < data_in[min])
        min = j;
    }
    temp = data_in[min];
    data_in[min] = data_in[i];
    data_in[i] = temp;
  }
}
bool isSorted (const SortableMove data_in[], int count_in)
{
  
  if (count_in <= 1)
  {
    return true;
  }
  else
  {
    for (int i = 0; i < count_in - 1; i++)
   {
     if (data_in[i+1] < data_in[i])
     {
       return false;
     }
   }
  }
  return true;
}
int sortedFindSmallest (const SortableMove data_in[], int count_in)
{
  assert(isSorted(data_in, count_in));
  return 0;
}
int sortedFindLargest (const SortableMove data_in[], int count_in)
{
  assert(isSorted(data_in, count_in));
  int largest = count_in - 1;
  return largest;
}
int binarySearch (const SortableMove data_in[], int count_in, const SortableMove& value_in)
{ 
  assert(isSorted(data_in, count_in));
  int return_value = VALUE_NOT_FOUND; 

  if (count_in == 0)
  {
    return return_value;
  }
  else
  {
    
   int high = sortedFindLargest(data_in, count_in);
   int low = sortedFindSmallest(data_in, count_in);

   while( low <= high)
   {
     int mid = (low + high) / 2;

     if (value_in == data_in[mid])
     {
       return mid;
     }
     else if (data_in[mid] < value_in)
     {
       low = mid + 1;
     }
     else if (value_in < data_in[mid])
     {
       high = mid -1 ;
     }
   }
  }
  return return_value;
}
int binarySearchFirst (const SortableMove data_in[], int count_in, const SortableMove& value_in)
{
  assert(isSorted(data_in, count_in));
  int return_value = VALUE_NOT_FOUND;
   if (count_in == 0)
  {
    return return_value;
  }
  else
   {
   int high =sortedFindLargest(data_in, count_in);
   int low =sortedFindSmallest(data_in, count_in);
    while( low <= high)
    {
     int mid = (low + high) / 2;

     if (value_in == data_in[mid] && (mid == 0 || data_in[mid - 1] < value_in) )
     {
       return mid;
     }
     else if (data_in[mid] < value_in)
     {
       low = mid + 1;
     }
     else if (!(data_in[mid] < value_in))
     {
       high = mid -1 ;
     }
   }
     return return_value;
  }
}
  

