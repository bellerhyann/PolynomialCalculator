/*
 * FILE: Term.cpp
 * AUTHOR: S. Blythe
 * DATE: 12/2020
 * PURPOSE: Inmplementation for the Term class, representing a single term in a 
 *            polynomial for CSC36000 Project #1.
 *
 *   NOTE: If you find yourself looking at this file, you are likely making
 *         things MILLIONS of times harder than they should be. 
 */
#include "Term.hpp"
#include "Token.hpp"

#include <cstdlib>
#include <iostream>
using namespace std;

// prints the current Term to the specified stream - usually cout
ostream&
Term::print(ostream& os) const
{
  // is this 0? 
  if (_coeff==0)
    {
      os << 0;
      return os;
    }

  // is this 1 or -1? 
  if ( (_coeff==-1 || _coeff==1) && _degree==0)
    {
      os << _coeff;
      return os;
    }

  // is this -x^i? 
  if (_coeff==-1)
    {
      os << "-";
    }
  // is this a term with a coefficient other thna 1 or -1? 
  else if (_coeff!=1)
    {
      os << _coeff;
    }

  // if this is a constant, we're done a t this point ...
  if (_degree==0)
    return os;

  // print out the variable name (assumed to be x)
  os << "x";

  // if this is more than just x ...
  if (_degree>1)
    {
      os << "^";
      os << _degree;
    }

  return os;
}

// read a Term from specified stream (most likely cin)
istream&
Term::read(istream &is)
{
  // get the first Token in the term 
  Token t;

  is >>t;

  // based on what first token is, behave accordingly ...

  // if first token is a var name, there's no coefficient. So it's value is 1
  if (t.type()==VAR)
    _coeff=1;

  // if the first thing encountered is a number ...
  else if (t.type()==NUMBER)
    {
      // convert the string number to a real number
      _coeff=atof(t.value().c_str());

      // read the next non-WS char, and put it back to be read later
      char ch;
      is >> ch;
      is.putback(ch);

      // if next char was not the variable name (x), we have a numeric constat
      if (ch!='x')
	{
	  _degree=0;
	  return is;
	}

      // read the variable name as the next token ... 
      is >> t;
    }
  else
    {
      _coeff=0;
      _degree=0;
      return is;
    }

  // check net char ... and make sure it's a digit before processinh
  char ch;
  is >> ch;
  is.putback(ch);

  // if term has no degree, then it's degree is 1. 
  if (!isdigit(ch))
    {
      _degree=1;
      return is;
    }

  // at this point, the next Token must be the degree ...
  is >> t;
  _degree=atoi(t.value().c_str());
  
  return is;
}

// overload << for output using print() to do so. 
ostream& operator<<(ostream &os, const Term &t)
{
  return t.print(os);
}

// overload >> for input using read() to do so. 
istream& operator>>(istream &is, Term &t)
{
  return t.read(is);
}

