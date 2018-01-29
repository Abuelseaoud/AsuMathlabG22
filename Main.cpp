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






CMatrix functionExe(int i,CMatrix &m,int r=0,int c=0)
{
	switch(i)
	{   case 0:
	           {
	    	     return sinh(m);
	             break;

	    	   }
	         
	    case 1: 
	            {
	            	return cosh(m);
	                break;
	            }
	         
	     case 2:
	           {
	    	     return tanh(m);
	             break;

	    	   }
	    case 3:
	           {
	    	     return coth(m);
	             break;

	    	   }
	    case 4:
	           {
	    	     return sech(m);
	             break;

	    	   }
	    case 5:
	           {
	    	     return csch(m);
	             break;

	    	   }
	         
	    case 6: 
	            {
	            	return sin(m);
	                break;
	            }
	         
	    case 7:
	           {
	    	     return cos(m);
	             break;

	    	   }
	    case 8:
	           {
	    	     return tan(m);
	             break;

	    	   }
	    case 9:
	           {
	    	     return cot(m);
	             break;

	    	   }
	    case 10:
	           {
	    	     return sec(m);
	             break;

	    	   }
	         
	    case 11: 
	            {
	            	return csc(m);
	                break;
	            }
	         
	    case 12:
	            {
	    	     return asin(m);
	             break;

	    	    }
	    case 13:
	           {
	    	     return acos(m);
	             break;

	    	   }
	    case 14:
	           {
	    	     return atan(m);
	             break;

	    	   }
	    case 15:
	           {
	    	     return acot(m);
	             break;

	    	   }
	         
	    case 16: 
	            {
	            	return asec(m);
	                break;
	            }
	         
	     case 17:
	           {
	    	     return acsc(m);
	             break;

	    	   }
	    case 18:
	           {
	    	     return sqrt(m);
	             break;

	    	   }
	   case 19:
	           {
	           	
	    	     return CMatrix (r,c,3,0);
	             break;

	    	   }
            					                  
        case 20:
	           { 
	    	     return CMatrix (r,c,2,0);
	             break;

	    	   }
	         
	    case 21: 
	            {
	            	return CMatrix (r,c,0,0);
	                break;
	            }
	         
	     case 22:
	           {
	    	     return CMatrix (r,c,1,0);
	             break;

	    	   }
	    case 23:
	           {
	    	     return log(m);
	             break;

	    	   }
	    case 24:
	           {
	    	     return ln(m);
	             break;

	    	   }
	     case 25:
	           {
	    	     return exp(m);
	             break;

	    	   }
	         
	                					           
 
	         
	}  		
	         
}
CMatrix Execution(string s )
{

	for (int x=0;x<26;x++)
	{
    		while(s.find(functionsname[x])!=-1)
    			{	
    				    string func;
    				    int index=s.find(functionsname[x]);
    				    int counter=0;
    				    int flag=0;
        				for(int z=index;z<s.length();z++)
        					{	
            					if(s[z]=='(')
                					{	counter++;
                    					flag=1;
                    				}
            					if(s[z]==')')
                					{	counter--;
                    					flag=1;
                    				}
            					if(counter==0&&flag==1)
            						{
                						func=s.substr(index+functionsname[x].length()+1,z-index-functionsname[x].length()-1);
                						string func1;
                						CMatrix e(0);
                						if(x==19||x==20||x==21||x==22)
                						{
                							func1=func.substr(func.find(",")+1);
                							func.erase(func.find(","));
                							e=Execution(func1);
                						}
                							
                						CMatrix c=Execution(func);
                					
                						c=functionExe(x,c,c(0,0),e(0,0));
    									
                						tempMatrices[tempNVar]=c;
                						////put the name of temp matrix 
                						
                						
                						
                						
                						if(index==0)
                						{
                							s.erase(index,z-index+1);
                							s=tempvaribleNames[tempNVar]+s;
                						}
                						else if(z==(s.length()-1))
                						{
                							s.erase(index,z-index+1);
                							s=s+tempvaribleNames[tempNVar];
                						}
                						else 
                						{
                								s=s.substr(0,index)+tempvaribleNames[tempNVar]+s.substr(z+1);
                						}
                							tempNVar++;
                							break;
            						}


        					}	
    			}




	}

  

	return postfixCalculation(s);

}
void errordetection(string &s)
{

	int counter =0;
	if(((   Isoperator(s[0]) && (s[0]!='+'&&s[0]!='-')|| Isoperator(s[s.length()-1]))))   throw("error:invalid expression");
	for(int i=0;i<s.length()-1;i++)
	{

		if(Isoperator(s[i+1])&&Isoperator(s[i]))
		{
			if(s[i+1]=='*'&&s[i]=='*')
			{
				s[i]='.';s[i+1]='^';
			}
			else if(s[i]==s[i+1])
			{

				throw("error:invalid expression");
			}
			else if(s[i+1]=='+'&& s[i]!='\'')
			{
                       s.erase(i+1,1);
			}
			else if(s[i+1]=='-')

			{
				    int counter =0;
				    s.replace(i+1,1,"(-1*");
                     cout<<i+5<<endl;
                     cout<<s.length()<<endl;
                     int j=i+5;
                     int q=s.length();
				    for( ; j<q ;j++)
				    	{
				    		
				    		if(Isoperator(s[j]) && counter==0)  { char w =s[j]; s.replace(j,1,")"+w); break;}
				    	    else if (s[j]=='(') counter++;
				    	    else if (s[j]==')') counter--;
				    	    if(j==(s.length()-1)) s=s+")"; 
				    	}	
                     cout<<s<<endl;
                      // throw("error: please use () ");
			}
			else{


					throw("error:invalid expression");
				}
		}









		if(s[i]=='(')
		{
			counter++;
			if(Isoperator(s[i+1]) && ((s[i+1]!='+')&&(s[i+1]!='-'))) throw("error:invalid expression");
		}
		else if(s[i]==')')
		{
			counter--;
			if(Isoperator(s[i-1])) throw("error:invalid expression");
		}

	}
	if(counter) throw("error:invalid expression");
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
