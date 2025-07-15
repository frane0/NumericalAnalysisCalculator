#include <stdio.h>
#include <stdlib.h>
#include "term.h"
#include "util.h"
int main()
{
    menu();

    return 0;
}

void menu()
{
    int n,i,j,max,choice=-1;
    char *text,*textDerivative;
    char temp[500],x_tmp[20],tempDerivative[500];
    double *x,result,a,b,*c,epsilon,stop,**mat,**inv;
    Term *termHead=NULL, *derivative=NULL;
    while(choice!=0)
    {
        printf("\n\nNUMERICAL ANALYSIS CALCULATOR\n----------------------------------------\n\n");
        printf("Exit - 0\n");
        printf("Bisection - 1\n");
        printf("Regula-Falsi - 2\n");
        printf("Newton-Raphson - 3\n");
        printf("Inverse Matrix - 4\n");
        printf("Gauss Elimination - 5\n");
        printf("Gauss-Seidel - 6\n");
        printf("Numerical Differentiation - 7\n");
        printf("Simpson's Rule - 8\n");
        printf("Trapezoidal Rule - 9\n");
        printf("Gregory-Newton - 10\n");
        printf("Choice:\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 0:
            printf("The program is terminating...\n");
            break;

        case 1:
            printf("Bisection is selected. Please enter the function:\n");
            scanf("%s",temp);
            n=strlen(temp);
            text=malloc((n+1)*sizeof(char));
            strcpy(text,temp);
            termHead=createTerm();
            parse(text,termHead);
            printf("\nParsing completed. Please enter the a value\n");
            scanf("%s",&x_tmp);
            a=calculateDouble(x_tmp);
            printf("Please enter the b value\n");
            scanf("%s",&x_tmp);
            b=calculateDouble(x_tmp);
            printf("Please enter the epsilon value\n");
            scanf("%lf",&epsilon);
            printf("Please enter the stopping criterion:\n|f(c)|<=epsilon  :  0\n(b-a)/2^n<epsilon : 1\n");
            scanf("%d",&stop);
            printf("Please enter the number of max iterations\n");
            scanf("%d",&max);
            result=bisection(termHead,a,b,epsilon,stop,max);
            printf("RESULT=%lf\n",result);
            break;

        case 2:
            printf("Regula-Falsi is selected. Please enter the function:\n");
            scanf("%s",temp);
            n=strlen(temp);
            text=malloc((n+1)*sizeof(char));
            strcpy(text,temp);
            termHead=createTerm();
            parse(text,termHead);
            printf("\nParsing completed. Please enter the a value\n");
            scanf("%s",&x_tmp);
            a=calculateDouble(x_tmp);
            printf("Please enter the b value\n");
            scanf("%s",&x_tmp);
            b=calculateDouble(x_tmp);
            printf("Please enter the epsilon value\n");
            scanf("%lf",&epsilon);
            printf("Please enter the stopping criterion.\n|f(c)|<=epsilon  :  0\n(b-a)/2^n<epsilon : 1\n");
            scanf("%d",&stop);
            printf("Please enter the number of max iterations\n");
            scanf("%d",&max);
            result=regulaFalsi(termHead,a,b,epsilon,stop,max);
            printf("RESULT=%lf\n",result);
            break;

        case 3:
            printf("Newton-Raphson is selected. Please enter the function:\n");
            scanf("%s",temp);
            n=strlen(temp);
            text=malloc((n+1)*sizeof(char));
            strcpy(text,temp);
            termHead=createTerm();
            parse(text,termHead);
            printf("\nParsing of the function is completed. Please enter the derivative function\n");
            scanf("%s",tempDerivative);
            n=strlen(tempDerivative);
            textDerivative=malloc((n+1)*sizeof(char));
            strcpy(textDerivative,tempDerivative);
            derivative=createTerm();
            parse(textDerivative,derivative);
            printf("\nParsing completed. Please enter the x value\n");
            scanf("%s",&x_tmp);
            a=calculateDouble(x_tmp);
            printf("Please enter the epsilon value\n");
            scanf("%lf",&epsilon);
            printf("Please enter the number of max iterations\n");
            scanf("%d",&max);
            result=newtonRaphson(termHead,derivative,a,epsilon,max);
            printf("RESULT=%lf\n",result);
            break;

        case 4:
            printf("Inverse Matrix is selected.Enter the size of the matrix\n");
            scanf("%d",&n);
            mat=getMatrix(n);

            inv=(double **)malloc(n*sizeof(double *));
            for(i=0; i<n; i++)
            {
                inv[i]=(double *)malloc(n*sizeof(double));
            }
            getInverse(mat,inv,n);
            printf("\n\n\nINVERSE MATRIX:\n");
            for(i=0; i<n; i++)
            {
                for(j=0; j<n; j++)
                {
                    printf("%lf ", inv[i][j]);
                }
                printf("\n");
            }
            break;

        case 5:
            printf("Gauss Elimination is selected. Enter the size of the matrix\n");
            scanf("%d",&n);
            mat=getMatrix(n);
            c=(double *)malloc(n*sizeof(double));
            x=(double *)malloc(n*sizeof(double));
            printf("Enter the constants: \n");
            for(i=0; i<n; i++)
            {
                scanf("%lf", &c[i]);
            }
            gaussElimination(mat,c,x,n);
            for(i=0; i<n; i++)
            {
                printf("x[%d]=%lf\n",i,x[i]);
            }
            break;

        case 6:
            printf("Gauss-Seidel is selected. Enter the size of the matrix\n");
            scanf("%d",&n);
            mat=getMatrix(n);
            c=(double *)malloc(n*sizeof(double));
            x=(double *)malloc(n*sizeof(double));
            printf("Enter the constants: \n");
            for(i=0; i<n; i++)
            {
                scanf("\n%lf", &c[i]);
            }
            printf("Enter the initial x values: \n");
            for (i = 0; i < n; i++)
            {
                scanf("%lf", &x[i]);
            }
            printf("Please enter the epsilon value\n");
            scanf("%lf",&epsilon);
            printf("Please enter the number of max iterations\n");
            scanf("%d",&max);
            gaussSeidel(mat,c,x,n,max,epsilon);
            for(i=0; i<n; i++)
            {
                printf("\nx[%d]=%lf\n",i,x[i]);
            }

            break;

        case 7:
            printf("Numerical Differentiation is selected. Please enter the function:\n");
            scanf("%s",temp);
            n=strlen(temp);
            text=malloc((n+1)*sizeof(char));
            strcpy(text,temp);
            termHead=createTerm();
            parse(text,termHead);
            printf("\nParsing completed. Please enter the x value to differentiate\n");
            scanf("%s",&x_tmp);
            a=calculateDouble(x_tmp);
            printf("Please enter the h value\n");
            scanf("%lf",&b);
            printf("Please select the differentiation method:\ncentral : 0\nforward : 1\nbackward : 2\n");
            scanf("%d",&stop);
            result=numericDerivative(termHead,a,b,stop);
            printf("RESULT=%lf\n",result);
            break;

        case 8:
            printf("Simpson's Rule is selected. Please select the rule to use:\nSimpson's 1/3 : 1\nSimpson's 3/8 : 2\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("Simpson's 1/3 is selected. Please enter the function:\n");
                scanf("%s",temp);
                n=strlen(temp);
                text=malloc((n+1)*sizeof(char));
                strcpy(text,temp);
                termHead=createTerm();
                parse(text,termHead);
                printf("\nParsing completed. Please enter the a value\n");
                scanf("%s",&x_tmp);
                a=calculateDouble(x_tmp);
                printf("Please enter the b value\n");
                scanf("%s",&x_tmp);
                b=calculateDouble(x_tmp);
                printf("Please enter the n value\n");
                scanf("%d",&max);
                result=simpson1_3(termHead,a,b,max);
                printf("RESULT=%lf\n",result);
            }
            else if(choice==2)
            {
                printf("Simpson's 3/8 is selected. Please enter the function:\n");
                scanf("%s",temp);
                n=strlen(temp);
                text=malloc((n+1)*sizeof(char));
                strcpy(text,temp);
                termHead=createTerm();
                parse(text,termHead);
                printf("\nParsing completed. Please enter the a value\n");
                scanf("%s",&x_tmp);
                a=calculateDouble(x_tmp);
                printf("Please enter the b value\n");
                scanf("%s",&x_tmp);
                b=calculateDouble(x_tmp);
                printf("Please enter the n value\n");
                scanf("%d",&max);
                result=simpson3_8(termHead,a,b,max);
                printf("RESULT=%lf\n",result);

            }
            break;

        case 9:
            printf("Trapezoidal Rule is selected. Please enter the function:\n");
            scanf("%s",temp);
            n=strlen(temp);
            text=malloc((n+1)*sizeof(char));
            strcpy(text,temp);
            termHead=createTerm();
            parse(text,termHead);
            printf("\nParsing completed. Please enter the a value\n");
            scanf("%s",&x_tmp);
            a=calculateDouble(x_tmp);
            printf("Please enter the b value\n");
            scanf("%s",&x_tmp);
            b=calculateDouble(x_tmp);
            printf("Please enter the n value\n");
            scanf("%d",&max);
            result=trapezoidal(termHead,a,b,max);
            printf("RESULT=%lf\n",result);
            break;

        case 10:
            printf("Gregory-Newton is selected. ");
            result=gregoryNewtonInterpolation();
            printf("RESULT=%lf\n",result);
            break;

        default:
            printf("Wrong input.\n");
            break;

        }
    }
}

