// =================================================================
//
// File: header.h
// Author: Pedro Perez
// Description: This file contains the interface and implementation
//				of the Chronometer class, as well as the
//				implementation of some support functions. This class
//				is used to record the execution time of a program.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
// =================================================================

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <sys/types.h>
#include <string>
#include <vector>

using namespace std;

// =================================================================
// Swap the content of two localities (i, j) in array A.
//
// @param A, an array of T elements.
// @param i, an index in the array.
// @param j, an index in the array.
// =================================================================
template <class T>
void swap(T *A, int i, int j)
{
  T aux = A[i];
  A[i] = A[j];
  A[j] = aux;
}

// =================================================================
// Swap the content of two localities (i, j) in vector v.
//
// @param v, a vector of T elements.
// @param i, an index in the vector.
// @param j, an index in the vector.
// =================================================================
template <class T>
void swap(vector<T> &v, int i, int j)
{
  T aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

#endif