// Author: S. Blythe
// Date:   1/2021
// Purpose: POlynomial class for CSC36000
#ifndef _POLYNOMIAL_HPP_
#define _POLYNOMIAL_HPP_

#include <iostream>
#include <list>

#include "Term.hpp"

using namespace std;

class Polynomial
{
private:
  list<Term> _poly;  // at its core, a polynomial is a list of Terms
public:
  Polynomial() : _poly() {}

  // add one term to the Polynomial
  void addTerm(Term newt);

  // methods to organize a polynomial
  void orderByDegree(); // sort it
  void normalize();     // sort it and combine like-degreed terms

  // empty te polynomial
  void clear() {_poly.clear();}

  // negate a polynomial
  void negate();

  // evaluate polynomial at specified value 
  double eval(double atX) const;

  // overloaded assignment
  const Polynomial& operator=(const Polynomial &other);

  // overloaded +/- (binary)
  const Polynomial& operator+(const Polynomial &other) const;
  const Polynomial& operator-(const Polynomial &other) const;

  // overloaed operator *, for both poly*poly and poly*Term
  const Polynomial& operator*(const Term &term) const;
  const Polynomial& operator*(const Polynomial &other) const;

  // unary -
  const Polynomial& operator-() const;

  // I/O methods
  ostream& print(ostream &os) const;
  istream& read(istream &is);

  // overloaded I/O operators
  friend istream& operator>> (istream &os, Polynomial &p);
  friend ostream& operator<< (ostream &os, const Polynomial &p);
};


  
#endif
