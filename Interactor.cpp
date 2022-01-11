#include <iostream>
#include <fstream>
#include <string>

#include "Polynomial.hpp"
#include "Term.hpp"
#include <stack>

using namespace std;
int main(int argc, char *arv[])
{
char input;
cout<< "Welcome to the Polynomial Calculator, what would you like to do?"<<endl;
cout<< ">>>";
//first input
cin>> input;

//build stack
stack<Polynomial> memory;

//run till user enter (q)uit
while(input != 'q')
	{
//takes input
	switch(input)
		{
//clear 
		case 'c': 
			{
			memory.pop();         				        				//removes the most recent entry
			if(memory.size()==0)
				{cout<<"The accumulator is empty."<<endl;} 
			else
				{cout << memory.top() << endl;}   					//returns the last polynomial and prints it
			break;
			}
//deletes
		case 'd': 
			{
			int sz = memory.size();                   						 //gets size of stack and removes that many elements	
			for(int i=0; i!=sz; i++)
				{
				memory.pop();
				}	 
			cout<<"The accumulator is empty."<<endl;
			break;
			}
//sets accumulator			
		case 's':
			{
			Polynomial poly;
			cout<< "Enter Polynomial to push: ";
			cin >> poly;                                   						 //take in a polynomial to use
			memory.push(poly);	               							 //pushes polynomial to the top of the stack
			
			cout << memory.top() << endl; 						//returns the last polynomial and prints it
			break;
			}
//Evaluates Polynomial at point	
		case 'e':
			{
			cout<< "Enter value of x at which to evaluate polynomial: ";
			double e;
			cin>> e;					        						 //takes in an int to use
			Polynomial eCurrent;
			eCurrent = memory.top(); 
			double evaluation = eCurrent.eval(e);
			cout<<"The value of the polynomial at " << e << " is: " << evaluation<< endl;
			cout << memory.top() << endl;                				//returns the last polynomial and prints it
			break;
			}
//add new term to current		
		case '+':
			{
			Polynomial current;	
			current = memory.top();            						//places current polynomial into usable varible
			memory.pop();										//removes top value
			
			Polynomial second;
			second = memory.top();            						//places the second polynomial in different varible
			memory.pop();			         						//removes top value
						
			Polynomial result;
			result = current + second;	 						//uses overloaded "+" function from polynomal class
			memory.push(result);                						 //pushes polynomial to the top of the stack
			cout << memory.top() << endl;               				//returns the last polynomial and prints it
			break;
			}
//subtracts given term		
		case '-':
			{
			Polynomial current;	
			current = memory.top();            						//places current polynomial into usable varible
			memory.pop();										//removes top value
			
			Polynomial second;
			second = memory.top();            						//places the second polynomial in different varible
			memory.pop();										//removes top value
						
			Polynomial result;
			result = second - current;	       						       //uses overloaded "-" function from polynomal class
			memory.push(result);                					      //pushes polynomial to the top of the stack
			cout << memory.top() << endl;                    			     //returns the last polynomial and prints it
			break;
			}
//Multiply			
		case '*':
			{
			Polynomial current;	
			current = memory.top();           					//places current polynomial into usable varible
			memory.pop();									//removes top value
			
			Polynomial second;
			second = memory.top();            					//places the second polynomial in different varible
			memory.pop();									//removes top value
						
			Polynomial result;
			result = current * second;	        					//uses overloaded "*" function from polynomal class
			memory.push(result);                					//pushes polynomial to the top of the stack
			cout << memory.top() << endl;              				//returns the last polynomial and prints it
			break;
			}
//print			
		case 'p':
			{
			if(memory.size()==0)
				{cout<<"The accumulator is empty."<<endl;}
			else
				{cout << memory.top() << endl;}               		//returns the last polynomial and prints it
			break;
			}
		default:
		cout << "you've selected an invalid function\n The current polynomial is:  " << memory.top() <<endl;
		
		
		}
		
//prompts for new action
	cout<< ">>>";
	cin>> input;
	}
	cout<< "Thank you for using polyCalc!"<<endl;
}








































