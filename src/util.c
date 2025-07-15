#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "term.h"
#include "analysis.h"
#include "util.h"


void parse(char *text,Term *termHead)
{
    char **terms;
    char *curStr;
    int i,j,n=strlen(text),flag,term_start=0,term_end,term_number=0,bracketCounter=0,isNegative=0;

    Poly *curPoly;
    Trig *curTrig;
    Log *curLog;
    Arc *curArc;
    Exp *curExp;
    Fact *curFact;

    Term *curTerm=NULL,*prevTerm=NULL;

    terms=(char **)malloc(30 * sizeof(char *));
    for(i=0; i<30; i++)
    {
        terms[i]=(char *)malloc(50 * sizeof(char));
    }

    /*
        FIRST PARSING
    */
    if(text[0]=='-')
    {
        isNegative=1;
    }
    for(i=isNegative; i<n; i++) /*Split the whole string into term substrings*/
    {
        if(text[i]!='(')
        {
            if(text[i]=='+'||text[i]=='-')
            {
                term_end=i-1;
                if(text[term_start]=='+')
                {
                    for(j=term_start+1; j<=term_end; j++)
                    {
                        terms[term_number][j-term_start-1]=text[j];
                    }
                    terms[term_number][j-term_start-1]='\0';
                }
                else
                {
                    for(j=term_start; j<=term_end; j++)
                    {
                        terms[term_number][j-term_start]=text[j];
                    }
                    terms[term_number][j-term_start]='\0';
                }
                term_start=i;
                term_number++;
            }
        }
        else
        {
            bracketCounter++;
            while(bracketCounter>0)
            {
                i++;
                if(text[i]=='(')
                {
                    bracketCounter++;
                }
                if(text[i]==')')
                {
                    bracketCounter--;
                }
            }
        }
    }
    term_end=n;
    if(text[term_start]=='+')
    {
        for(j=term_start+1; j<=term_end; j++)
        {
            terms[term_number][j-term_start-1]=text[j];
        }
        terms[term_number][j-term_start]='\0';
    }
    else
    {
        for(j=term_start; j<=term_end; j++)
        {
            terms[term_number][j-term_start]=text[j];
        }
        terms[term_number][j-term_start+1]='\0';
    }
    *terms[term_number+1]=NULL;
    /*
    for(i=0;i<=term_number;i++)
    {
        printf("%s\n",terms[i]);
    }
    printf("\n--------------------------------------\n");
    */

    /*
        SECOND PARSING
    */
    for(i=0; i<=term_number; i++) /*Determine the types of each term and create the fitting structs.*/
    {
        j=0;
        flag=0;
        if(curTerm==NULL)
        {
            curTerm=termHead;
            prevTerm=termHead;
        }
        else
        {
            curTerm=createTerm();
            prevTerm->next=curTerm;
            prevTerm=curTerm;
        }
        while(j<strlen(terms[i]) && flag==0)
        {
            if(terms[i][j]!='(')
            {
                if(terms[i][j+1]=='x')
                {
                    if(j+3<strlen(terms[i]) && terms[i][j+2]=='^' && terms[i][j+3]=='(')
                    {
                        curTerm->type=EXP;
                        curTerm->E=createExp();
                        flag=1;
                    }
                    else if(j+3<strlen(terms[i]) && (terms[i][j+2]=='*' || terms[i][j+2]=='/') && terms[i][j+3]=='(')
                    {
                        curTerm->type=FACT;
                        curTerm->F=createFact();
                        flag=1;
                    }
                    else
                    {
                        curTerm->type=POLY;
                        curTerm->P=createPoly();
                        flag=1;
                    }
                }
                else if(terms[i][j]=='s' || terms[i][j]=='t' || terms[i][j]=='c')
                {
                    curTerm->type=TRIG;
                    curTerm->T=createTrig();
                    flag=1;
                }
                else if(terms[i][j]=='l')
                {
                    curTerm->type=LOG;
                    curTerm->L=createLog();
                    flag=1;
                }
                else if(terms[i][j]=='a')
                {
                    curTerm->type=ARC;
                    curTerm->A=createArc();
                    flag=1;
                }
                else if(terms[i][j]=='^' && terms[i][j+1]=='(')
                {
                    curTerm->type=EXP;
                    curTerm->E=createExp();
                    flag=1;
                }
            }
            else
            {
                bracketCounter=1;
                while(j<strlen(terms[i]) && bracketCounter>0)
                {
                    j++;
                    if(terms[i][j]=='(')
                    {
                        bracketCounter++;
                    }
                    if(terms[i][j]==')')
                    {
                        bracketCounter--;
                    }
                }
                j++;
                if(j<strlen(terms[i]))
                {
                    if(terms[i][j]=='^' && terms[i][j+1]=='(')
                    {
                        curTerm->type=EXP;
                        curTerm->E=createExp();
                        flag=1;
                    }
                    else if(terms[i][j]=='*' || terms[i][j]=='/')
                    {
                        curTerm->type=FACT;
                        curTerm->F=createFact();
                        flag=1;
                    }
                    else
                    {
                        curTerm->type=POLY;
                        curTerm->P=createPoly();
                        flag=1;
                    }
                }
                else
                {
                    curTerm->type=POLY;
                    curTerm->P=createPoly();
                    flag=1;
                }
            }
            j++;
        }
        if(flag==0)
        {
            curTerm->type=POLY;
            curTerm->P=createPoly();
        }
    }
    curTerm=termHead;
    /*
    for(i=0;i<=term_number;i++)
    {
        printf("%d\n",curTerm->type);
        curTerm=curTerm->next;
    }
    printf("\n-------------------------\n");
    */

    /*
        THIRD PARSING
    */
    curTerm=termHead;
    for(i=0; i<=term_number; i++)
    {
        curStr=terms[i];
        if(curTerm->type==POLY)
        {
            curPoly=curTerm->P;
            analyzePoly(curPoly,curStr);
            /*printf("coef of %s:%lf\nexpo of %s:%lf\n",curStr,curPoly->coefficient,curStr,curPoly->exponent);*/
        }
        else if(curTerm->type==TRIG)
        {
            curTrig=curTerm->T;
            analyzeTrig(curTrig,curStr);
            /*printf("coef of %s:%lf\n",curStr,curTrig->coefficient);*/
        }
        else if(curTerm->type==LOG)
        {
            curLog=curTerm->L;
            analyzeLog(curLog,curStr);
            /*printf("coef of %s:%lf\n",curStr,curLog->coefficient);*/
        }
        else if(curTerm->type==ARC)
        {
            curArc=curTerm->A;
            analyzeArc(curArc,curStr);
            /*printf("coef of %s:%lf\n",curStr,curArc->coefficient);*/
        }
        else if(curTerm->type==EXP)
        {
            curExp=curTerm->E;
            analyzeExp(curExp,curStr);
        }
        else if(curTerm->type==FACT)
        {
            curFact=curTerm->F;
            analyzeFact(curFact,curStr);
        }
        curTerm=curTerm->next;
    }

}

