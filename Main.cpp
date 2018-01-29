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
CMatrix postfixCalculation(string  s)
{
		trimSpace(s);
    
	if(s[0]=='-'||s[0]=='+')
      {
    		s.insert(0,1,'0');

      }

    for(int i=1;i<s.length()-1;i++)
    {
    	if(s[i]=='\'')
    		{
    			 if(!(Isoperator(s[i+1])||s[i+1]==')'))
    			 	   s.insert(i+1,1,'*');

    		}
    	if((s[i]=='-'||s[i]=='+')&&s[i-1]=='(')
    		{
    			s.insert(i,1,'0');	
    		}
    }


    if(s.length()>1)
    {
    for(int i=1;i<(s.length()-2);i++)
       {
    	
    	if(s[i]==')'&&!(Isoperator(s[i+1])||s[i+1]=='\'')&&s[i+1]!=')'&&(s[i+1]!='.'&&Isoperator(s[i+2])))
    	{
    	  	s.insert(i+1,1,'*');
    	}

    	if(s[i]=='('&&(!Isoperator(s[i-1]))&&s[i-1]!='(')
    	{
    	  	s.insert(i,1,'*');
    	}
       }
    }

   


    

    int flag=1;
    int flagpower=0;
    stack <string> ope,post,ex;
    stack <CMatrix> result;
    int sum=0;
    char* infix = new char[s.length() + 1];
	strcpy(infix, s.c_str());
	char* spearators = "+/*-^% \'";
	char* token = strtok(infix, spearators);
	while (token)
	{ int counter=0;
	    sum+=strlen(token);
	    if(token[strlen(token)-1]=='.'){token[strlen(token)-1]=NULL;flagpower=1;}
	    while(token[0]=='('){ope.push("(");token++;}
	    while(token[strlen(token)-1]==')')
            {
                token[strlen(token)-1]=NULL;   counter++; 
            }

        post.push(token);
        while(counter)
           {
                while(ope.top()!="(")
                    {
                            post.push(ope.top());
                            ope.pop();
                    }
                    ope.pop();
                    counter--;
            }



         for(int i=0;i<1;i++)
            {
                if(ope.empty()) continue;
                 while((!HasHigherPrecedence(s.substr(sum,1),ope.top()))&&(!ope.empty()))
                        {
                            post.push(ope.top());
                            ope.pop();
                            if(ope.empty()) break;
                        }

            }

	    if(sum<s.length()) 
	    	{
	    		if((flagpower==1)&&(Isoperator(s[sum]))) ope.push(s.substr(sum,1)+".");
	    		else ope.push(s.substr(sum,1));
            }
        sum++;
		token = strtok(NULL, spearators);
		flag++;
		flagpower=0;
	}

	

while(!post.empty())
{
	ex.push(post.top());
	post.pop();
}



while(!ex.empty())
{
	string top=ex.top();
	int x=index(top,tempvaribleNames,tempNVar);
	int y=index(top,varibleNames,NVar);
	if(Isoperator(top[0]))
	{
		CMatrix A =result.top();
		result.pop();
        if(top[0]=='+')
        {
        	if(A.getn()==1) result.top()+=A(0,0);
        	else if(result.top().getn()==1) result.top()=A+result.top()(0,0);
        	else	result.top()+=A;
        }
        else if(top[0]=='-')
        {

        	if(A.getn()==1) result.top()-=A(0,0);
        	else if(result.top().getn()==1) result.top()=-A+result.top()(0,0);
        	else	result.top()-=A;
        }
        else if(top[0]=='*')
        {

        	if(A.getn()==1) result.top()=result.top()*A(0,0);
        	else if(result.top().getn()==1) result.top()=A*result.top()(0,0);
        	else	{
        		              if(top.length()==1)result.top()=result.top()*A;
        		              else
        		              {
        		              	if(A.getnR()!=result.top().getnR() ||A.getnC()!=result.top().getnC()) throw("error  Invalid Matrices Dim");
        		              	else
        		              	{
        		              		for(int r=0;r<A.getnR();r++) for(int c=0;c<A.getnC();c++)
        		              		 { result.top().setElement(r,c,result.top()(r,c)*A(r,c));}
        		              	}



        		              }
        		    }
        }
        else if(top[0]=='/')
        {
        	
        	if(A.getn()==1) result.top()=result.top()*(1.0/A(0,0));
        	else if(result.top().getn()==1) result.top()=A.elementDiv(result.top()(0,0));
        	else	{
        		              if(top.length()==1)result.top()=result.top()/A;
        		              else
        		              {
        		              	if(A.getnR()!=result.top().getnR() ||A.getnC()!=result.top().getnC()) throw("error  Invalid Matrices Dim");
        		              	else
        		              	{
        		              		for(int r=0;r<A.getnR();r++) for(int c=0;c<A.getnC();c++)
        		              		 result.top().setElement(r,c,result.top()(r,c)/A(r,c));
        		              	}



        		              }
        		    }

        }
        else if(top[0]=='%')
        {
        	int LS,RS;
        	LS=result.top()(0,0);
        	RS=A(0,0);
        	LS=LS%RS;
        	CMatrix H(LS);
        	result.top()=H;
        }

        else if(top[0]=='^')
        {    if (A.getn()==1)
        	{
        	if(top.length()>1) result.top()=result.top().powElement(A(0,0));
        	else if(result.top().getn()==1) result.top()=result.top().powElement(A(0,0));
        	else result.top()=result.top().pow_matrix(A(0,0));
       	    }
       	    else{
                    if(A.getnR()!=result.top().getnR() ||A.getnC()!=result.top().getnC()) throw("error  Invalid Matrices Dim");
                    else
                    {

                    		for(int r=0;r<A.getnR();r++) for(int c=0;c<A.getnC();c++)
        		              		 result.top().setElement(r,c,pow(result.top()(r,c),A(r,c)));

                    }
       	    }

        }
        else if(top[0]=='\'')
        {
        	result.push(A.getTranspose());
        }
	}
    else if(y!=-1)
    {
    	result.push(Matrices[y]);
    }
    else if(x!=-1)
    {
        result.push(tempMatrices[x]);

    }

    else
    {
    	if(isdigit(top[0]) )
    		{
    			CMatrix m(atof(top.c_str()));
    	        result.push(m);
    	    }

    	else if(top.length()==1)
    	    {
                   throw("undefine varible");
    	    }
    	else
    	{
    		if(isdigit(top[1])&&top[0]=='.')
    		{
    			
    			CMatrix m(atof(top.c_str()));
    	        result.push(m);
    	        
    	    
    		}
    		else throw("undefine varible");
    	}
    }




    ex.pop();

}


return result.top();



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
