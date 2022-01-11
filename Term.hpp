/*
 * FILE: Term.hpp
 * AUTHOR: S. Blythe
 * DATE: 12/2020
 * PURPOSE: Interface for the Term class, representing a single term in a 
 *            polynomial for CSC36000 Project #1.
 */
#ifndef _TERM_HPP_
#define _TERM_HPP_

#include <iostream>

class Term
{
private:
  double _coeff;         // term's coefficient
  unsigned int _degree;  // term's degree
public:
  //default constructor (Term evaluates to 0 )
  Term(): _coeff(0), _degree(0) {}
  // build a Term out of a constant. 
  Term(double coeff): _coeff(coeff), _degree(0) {}
  // build a Term out of both a coefficient and a degree
  Term(double coeff, int degree) : _coeff(coeff), _degree(degree) {}

  // accessor/modifier for the coefficient
  double coefficient() const {return _coeff;}
  double& coefficient() {return _coeff;}

  // accessor/modifier for the degree
  unsigned int degree() const {return _degree;}
  unsigned int& degree() {return _degree;}

  // comparator. Looks strange, but we want a higher degree term to appear
  //   before lower degree terms. 
  bool operator<(const Term &other) const {return _degree>other._degree;}

  // methods for performing I/O. They are directly utilized in overloaded <<,>>
  std::ostream& print(std::ostream &os) const;
  std::istream& read(std::istream &os);

  // want to overload << and >> for Terms. 
  friend std::ostream& operator<<(std::ostream &os, const Term &t);
  friend std::istream& operator>>(std::istream &is, Term &t);
};



#endif
