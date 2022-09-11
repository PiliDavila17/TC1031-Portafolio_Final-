// =================================================================
//
// File: insertion.h
// Author: Pedro Perez
// Description: This file contains the implementation of the
//				insertion sort.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
// =================================================================
#ifndef INSERTION_H
#define INSERTION_H

#include "header.h"
#include <vector>

template <class T>
int insertionSortDay(std::vector<T> &v)
{
  int count = 0;
  for (int i = 1; i < v.size(); i++)
  {
    for (int j = i; j > 0 && v[j].day < v[j - 1].day; j--)
    {
      swap(v, j, j - 1);
      count++;
    }
  }
  return count;
}

template <class T>
int insertionSortMonth(std::vector<T> &v)
{
  int count = 0;
  for (int i = 1; i < v.size(); i++)
  {
    for (int j = i; j > 0 && v[j].month < v[j - 1].month; j--)
    {
      swap(v, j, j - 1);
      count++;
    }
  }
  return count;
}

#endif /* INSERTION_H */