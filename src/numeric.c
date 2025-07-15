#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "term.h"
#include "util.h"
#include "numeric.h"


double bisection(Term *termHead,double a,double b,double epsilon,int stopCriterion,int maxIteration)
{
    double c=0;
    int i;

    if (calculateTheFunction(termHead,a) * calculateTheFunction(termHead,b) >= 0)
    {
        printf("Incorrect initial interval [a, b]. The function should have opposite signs at the endpoints.\n");
        return -1;
    }

    for (i=0 ; i<maxIteration ; i++)
    {
        c=(a+b)/2;
        printf("-----------------------------------\n%d. ITERATION\n",i);
        printf("\nf(a=%lf)=%lf\nf(c=%lf)=%lf\nf(b=%lf)=%lf\n\n",a,calculateTheFunction(termHead,a),c,calculateTheFunction(termHead,c),b,calculateTheFunction(termHead,b));
        if ((fabs(calculateTheFunction(termHead,c)) <= epsilon && stopCriterion==0) || ((b-a)/pow(2,i) < epsilon && stopCriterion==1))
        {
            return c;
        }
        if (calculateTheFunction(termHead,c) * calculateTheFunction(termHead,a) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }
    printf("Bisection method did not converge within the maximum number of iterations.\n");
    return c;
}

double regulaFalsi(Term *termHead,double a,double b,double epsilon,int stopCriterion,int maxIteration)
{
    double c=0,fa,fb,fc;
    int i;

    if (calculateTheFunction(termHead,a) * calculateTheFunction(termHead,b) >= 0)
    {
        printf("Incorrect initial interval [a, b]. The function should have opposite signs at the endpoints.\n");
        return -1;
    }

    for (i=0 ; i<maxIteration ; i++)
    {
        fa=calculateTheFunction(termHead,a);
        fb=calculateTheFunction(termHead,b);
        c=(b*fa-a*fb)/(fa-fb);
        fc=calculateTheFunction(termHead,c);
        printf("-----------------------------------\n%d. ITERATION\n",i);
        printf("\nf(a=%lf)=%lf\nf(c=%lf)=%lf\nf(b=%lf)=%lf\n\n",a,fa,c,fc,b,fb);
        if ((fabs(fc) <= epsilon && stopCriterion==0) || ((b-a)/pow(2,i) < epsilon && stopCriterion==1))
        {
            return c;
        }
        if (fc * fa < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }
    printf("Regula-Falsi method did not converge within the maximum number of iterations.\n");
    return c;
}

double newtonRaphson(Term *func,Term *derivative,double x,double epsilon,int maxIteration)
{
    double c=x,fc,fx,fdx;
    int i;
    for (i=0 ; i<maxIteration ; i++)
    {
        x=c;
        fx=calculateTheFunction(func,x);
        fdx=calculateTheFunction(derivative,x);
        c=x-fx/fdx;
        fc=calculateTheFunction(func,x);
        printf("-----------------------------------\n%d. ITERATION\n",i);
        printf("\nf(%lf)=%lf\nf'(%lf)=%lf\nfc(%lf)=%lf\n\n",x,fx,x,fdx,c,fc);
        if (fabs(fc) <= epsilon )
        {
            return c;
        }
    }
    printf("Newton-Raphson method did not converge within the maximum number of iterations.\n");
    return c;
}

double numericDerivative(Term *func,double x,double h,int option)
{
    double x2,fx,fx2;
    if(option==0)/*merkezi*/
    {
        x2=x+h;
        x-=h;
    }
    else if(option==1)/*ileri*/
    {
        x2=x+h;
    }
    else/*geri*/
    {
        x2=x;
        x-=h;
    }
    fx=calculateTheFunction(func,x);
    fx2=calculateTheFunction(func,x2);
    return (fx2-fx)/(x2-x);

}

double simpson1_3(Term *func,double a,double b,int n)
{
    int i;
    double h,fx,sum,x;
    h=(b-a)/n;
    sum = calculateTheFunction(func,a) + calculateTheFunction(func,b);
    for(i=1; i<n; i++)
    {
        x=a+i*h;
        fx=calculateTheFunction(func,x);
        if (i%2==0)
        {
            sum+=2*fx;
        }
        else
        {
            sum+=4*fx;
        }
    }
    return (h/3)*sum;
}

double simpson3_8(Term *func,double a,double b,int n)
{
    double h,sum,x,fx;
    int i;
    n*=3;
    h=(b-a)/n;
    sum=calculateTheFunction(func,a)+calculateTheFunction(func,b);
    for (i=1; i<n; i++)
    {
        x=a+i*h;
        fx=calculateTheFunction(func,x);
        printf("f(%lf)=%lf\n",x,fx);
        if (i%3==0)
        {
            sum+=2*fx;
        }
        else
        {
            sum+=3*fx;
        }
    }

    return (3*h/8)*sum;
}

double trapezoidal(Term *func,double a,double b,int n)
{
    double h,sum,x,fx;
    int i;

    h=(b-a)/n;
    sum=calculateTheFunction(func,a)+calculateTheFunction(func,b);
    /*printf("f(%lf)=%lf\n",a,calculateTheFunction(func,a));*/
    for (i=1; i<n; i++)
    {
        x=a+i*h;
        fx=calculateTheFunction(func,x);
        sum+=2*fx;
        /*printf("2*f(%lf)=%lf\n",x,2*fx);*/
    }
    /*printf("f(%lf)=%lf\n",b,calculateTheFunction(func,b));*/
    return (h/2)*sum;
}

double gregoryNewtonInterpolation()
{
    double *x,*y,**diffTable,value,result,productTerm,h;
    int n,i,j;

    printf("Please enter the number of known values\n");
    scanf("%d",&n);
    x=(double *)malloc(n*sizeof(double));
    y=(double *)malloc(n*sizeof(double));
    diffTable=(double **)malloc(n*sizeof(double *));
    for (i=0; i<n; i++)
    {
        diffTable[i]=(double *)malloc(n*sizeof(double));
    }

    printf("Please enter the x values\n");
    for (i=0; i<n; i++)
    {
        scanf("%lf",&x[i]);
    }
    printf("Please enter the y values\n");
    for (i=0; i<n; i++)
    {
        scanf("%lf",&y[i]);
    }
    printf("Please enter the x value to interpolate\n");
    scanf("%lf",&value);

    for(i=0; i<n; i++)
    {
        diffTable[i][0]=y[i];
    }
    for(j=1; j<n; j++)
    {
        for(i=0; i<n-j; i++)
        {
            diffTable[i][j]=diffTable[i+1][j-1]-diffTable[i][j-1];
        }
    }
    result=diffTable[0][0];
    productTerm=1;
    h=x[1]-x[0];
    i=1;
    while(i<n && diffTable[0][i]!=0)
    {
        productTerm*= (value-x[i-1]) / (i*h);
        result+=productTerm*diffTable[0][i];
        i++;
    }

    free(x);
    free(y);
    for (i=0; i<n; i++)
    {
        free(diffTable[i]);
    }
    free(diffTable);

    return result;
}

int getInverse(double **mat,double **inv, int n)
{
    double **adj,det;
    int i,j;

    det = determinant(mat, n);
    if(det==0)
    {
        printf("Singular matrix, can't find its inverse\n");
        return;
    }

    adj=(double **)malloc(n*sizeof(double *));
    for(i=0; i<n; i++)
    {
        adj[i]=(double *)malloc(n*sizeof(double));
    }
    adjoint(mat, adj, n);

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            inv[i][j]=adj[i][j]/det;
        }
    }

    for(i=0; i<n; i++)
    {
        free(adj[i]);
    }
    free(adj);

    return inv;
}

