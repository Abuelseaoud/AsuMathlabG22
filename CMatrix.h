/////////////////////////////////////////////////* Functions Declaration *///////////////////////////////////////////
#ifndef CMATRIX_H
#define CMATRIX_H
#include <iostream>
#include <string>

using namespace std;
 


class CMatrix
{

	int nR, nC;
	double** values;
	int checkzero(int r,int c);
public:

	CMatrix();                                      /* default Constructor */
	/*CMatrix(int nR, int nC); */                       /* constructor */
	CMatrix(const  CMatrix &m);                            /* Copy constructor */
	~CMatrix();						                /* Destructor */
	void reset();					                /* Reset */
	void setElement(int nR, int nC, double v);      /* to set an element with given coordinates & value to a matrix */
	double getElement(int r, int c);                /* to get an element with given coordinates from a matrix */
	void copy(const CMatrix& m);                          /* Copy Function */
	CMatrix getMinor(int r, int c);                 /* to get minor of a an element */
	double getDeterminant();		                /* to calculate the determinant of the matrix */
	CMatrix  getCofactor();			                /* to get cofactor of the matrix*/
	int getn();                                     /* to get the total number of ELEMENTS inside the matrix */
	int getnR();									/* to get the number of ROWS inside the matrix */
	int getnC();									/* to get the number of COLOUMS inside the matrix */
	CMatrix getTranspose();							/* to get the TRANSPOSE of the matrix */
	CMatrix  getInverse();							/* to get the INVERSE of the matrix */
	CMatrix operator = (const CMatrix& m);                /* equal ("=") opertor */
	double  operator [] (int index);				/* []operator to get an element with a given index */
	double  operator () (int index);				/* ()operator to get an element with a given index */
	double  operator () (int r, int c);				/* ()operator to get an element with a given Coordinates */
	friend istream& operator >> (istream &is, CMatrix& C);    /* Out Stream*/
	friend ostream& operator << (ostream &os, CMatrix& C);    /* In Stream Void*/
	///////////////////////////////////////////////////////////////////////////////////////////////
	void add(const CMatrix& m);
	void add(double c);
	void operator+=(const CMatrix& m);
	void operator+=(double c);
	CMatrix operator+(const CMatrix &m);
	CMatrix operator+(double c);
	void sub(const CMatrix& m);
	void sub(double c);
	void operator-=(const CMatrix& m);
	void operator-=(double c);
	CMatrix operator-(CMatrix m);
	CMatrix operator-(double c);
	void mul(const CMatrix& m);
	void mul(double c);
	void operator*=(const CMatrix& m);
	void operator*=(double d);
	CMatrix operator*(const CMatrix& m);
	CMatrix operator*(double d);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	enum MI{ MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };
	CMatrix(int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0);
	CMatrix(int nR, int nC, double first, ...);
	CMatrix(double d);
	CMatrix(string s);
	void copy(double d);
	void copy(string s);
	string getString();
	CMatrix operator=(double d);
	CMatrix operator=(string s);
	void addColumn(CMatrix& m);
	void addRow(CMatrix& m);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void div(const CMatrix& m);                    //division  
	void operator/=(const CMatrix& m);             // division matrix over matrix internal return
	void operator/=(double d);               //division matrix over value internal return
	CMatrix operator/(const CMatrix& m);           // division matrix over matrix returns matrix           
	CMatrix operator/(double d);             // division matrix over value returns matrix       
	CMatrix operator++();                    //Pre Increment
	CMatrix operator++(int);                 //Post Increment, int is not used 
	CMatrix operator--();                    //Pre Increment
	CMatrix operator--(int);                 //Post Increment, int is not used
	CMatrix operator-();                     //positive
	CMatrix operator+();                     //negative
	void setSubMatrix(int iR, int iC, CMatrix& m);                  /*setSubMatrix*/
	CMatrix getSubMatrix(int r, int c, int nr, int nc);                /*getSubMatrix*/
	CMatrix elementDiv(double d =1.0);                                           /*return matrix of element division*/



};


#endif // CMATRIX_H


