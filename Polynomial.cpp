//Author: S. Blythe
//Date:   1/2021
//Purpose: represents polynomial for CSC36000 project #1


#include "Polynomial.hpp"

// dump a polynomial to specified stream
ostream&
Polynomial::print(ostream &os) const
{
  // no terms? print 0. 
  if (_poly.size()==0)
    {
      os << 0;
      return os;
    }

  // print each term. 
  bool first=true;
  for (Term t:_poly)
    {
      // print a + if term is positive. but not if it's the first term. 
      if (t.coefficient()>0 && !first)
	os << "+";
      os << t;
      first=false;
    }
  return os;
}

// add a term by simply appending it to the end of the list
void
Polynomial::addTerm(Term t)
{
  _poly.push_back(t);
}


// evaluate using Horner's method
double
Polynomial::eval(double atX) const
{
  // start with 0 as the answer ...
  double answer =0;

  // get degree of polynomial 
  unsigned int degree=_poly.front().degree();

  // look at each polynomial term
  for (Term t:_poly)
    {
      // while the term's degree doesn't match the degree we expect ...
      while (t.degree()!=degree)
	{
	  // ... update sum as if coefficeint is 0. 
	  answer *= atX;
	  degree--;
	}

      // addin coefficcient
      answer+=t.coefficient();
    }

  // there might be some trailing "missing" terms ... deal with those next.
  while (degree>0)
  {
    answer*=atX;
    degree--;
  }
  
  return answer;
}

// add two polynomials. 
const Polynomial&
Polynomial::operator+(const Polynomial &other) const
{
  Polynomial *answer = new Polynomial();

  // put terms from each polynomial into the answer
  for (Term t:_poly)
    answer->addTerm(t);
  for (Term t:other._poly)
    answer->addTerm(t);

  // merge duplicate terms and sort degrees. 
  answer->normalize();
  
  return *answer;
}

// subtract two polynomials
const Polynomial&
Polynomial::operator-(const Polynomial &other) const
{
  // sneaky - use unary - (see below) and then add ...
  return (*this) + -other;
}

// multiply a polynimial by a term
const Polynomial&
Polynomial::operator*(const Term &t) const
{
  Polynomial *answer = new Polynomial();

  // start the result as just being this polynomial
  *answer = *this;

  // then multiply each term in this polynomial by the term 
  for (Term &pt:answer->_poly)
    {
      pt.coefficient() *= t.coefficient();
      pt.degree() += t.degree();
    }

  return *answer;
}

// multiply two polynomials
const Polynomial&
Polynomial::operator*(const Polynomial &other) const
{
  Polynomial *answer = new Polynomial();

  // look at each term in 2nd polynomial
  for (Term t:other._poly)
    {
      // use the poly * term method (above)
      Polynomial termMult = *this * t;

      // use + to add the new ploy*term polynomial. 
      *answer = *answer + termMult;
    }
  
  return *answer;
}

// asignment operator
const Polynomial&
Polynomial::operator=(const Polynomial &other)
{
  // assigning should clear out this polnomial. 
  this->_poly.clear();

  // just add the terms 
  for (Term t:other._poly)
    this->addTerm(t);

  normalize();
  
  return *this;
}

// used with unary minus (see below)
void
Polynomial::negate()
{
  // just negate each term ...
  for(Term &t:_poly)
    {
      t.coefficient() = -t.coefficient();
    }
}  

// re-arrange polynomial from highest degree term to lowest. 
void
Polynomial::orderByDegree()
{
  _poly.sort();
}

// sort and combine terms of duplicate degree
void
Polynomial::normalize()
{
  list<Term> newPoly;

  orderByDegree(); // sort by degree

  // go through the terms in the polynomial
  unsigned int currentDegree = 0;
  Term newTerm;
  bool firstTerm=true;

  // look at each term 
  for(Term t:_poly)
    {
      // if this si the first pass, update current degree. 
      if (firstTerm)
	{
	  currentDegree=t.degree();
	  newTerm = t;
	  firstTerm=false;
	}
      else if (t.degree()==currentDegree) // if this term matches degree
	{
	  newTerm.coefficient()+=t.coefficient();
	}
      else // degree change, need to take newTerm and add to new Poly
	{
	  if (newTerm.coefficient()!=0)
	    newPoly.push_back(newTerm);

	  // also need to update current degree and re-initialize newTerm
	  currentDegree=t.degree();
	  newTerm=t;
	}
    }

  //last term would not yet have been added to normalized polynomial ...
  if (newTerm.coefficient()!=0)
    newPoly.push_back(newTerm);
  
  _poly=newPoly;
}

// unary -
const Polynomial&
Polynomial::operator-() const
{
  Polynomial *ans = new Polynomial;

  // negate each term 
  for (Term ptr:_poly)
    {
      Term newTerm;// = new Term();
      newTerm=ptr;
      newTerm.coefficient()=-ptr.coefficient();
      ans->addTerm(newTerm);
    }
  return *ans;
}

// read a polynomial
istream&
Polynomial::read(istream &is)
{
  Term myTerm;
  _poly.clear(); // cleear out polynomial first. 
  
  is >> myTerm;

  while(myTerm.coefficient()!=0)
    {
      addTerm(myTerm);
      is >> myTerm;
    }

  normalize();

  return is;
}


// overlaoaded >> for Polynomial
istream& operator>> (istream &is, Polynomial &p)
{
  return p.read(is);
}

// overloaded << for Polynomial
ostream& operator<< (ostream &os, const Polynomial &p)
{
  return p.print(os);
}
