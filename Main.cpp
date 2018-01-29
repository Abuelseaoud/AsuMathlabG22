#include "CMatrix.h"
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <exception>
#include <stack>
#include <string.h>
#include "math.h"
#include <ctgmath>
using namespace std;

//global variables 
int NVar = 0;
int tempNVar = 0;
//array of varibles names
string * varibleNames = new string[100];
//array of Matrices
CMatrix * Matrices = new CMatrix[100];
const string  tempvaribleNames [20]= {"#","##","###","####","#####","######","#######","########","#########","##########","###########","############","#############","##############","##############",
                                      "################","#################","##################","###################","####################"};
//array of  temp Matrices
CMatrix * tempMatrices = new CMatrix[20];
const string functionsname []={ "sinh",	"cosh",	"tanh","coth","sech","csch",
	                            "sin","cos","tan","cot","sec","csc",	
                                "asin",	"acos","atan","acot","asec","acsc",	
                                "sqrt","rand","eye","zeros","ones","log10","log","exp"};


void trimend(string & x)
{
	for (int i = x.length() - 1; i<0; i--)
	{
		if (x[i] == ' ')
		{
			x.erase(i, 1);

			i--;
		}
		else
		{
			break;

		}
	}
}

void trimSpace(string & x)
{
	for (int i = 0; i<x.length(); i++)

	{
		if (x[i] == ' ')
		{
			x.erase(i, 1);

			i--;
		}

	}



}



/*  get varible index from  the array   */
int index(string varName, const string * varibleNames, int NVar)
{

	for (int i = 0; i < NVar; i++)
	{


		if (varName == varibleNames[i])
		{



			return i;
		}

	}
	return (-1);

}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op)
{
	int weight = -1;
	switch(op)
	{
	case '(':
        {weight = 0;
        break;}
    case '+':
	case '-':
		{weight = 1;

		break;}
	case '*':
	case '/':
    case '%':
		{weight = 2;
		break;}
	case '^':
	case '\'':
		{weight = 3;
		break;}
	}
	return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence( string op1,  string op2)
{
	int op1Weight = GetOperatorWeight(op1[0]);
	int op2Weight = GetOperatorWeight(op2[0]);

	return op1Weight > op2Weight ?  1: 0;
}
int Isoperator(char a)
{
	if(a=='+'||a=='-'||a=='*'||a=='/'||a=='%'||a=='^'||a=='\'')return 1;
	else return 0;
}


int main(int argc, char*argv[])
{

	
	 
	
	
				string op;

				if (argc == 1)
				{
					
					while (1)
					{
						try{
								cout<<">>";
								getline(cin, op);
								int m;
								m = op.find("[");
								if (m>=0 && m<op.length())
								{
									while (1)
									{
										m = op.find("]");
										if (m<0 || m >= op.length())
										{
											string temp;
											getline(cin, temp);
											op = op + temp;
										}
										else
										{
											break;
										}
									}
								}
                                    
								if(op.find("[")==-1) operationHandling(op);

								else ;


							}
							catch( const char * error)
								{
									cout<< error<<endl;
								}

					}

				}
				else
				{
					ifstream infile(argv[1]);
					while (!infile.eof())
					{

						getline(infile, op);
						int m;
						m = op.find("[");
						if (m>=0 && m<op.length())
						{
							while (1)
							{
								m = op.find("]");
								if (m<0 || m >= op.length())
								{
									string temp;
									getline(infile, temp);
									op = op + temp;
								}
								else
								{
									break;
								}
							}
						}

						if(op.find("[")==-1) 
								{
									try{operationHandling(op);}
									catch( const char * error)
									{
										cout<< error<<endl;
									}
								}	
						else ;


					}
				}
				
			

			
		

	delete[] varibleNames;
	delete[] Matrices;
	delete[] tempMatrices;







}
