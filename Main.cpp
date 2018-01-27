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

///////////////////////////////////////////////////Subtract the expression/////////////////////////////////////////
int findOPs(string& s, int pos)         // Amira's find function  
{
	for (int i = pos; i < s.length(); i++)
	if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^' || (s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n') 
		|| (s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's') || (s[i] == 't' && s[i + 1] == 'a' && s[i + 2] == 'n') 
		|| (s[i] == 'l' && s[i + 1] == 'o' && s[i + 2] == 'g') || (s[i] == 'l' && s[i + 1] == 'n')
		|| (s[i] == 's' && s[i + 1] == 'q' && s[i + 2] == 'r' && s[i + 3] == 't')
	   	|| (s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 't') || (s[i] == 's' && s[i + 1] == 'e' && s[i + 2] == 'c')
	    	|| (s[i] == 'c' && s[i + 1] == 's' && s[i + 2] == 'c') || (s[i] == 'e' && s[i + 1] == 'x' && s[i + 2] == 'p'))
			return i;
	return -1;
}
int findSpaceBefore(string& s, int pos)         
{
	for (int i = pos; i >= 0; i--)
	if (s[i] == ' ' || s[i] == '[' || s[i] == ']' || s[i] == ';')
		return i;
	return -1;
}
int findSpaceAfter(string& s, int pos)         
{
	for (int i = pos; i < s.length(); i++)
	if (s[i] == ' ' || s[i] == '[' || s[i] == ']' || s[i] == ';')
		return i;
	return -1;
}
void updateString(string& s1)                /*replace the part to send to alaa */
{
	string s;
	trim(s1);
	int pos = findOPs(s1, 0), pos1, pos2;
	while (pos != -1)
	{
		pos1 = findSpaceBefore(s1, pos);
		pos2 = findSpaceAfter(s1, pos);
		s = s1.substr(pos1 + 1, pos2 - pos1 - 1);
		// Alaa's fn
		s1 = s1.replace(pos1 + 1, pos2 - pos1 - 1, "Medhat"); // replace medhat with  alaa's fn .sendstring()
		pos = findOPs(s1, 0);
	}
}


////////////////////////////////////////////// Modify the string to match the standard format \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


string modify(string& s)
{
	CMatrix A;
	CMatrix B;
	string s1, s2, s3;
	int i;
	int j;
	int k;

	while (s.find("] [") != -1 || s.find("],[") != -1)
	{
		i = s.find("] [");
		k = s.find("],[");
		if (i != -1)
		{
			s1 = s.substr(i + 2);
		}
		else if (k != -1)
		{
			s1 = s.substr(k + 2);
		}
		j = s1.find("]");
		s1 = s1.substr(0, j + 1);
		A.copy(s1);

		if (i != -1)
		{
			s2 = s.substr(0, i + 1);
		}
		else if (k != -1)
		{
			s2 = s.substr(0, k + 1);
		}
		j = s2.rfind("[");
		s2 = s2.substr(j);
		B.copy(s2);

		B.concatinate(A);
		s = s.replace(j, s1.length() + s2.length() + 1, B.sendString());
	}
	while (s.find("[") != -1)
	{
		s.erase(s.find("["), 1);
	}
	while (s.find("]") != -1)
	{
		s.erase(s.find("]"), 1);
	}
	s = s + "]";
	s = '[' + s;
	if (s[1] == ' ') s.erase(1, 1);
	return s;

}

//////////////////////////////////////////////Parsing//////////////////////////////////////////////

string parse(string &operation)
{
	string varName, s2,s;
	int pos, flag=0, index;
	CMatrix x;
	if (operation.find("=") != -1)
	{
		varName = operation.substr(0, operation.find("="));
		trimSpace(varName);
		s2 = operation.substr(operation.find("=") + 1);
		if (s2.find("\r\n") != -1) s2 = s2.replace(s2.find("\r\n"), 2, ";");

		if (s2[s2.length() - 1] == ';')   // to know whether to print or not
		{
			flag = 1;
			s2.erase(s2.length() - 1, 1);
		}

		trimend(s2);					//removing extra spaces and update string
		advancedTrim(s2);
		//updateString(s2); 


		for (int i = 0; i <= NVar; i++)   //search if there's an existant matrix variable name (A or B etc.) in the string 
		{
			pos = s2.find(variableNames[i]);
			while (pos != -1)
			{
				s2.replace(pos, varName.length(), Matrices[i].sendString());
				pos = s2.find(variableNames[i]);
			}
		}

		s2 = modify(s2);   // the string is in the standard format of matrix
		x.copy(s2);
		for (int i = 0; i <= NVar; i++)  //search if the variable before = exists or not in variableNames
		{
			if (variableNames[i] == varName)         //update the value of existant matrix
				index = i;
			else									//add new matrix to Matrices
			{
				index = NVar;
				variableNames[index] = varName;
				NVar++;
				break;
			}
		}
		Matrices[index] = x;
		if (flag == 0){ cout << Matrices[index].getString(); } /*print the matrix when there is no semicolon in the end of the operation*/
	}

	//if just the Matrix name is written to be printed
	else
	{
		varName = operation;
		trimSpace(varName);
		trimend(varName);
		for (int i = 0; i <= NVar; i++)
		{
			if (variableNames[i] == varName)
				cout << Matrices[i].getString() << endl;
			//else throw("Error:you try to print undefined Matrix");
		}
	}

	return Matrices[index].sendString();
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
