/*
 * FILE: Token.hpp
 * AUTHOR: S. Blythe
 * DATE: 12/2020
 * PURPOSE: Interface for the Tokenclass, representing a single "logical block"
 *            in input for CSC36000 Project #1.
 *
 *  NOTE: If you are trying to understand this file, you are making the project
 *           MILLIONS of times harder than it should be. 
 */
#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <iostream>

// the following are effectively DFA state numbers
#define NOTOK 0   // invalid token
#define NUMBER 1  // this is a number
#define VAR 2     // this is a variable name
#define EXPO 3    // this is an exponentiation sign
#define EOP 4     // this is a terminating term.

class Token
{
private:
  int _type;           // the type number for #define's above
  std::string _sval;   // actual string value of the next logical block
public:
  // default contructor
  Token();
  // accessor methods
  int type() const {return _type;}
  const std::string& value() const {return _sval;}

  // methods for I/O
  std::ostream& print(std::ostream &os) const;
  std::istream& read(std::istream &is);

  // overload << and >> for I/O on Tokens
  friend std::ostream& operator<<(std::ostream &os, const Token &t);
  friend std::istream& operator>>(std::istream &os, Token &t);
};



#endif
