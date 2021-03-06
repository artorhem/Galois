/*
 * This file belongs to the Galois project, a C++ library for exploiting parallelism.
 * The code is being released under the terms of the 3-Clause BSD License (a
 * copy is located in LICENSE.txt at the top-level directory).
 *
 * Copyright (C) 2018, The University of Texas at Austin. All rights reserved.
 * UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING THIS
 * SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR ANY PARTICULAR PURPOSE, NON-INFRINGEMENT AND WARRANTIES OF
 * PERFORMANCE, AND ANY WARRANTY THAT MIGHT OTHERWISE ARISE FROM COURSE OF
 * DEALING OR USAGE OF TRADE.  NO WARRANTY IS EITHER EXPRESS OR IMPLIED WITH
 * RESPECT TO THE USE OF THE SOFTWARE OR DOCUMENTATION. Under no circumstances
 * shall University be liable for incidental, special, indirect, direct or
 * consequential damages or loss of profits, interruption of business, or
 * related expenses which may arise from use of Software or Documentation,
 * including but not limited to those resulting from defects in Software and/or
 * Documentation, or loss or inaccuracy of data of any kind.
 */

/*
 * EquationSystem.h
 *
 *  Created on: 05-08-2013
 *      Author: kj
 */

#ifndef EQUATIONSYSTEM_H_
#define EQUATIONSYSTEM_H_

#include <cstdio>
#include <cstdlib>

class EquationSystem {
private:
  // needed because of implementation of swapRows
  double* origPtr;

public:
  // this variables _should_ be public
  // Productions will use them directly

  unsigned long n;
  double** matrix;
  double* rhs;

  EquationSystem(){};
  EquationSystem(unsigned long n);
  EquationSystem(double** matrix, double* rhs, unsigned long size);
  virtual ~EquationSystem();

  void swapRows(const int i, const int j);
  void swapCols(const int i, const int j);

  void eliminate(const int rows);
  void backwardSubstitute(const int startingRow);

  void checkRow(int row_nr, int* values, int values_cnt);
  void print() const;
};

#endif /* EQUATIONSYSTEM_H_ */
