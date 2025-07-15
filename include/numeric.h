#ifndef NUMERIC_H
#define NUMERIC_H

#include "term.h"

double bisection(Term*,double,double,double,int,int);
double regulaFalsi(Term*,double,double,double,int,int);
double newtonRaphson(Term*,Term*,double,double,int);
double numericDerivative(Term*,double,double,int);
double simpson1_3(Term*,double,double,int);
double simpson3_8(Term*,double,double,int);
double trapezoidal(Term*,double,double,int);
double gregoryNewtonInterpolation(void);
int    getInverse(double **,double **,int);
void   gaussElimination(double **,double *,double *,int);
void   gaussSeidel(double **,double *,double *,int,int,double);

#endif