double calculateTheFunction(Term *termHead, double x)
{
    double result=0, termResult=0, resultant=0, exponent=0, base=0;
    Term *term;
    Poly *curPoly;
    Trig *curTrig;
    Log *curLog;
    Arc *curArc;
    Exp *curExp;
    Fact *curFact;

    term=termHead;
    while(term!=NULL)
    {
        if(term->type==POLY)
        {
            curPoly=term->P;
            if(curPoly->resultant==NULL)
            {
                termResult=curPoly->coefficient*pow(x,curPoly->exponent);
            }
            else
            {
                resultant=calculateTheFunction(curPoly->resultant,x);
                termResult=curPoly->coefficient*pow(resultant,curPoly->exponent);
            }
        }
        else if(term->type==TRIG)
        {

            curTrig=term->T;
            exponent=calculateTheFunction(curTrig->exponent,x);
            resultant=calculateTheFunction(curTrig->resultant,x);
            if(curTrig->func==SIN)
            {
                resultant=sin(resultant);
            }
            else if(curTrig->func==COS)
            {
                resultant=cos(resultant);
            }
            else if(curTrig->func==TAN)
            {
                resultant=tan(resultant);
            }
            else if(curTrig->func==COT)
            {
                resultant=1/tan(resultant);
            }
            else if(curTrig->func==SEC)
            {
                resultant=1/cos(resultant);
            }
            else if(curTrig->func==CSC)
            {
                resultant=1/sin(resultant);
            }
            termResult=curTrig->coefficient*pow(resultant,exponent);
        }
        else if(term->type==LOG)
        {
            curLog=term->L;
            base=calculateTheFunction(curLog->base,x);
            resultant=calculateTheFunction(curLog->resultant,x);
            resultant=log(resultant)/log(base);
            termResult=curLog->coefficient*resultant;
        }
        else if(term->type==ARC)
        {
            curArc=term->A;
            exponent=calculateTheFunction(curArc->exponent,x);
            resultant=calculateTheFunction(curArc->resultant,x);
            if(curArc->func==ARCSIN)
            {
                resultant=asin(resultant);
            }
            else if(curArc->func==ARCCOS)
            {
                resultant=acos(resultant);
            }
            else if(curArc->func==ARCTAN)
            {
                resultant=atan(resultant);
            }
            else if(curArc->func==ARCCOT)
            {
                resultant=atan(1/resultant);
            }
            else if(curArc->func==ARCSEC)
            {
                resultant=acos(1/resultant);
            }
            else if(curArc->func==ARCCSC)
            {
                resultant=asin(1/resultant);
            }
            termResult=curArc->coefficient*pow(resultant,exponent);
        }
        else if(term->type==EXP)
        {
            curExp=term->E;
            exponent=calculateTheFunction(curExp->exponent,x);
            base=calculateTheFunction(curExp->base,x);
            termResult=pow(base,exponent);
        }
        else if(term->type==FACT)
        {
            curFact=term->F;
            termResult=1;
            while(curFact!=NULL)
            {
                resultant=calculateTheFunction(curFact->function,x);
                if(curFact->op==MULTIPLY)
                {
                    termResult*=resultant;
                }
                else
                {
                    termResult/=resultant;
                }
                curFact=curFact->next;
            }
        }
        result+=termResult;
        term=term->next;
    }
    return result;
}

