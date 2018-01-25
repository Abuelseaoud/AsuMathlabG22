#include "CMatrix.h"
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <exception>
using namespace std;

//global variables 
string varName, Matrix1, Matrix2, Matrix3;
char Operator;
int NVar = 0;
int MA,MB;
//array of varibles names
string * varibleNames = new string[30];
//array of Matrices
CMatrix * Matrices = new CMatrix[30];


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
int index(string varName, string * varibleNames, int NVar)
{

	for (int i = 0; i <= NVar; i++)
	{


		if (varName == varibleNames[i])
		{



			return i;
		}

	}
	return (-1);

}

///////////////////////////////////////////remove duplicated spaces //////////////////////////////////////////////////////////

void advancedTrim(string& s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
		{
			s.erase(i, 1);
			i--;
		}	
	}
}

///////////////////////////////////////////Trim spaces before and after operations//////////////////////////////////////
void trim(string& text)
{
	int n, startpos = 0;
	int pos;
	pos = myfind(text, startpos);
	do
	{
		n = 0;
		if (pos != -1)
		{
			if (text[pos + 1] == ' ')
			{
				text.erase(pos + 1, 1);
				startpos = pos + 1;
				n++;
			}
			if (text[pos - 1] == ' ')
			{
				text.erase(pos - 1, 1);
				startpos = pos;
				n++;
			}
			if (n == 0)
				startpos = pos + 1;
			pos = myfind(text, startpos);
		}
	} while (pos != -1);
}

int myfind(string& s, int pos)
{
	for (int i = pos; i < s.length(); i++)
	{

		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^' || (s[i] == '.' && s[i + 1] == '+') || (s[i] == '.' && s[i + 1] == '-') || (s[i] == '.' && s[i + 1] == '*') || (s[i] == '.' && s[i + 1] == '/') || (s[i] == '.' && s[i + 1] == '^'))
			return i;
	}

	return -1;
}

/*
int main(int argc, char*argv[])
{
			
	
	
		    try
			{
				string op;

				if (argc == 1)
				{
					while (1)
					{

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

						excute(op);

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

						if(op.find("[")==-1) {trimSpace(op); cout<<op<<endl;}
						excute(op);


					}
				}
				
			}
			catch (char* error)
			{
				cout << error << endl;
			}

		

	delete[] varibleNames;
	delete[] Matrices;

}*/