void gaussElimination(double **a, double *b, double *x, int n)
{
    int i, j, k;
    double factor;

    for(k=0; k<n-1; k++)
    {
        for(i=k+1; i<n; i++)
        {
            factor = a[i][k] / a[k][k];
            for(j=k; j<n; j++)
            {
                a[i][j]=a[i][j] - factor*a[k][j];
            }
            b[i]=b[i] - factor*b[k];
        }
    }

    x[n-1]=b[n-1]/a[n-1][n-1];
    for(i=n-2; i>=0; i--)
    {
        x[i]=b[i];
        for(j=i+1; j<n; j++)
        {
            x[i]=x[i]-a[i][j]*x[j];
        }
        x[i]=x[i]/a[i][i];
    }
}

void gaussSeidel(double **A, double *b, double *x, int n,int maxIteration,double epsilon)
{
    int i,j,maxRow,iter,k,t;
    double *temp,tempVal,sum,norm,*newX;

    /*put the largest number to the diagonal*/
    for(i=0; i<n; i++)
    {
        maxRow=i;
        for(j=i+1; j<n; j++)
        {
            if(fabs(A[j][i])>fabs(A[maxRow][i]))
            {
                maxRow=j;
            }
        }
        if(maxRow!=i)
        {
            temp = A[i];
            A[i] = A[maxRow];
            A[maxRow] = temp;

            tempVal = b[i];
            b[i] = b[maxRow];
            b[maxRow] = tempVal;
        }
        for(k=0; k<n; k++)
        {
            for(t=0; t<n; t++)
            {
                printf("%lf ", A[k][t]);
            }
            printf("| %lf\n");
        }
    }

    newX = (double *)malloc(n * sizeof(double));
    for(i=0; i<n; i++)
    {
        newX[i]=x[i];
    }

    iter = 0;
    norm=epsilon+1;
    while (iter < maxIteration && norm>epsilon)
    {
        for(i=0; i<n; i++)
        {
            sum = b[i];
            for(j=0; j<n; j++)
            {
                if(j!=i)
                {
                    sum -= A[i][j] * newX[j];
                }
            }
            newX[i] = sum / A[i][i];
        }
        norm = 0.0;
        for(i=0; i<n; i++)
        {
            norm += fabs(newX[i] - x[i]);
        }
        for(i=0; i<n; i++)
        {
            x[i] = newX[i];
        }
        iter++;
    }
    free(newX);
}