double calculateDouble(char *curStr)
{
    int i=0,nextOp=1,flag=0;
    double result=1;
    while(i<strlen(curStr) && flag==0)
    {
        if(curStr[i]=='*' || curStr[i]=='/')
        {
            if(nextOp==1)
            {
                if(curStr[i-1]=='e')
                    result*=EULER;
                else if(curStr[i-1]=='p')
                    result*=PI;
                else
                    result*=atof(curStr);
            }
            if(nextOp==2)
            {
                if(curStr[i-1]=='e')
                    result/=EULER;
                else if(curStr[i-1]=='p')
                    result/=PI;
                else
                    result/=atof(curStr);
            }

            if(curStr[i]=='*')
                nextOp=1;
            else if(curStr[i]=='/')
                nextOp=2;

            if(i<strlen(curStr)-1)
            {
                curStr=takePiece(curStr,i+1,strlen(curStr)-1);
                i=-1;
            }
            else
                flag=1;
        }
        i++;
    }
    if(flag==0)
    {
        if(nextOp==1)
        {
            if(curStr[i-1]=='e')
                result*=EULER;
            else if(curStr[i-1]=='p')
                result*=PI;
            else
                result*=atof(curStr);
        }
        if(nextOp==2)
        {
            if(curStr[i-1]=='e')
                result/=EULER;
            else if(curStr[i-1]=='p')
                result/=PI;
            else
                result/=atof(curStr);
        }

    }
    return result;
}

char *takePiece(char *str, int index1, int index2)
{
    int i,n=index2-index1;
    char *newStr;
    newStr=(char *)malloc((index2-index1+2)*sizeof(char));
    for(i=0; i<=n; i++)
    {
        newStr[i]=str[i+index1];
    }
    newStr[i]='\0';
    return newStr;
}

char *combineStr(char *firstStr, char *secondStr)
{
    int i,n1=strlen(firstStr), n2=strlen(secondStr);
    char *newStr;
    newStr=(char *)malloc((n1+n2+1)*sizeof(char));
    for(i=0; i<n1; i++)
    {
        newStr[i]=firstStr[i];
    }
    for(i=0; i<n2; i++)
    {
        newStr[i+n1]=secondStr[i];
    }
    newStr[n1+n2]='\0';
    return newStr;
}


double **getMatrix(int n)
{
    double **mat;
    int i,j;

    mat=(double **)malloc(n*sizeof(double *));
    for(i=0; i<n; i++)
    {
        mat[i]=(double *)malloc(n*sizeof(double));
    }

    printf("Enter the elements of the matrix:\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%lf",&mat[i][j]);
        }
    }

    return mat;
}

double determinant(double **mat, int n)
{
    double det=0,**temp;
    int i,sign=1,f;
    if(n==1)
    {
        return mat[0][0];
    }

    temp=(double **)malloc(n*sizeof(double *));
    for(i=0; i<n; i++)
    {
        temp[i]=(double *)malloc(n*sizeof(double));
    }

    for(f=0; f<n; f++)
    {
        getCofactor(mat,temp,0,f,n);
        det+=sign*mat[0][f]*determinant(temp,n-1);
        sign=-sign;
    }

    for(i=0; i<n; i++)
    {
        free(temp[i]);
    }
    free(temp);

    return det;
}

void getCofactor(double **mat, double **temp, int p, int q, int n)
{
    int i = 0, j = 0;
    int row, col;
    for(row=0; row<n; row++)
    {
        for(col=0; col<n; col++)
        {
            if(row!=p&&col!=q)
            {
                temp[i][j++]=mat[row][col];
                if(j==n-1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjoint(double **mat, double **adj, int n)
{
    int sign = 1, i, j;
    double **temp;
    if (n==1)
    {
        adj[0][0]=1;
        return;
    }

    temp=(double **)malloc(n*sizeof(double *));
    for(i=0; i<n; i++)
    {
        temp[i] = (double *)malloc(n * sizeof(double));
    }

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            getCofactor(mat, temp, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, n - 1));
        }
    }

    for (i = 0; i < n; i++)
    {
        free(temp[i]);
    }
    free(temp);
}
