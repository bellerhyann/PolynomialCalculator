/*
 * FILE: Token.cpp
 * AUTHOR: S. Blythe
 * DATE: 12/2020
 * PURPOSE: Implementation for the Token class, representing a single
 *    "logical block" in input for CSC36000 Project #1.
 *
 *  NOTE: If you are trying to understand this file, you are making the project
 *           MILLIONS of times harder than it should be. 
 */
#include "Token.hpp"

#include <iostream>
using namespace std;

// the 2-D table used to represent the underlying DFA
static int **table=NULL;

// default constructor - should just build the DFA table if not yet built
Token::Token()
{
  // if table not built ...
  if (table==NULL)
    {
      // initialize table
      table = new int*[7];

      // mark all transitions as iniitially invalid (-1)
      for(int state=0; state<7; state++)
	{
	  table[state]=new int[256];
	  for(int ch=0; ch<256; ch++)
	    table[state][ch]=-1;
	}

      // State 0 transitions
      table[0][(int)'+']=1;
      table[0][(int)'-']=1;

      for (int ch='0'; ch<='9'; ch++)
	table[0][ch]=2;

      table[0][(int)'.']=3;
      
      table[0][(int)'x']=5;

      table[0][(int)';']=6;
      
      // State 1 transitions
      for (int ch='0'; ch<='9'; ch++)
	table[1][ch]=2;

      table[1][(int)'.']=3;

      // State 2 transitions
      for (int ch='0'; ch<='9'; ch++)
	table[2][ch]=2;
      table[2][(int)'.']=3;

      // State 3 transitions
      for (int ch='0'; ch<='9'; ch++)
	table[3][ch]=4;

      // State 4 transitions
      for (int ch='0'; ch<='9'; ch++)
	table[4][ch]=4;
      
    }

  // default token values
  _type=-1; // invalid type
  _sval=""; // empty string
}

// dumps a token to specified stream (most likely cout)
ostream&
Token::print(ostream &os) const
{
  os << _sval;
  return os;
}

// reads a token from specified stream (most likely cin)
istream&
Token::read(std::istream &is)
{
  _sval=""; // start token val as empty
  char ch; // character to consider adding to Token. 

  // skip whitespace (tricky, tricky!)
  is >> ch;
  is.putback(ch);
  
  int curr=0;  // current state - initialized as start state
  int prev=-1; // previous state; when starting, we don't have one. 

  // keep following transitions until we can't legally do so 
  while(curr!=-1)
    {
      // read next character (without skipping whitespace)
      ch=is.get();

      // update state(s)
      prev=curr;
      curr=table[curr][(int)ch];

      // add char to Taken value if still in legal state. 
      if (curr!=-1)
	_sval+=ch;
    }
  // last char read was not part of this token, so put it back ...
  is.putback(ch);

  // figure out which type of token we've got and adjust value accordingly. 
  int final=prev;
  if (final==1)
    {
      _type=NUMBER;
      _sval+="1"; // turn + into +1, - into -1
    }
  else if (final==2 || final==4)
    _type= NUMBER;
  else if (final==5)
    _type=VAR;
    else if (final==6)
    _type=EOP;
  else
    _type=NOTOK;

  return is;
}

// overload << using above print method. 
ostream& operator<<(ostream &os, const Token &t)
{
  return t.print(os);
}

// overload >> using above read method. 
istream& operator>>(istream &is, Token &t)
{
  return t.read(is);
}

