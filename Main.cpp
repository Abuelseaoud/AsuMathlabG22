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
string * varibleNames = new string[20];
//array of Matrices
CMatrix * Matrices = new CMatrix[20];
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


/* operation string to operation code*/

void operationMaking(string operation, string &destination, string& MatrixA, string& MatrixB, char &Operator)
{
	string code = operation;



	string delimiter = ".\'/*-+";
	// get the name of destination matrix
	destination = code.substr(0, code.find('='));

	for (int i = 0; i<6; i++)
	{
		if ((code.find(delimiter[i])>0) && (code.find(delimiter[i])<code.length()))
		{
			if (delimiter[i]=='.')
			{
				//get the type of operation
				Operator = delimiter[i];
				// get the name of matrix 1 it will contain a number 
				MatrixA = code.substr(code.find('=') + 1, code.find('/') - code.find('=') - 1);
				// get the name of matrix 2
				MatrixB = code.substr((code.find('/')) + 1);
				int pos = MatrixB.find(';');
				if (pos>=0 && pos<code.length())
				{
					MatrixB.erase(pos, 1);
				}
				break;
				
			}
			else if (delimiter[i]=='\'')
			{
				//get the type of operation
				Operator = delimiter[i];
				// get the name of matrix 1
				MatrixA = code.substr(code.find('=') + 1, code.find(delimiter[i]) - code.find('=') - 1);
				break;
			}
			else
			{
				//get the type of operation
				Operator = delimiter[i];

				// get the name of matrix 1
				MatrixA = code.substr(code.find('=') + 1, code.find(delimiter[i]) - code.find('=') - 1);

				// get the name of matrix 2
				MatrixB = code.substr((code.find(delimiter[i])) + 1);
				int pos = MatrixB.find(';');
				if (pos>=0 && pos<code.length())
				{
					MatrixB.erase(pos, 1);
				}
				break;
			}

		}
	}
	
	
	
}




// fun convert string into small element to initialize CMAtrix
string MatrixInitializingString(string code, string & destinationName)
{
	//get matrix Name
	destinationName = code.substr(0, code.find('='));
	// return matrix value
	return code.substr(code.find('['), code.find(']') - code.find('[') + 1);

}
/////////////////////////////////////////////////////////////////////////////////
void excute(string operation)
{
	if ( (operation.find("[")>=0) && (operation.find("[")<operation.length() ) )
	{
		CMatrix x(MatrixInitializingString(operation, varName));
		int k = index(varName, varibleNames, NVar);
		if (k != -1)
			Matrices[k] = x;
		else
		{

			Matrices[NVar] = x;
			trimSpace(varName);
			varibleNames[NVar] = varName;
			NVar=NVar+1;
		}
		

		
	}

	else if ((operation.find("=")>=0) && (operation.find("=")<operation.length()))
	{
		/*trimSpace(operation);*/
		operationMaking(operation, Matrix3, Matrix1, Matrix2, Operator);
		int m;
		operation=operation.substr(operation.find("=")+1);
		for(int h=0;h<NVar;h++)
		{
			if(operation.find(varibleNames[h])!=-1)
			{
				if(varibleNames[h]==Matrix1){m=h;}
				else{m=h; break;}

			}
		}
		int M1 = index(Matrix1, varibleNames, NVar);
		int M2 = m;
		int M3 = index(Matrix3, varibleNames, NVar);
		switch (Operator)
		{
		case '*':
		{
					if (M1 == -1 || M2 == -1) throw("Error:you try to make operation on undefine matrix");
					else
					{
						CMatrix result = Matrices[M1] * Matrices[M2];

						if (M3 != -1)
							Matrices[M3] = result;
						else
						{

							Matrices[NVar] = result;
							trimSpace(Matrix3);
							varibleNames[NVar] = Matrix3;
							NVar++;
						}

						cout << result;
						break;
					}
					

		}

		case '/':
		{
					if (M1 == -1 || M2 == -1) throw("Error:you try to make operation on undefine matrix");
					if(Matrices[M2].getDeterminant()==0) {cout<<"error:can't measure div as a second Matrix is a singular Matrix "<<endl; break;}
					else
					{
						CMatrix result = Matrices[M1] / Matrices[M2];

						if (M3 != -1)
							Matrices[M3] = result;
						else
						{

							Matrices[NVar] = result;
							trimSpace(Matrix3);
							varibleNames[NVar] = Matrix3;
							NVar++;
						}

						cout << result;
						break;
					}
		}

		case '-':
		{
					if (M1 == -1 || M2 == -1) throw("Error:you try to make operation on undefine matrix");
					else
					{
						CMatrix result = Matrices[M1] - Matrices[M2];

						if (M3 != -1)
							Matrices[M3] = result;
						else
						{

							Matrices[NVar] = result;
							trimSpace(Matrix3);
							varibleNames[NVar] = Matrix3;
							NVar++;
						}

						cout << result;
						break;
					}
		}

		case '+':
		{
					
					if (M1 == -1 || M2 == -1) throw("Error:you try to make operation on undefine matrix");
					else
					{
						CMatrix result = Matrices[M1] + Matrices[M2];

						if (M3 != -1)
							Matrices[M3] = result;
						else
						{

							Matrices[NVar] = result;
							trimSpace(Matrix3);
							varibleNames[NVar] = Matrix3;
							NVar++;
						}

						cout << result;
						break;
					}
		}

		case '\'':
		{

					if (M1 == -1) throw("Error:you try to make operation on undefine matrix");
					else
					{
						CMatrix result = Matrices[M1].getTranspose();

						if (M3 != -1)
							Matrices[M3] = result;
						else
						{

							Matrices[NVar] = result;
							trimSpace(Matrix3);
							varibleNames[NVar] = Matrix3;
							NVar++;
						}

						cout << result;
						break;
					}
		}

		case '.':
		{

					if ( M2 == -1) throw("Error:you try to make operation on undefine matrix");
					else
					{
						char*v = new char[50];
						strcpy(v, Matrix1.c_str());
						double value = atof(v);
						value = (value != 0) ? value : 1;
						CMatrix result = Matrices[M2].elementDiv(value);
						delete[]v;
						if (M3 != -1)
							Matrices[M3] = result;
						else
						{

							Matrices[NVar] = result;
							trimSpace(Matrix3);
							varibleNames[NVar] = Matrix3;
							NVar++;
						}

						cout << result;
						break;
					}
		}
		}

	}
cout<<endl<<endl<<endl;	

}




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

}