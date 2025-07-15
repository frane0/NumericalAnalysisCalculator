#ifndef UTIL_H
#define UTIL_H

#include "term.h"
#define PI    3.14159265359
#define EULER 2.71828182846

void     parse(char*, Term*);
double   calculateTheFunction(Term*, double);
double   calculateDouble(char*);
char*    takePiece(char*, int, int);
char*    combineStr(char*, char*);
double** getMatrix(int);
double   determinant(double**, int);
void     adjoint(double**, double**, int);
void     getCofactor(double**, double**, int, int, int);
void     menu(void);

#endif
