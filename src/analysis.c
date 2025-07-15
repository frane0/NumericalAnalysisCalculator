#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "term.h"
#include "analysis.h"
#include "util.h"

void analyzePoly(Poly *curPoly,char *curStr)
{
    char *partString;
    int i,flag,indexOfX,indexOfFirstBracket=-1,indexOfLastBracket=-1,bracketCounter=0,isNegative=0;
    curPoly->coefficient=1;
    curPoly->exponent=1;
    i=0;
    flag=0;
    if(curStr[0]=='-')
    {
        isNegative=1;
        curStr=takePiece(curStr,1,strlen(curStr)-1);
    }
    while(i<strlen(curStr) && curStr[i]!='x' && flag==0)
    {
        if(curStr[i]=='(')
        {
            indexOfFirstBracket=i;
            flag=1;
        }
        i++;
    }
    indexOfX=i;
    if(flag==0)
    {
        if(indexOfX==strlen(curStr)) /*constant*/
        {
            curPoly->exponent=0;
            curPoly->coefficient=calculateDouble(curStr);
        }
        else
        {
            /*
                Coefficient
            */

            if(indexOfX==0)/* Doesn't contain a coefficient */
            {
                curPoly->coefficient=1;
            }
            else
            {
                partString=takePiece(curStr,0,indexOfX-1);
                curPoly->coefficient=calculateDouble(partString);
            }

            /*
                Exponent
            */

            if(indexOfX==strlen(curStr)-1)/* Doesn't contain an exponent */
            {
                curPoly->exponent=1;
            }
            else
            {
                partString=takePiece(curStr,indexOfX+2,strlen(curStr));
                curPoly->exponent=atof(partString);
            }
        }
    }
    else
    {
        curPoly->resultant=createTerm();
        i=indexOfFirstBracket+1;
        flag=0;
        while(i<strlen(curStr) && flag==0)
        {
            if(curStr[i]=='(')
            {
                bracketCounter++;
            }
            if(curStr[i]==')')
            {
                bracketCounter--;
                if(bracketCounter<0)
                {
                    flag=1;
                    indexOfLastBracket=i;
                }
            }
            i++;
        }
        partString=takePiece(curStr,indexOfFirstBracket+1,indexOfLastBracket-1);
        curPoly->resultant=createTerm();
        parse(partString,curPoly->resultant);

        if(indexOfFirstBracket==0)
        {
            if(indexOfLastBracket==strlen(curStr)-1)
            {
                curPoly->exponent=1;
                curPoly->coefficient=1;
            }
            else
            {
                partString=takePiece(curStr,indexOfLastBracket+1,strlen(curStr)-1);
                partString=combineStr("x",partString);
                analyzePoly(curPoly,partString);
            }
        }
        else
        {
            if(indexOfLastBracket==strlen(curStr)-1)
            {
                partString=takePiece(curStr,0,indexOfFirstBracket-1);
                partString=combineStr(partString,"x");
                analyzePoly(curPoly,partString);
            }
            else
            {
                partString=takePiece(curStr,0,indexOfFirstBracket-1);
                partString=combineStr(combineStr(partString,"x"),takePiece(curStr,indexOfLastBracket+1,strlen(curStr)-1));
                analyzePoly(curPoly,partString);
            }
        }
    }
    if(isNegative==1)
    {
        curPoly->coefficient*=-1;
    }
}

void analyzeTrig(Trig *curTrig,char *curStr)
{
    char *partString;
    int i,flag,indexOfFunction=-1,bracketCounter=0,indexOfFirstBracket=-1,indexOfLastBracket=-1,isNegative=0;
    Poly *newPoly;
    i=0;
    flag=0;
    if(curStr[0]=='-')
    {
        isNegative=1;
        curStr=takePiece(curStr,1,strlen(curStr)-1);
    }

    while(i<strlen(curStr) && flag==0)
    {
        if(curStr[i]=='s')
        {
            if(curStr[i+1]=='i')
            {
                curTrig->func=SIN;
                indexOfFunction=i;
                flag=1;
            }
            else
            {
                curTrig->func=SEC;
                indexOfFunction=i;
                flag=1;
            }
        }
        else if(curStr[i]=='t')
        {
            curTrig->func=TAN;
            indexOfFunction=i;
            flag=1;
        }
        else if(curStr[i]=='c')
        {
            if(curStr[i+2]=='s')
            {
                curTrig->func=COS;
                indexOfFunction=i;
                flag=1;
            }
            else if(curStr[i+2]=='t')
            {
                curTrig->func=COT;
                indexOfFunction=i;
                flag=1;
            }
            else
            {
                curTrig->func=CSC;
                indexOfFunction=i;
                flag=1;
            }
        }
        i++;
    }

    /*
        Coefficient
    */

    if(indexOfFunction==0)
    {
        curTrig->coefficient=1;
    }
    else
    {
        partString=takePiece(curStr,0,indexOfFunction-2);
        newPoly=createPoly();
        analyzePoly(newPoly,partString);
        curTrig->coefficient=newPoly->coefficient;
        free(newPoly);
    }

    /*
        Exponent
    */

    if(curStr[indexOfFunction+3]=='^')
    {
        i=indexOfFunction+3;
        flag=0;
        bracketCounter=0;
        while(i<strlen(curStr) && flag==0)
        {
            if(curStr[i]=='(')
            {
                bracketCounter++;
            }
            if(curStr[i]==')')
            {
                bracketCounter--;
                if(bracketCounter==0)
                {
                    flag=1;
                }
            }
            i++;
        }
        indexOfFirstBracket=i;
        partString=takePiece(curStr,indexOfFunction+5,i-2);
        curTrig->exponent=createTerm();
        parse(partString,curTrig->exponent);
    }
    else
    {
        curTrig->exponent=createTerm();
        curTrig->exponent->type=0;
        curTrig->exponent->P=createPoly();
        curTrig->exponent->P->coefficient=1;
        curTrig->exponent->P->exponent=0;
        indexOfFirstBracket=indexOfFunction+3;
    }

    /*
        Resultant
    */

    i=indexOfFirstBracket;
    flag=0;
    bracketCounter=0;
    while(i<strlen(curStr) && flag==0)
    {
        if(curStr[i]=='(')
        {
            bracketCounter++;
        }
        if(curStr[i]==')')
        {
            bracketCounter--;
            if(bracketCounter==0)
            {
                flag=1;
                indexOfLastBracket=i;
            }
        }
        i++;
    }
    partString=takePiece(curStr,indexOfFirstBracket+1,indexOfLastBracket-1);
    curTrig->resultant=createTerm();
    parse(partString,curTrig->resultant);

    if(isNegative==1)
    {
        curTrig->coefficient*=-1;
    }
}

void analyzeLog(Log *curLog,char *curStr)
{
    char *partString;
    int i,flag,indexOfFunction=-1,bracketCounter=0,indexOfFirstBracket=-1,indexOfLastBracket=-1,isNegative=0;
    Poly *newPoly;
    i=0;
    flag=0;
    if(curStr[0]=='-')
    {
        isNegative=1;
        curStr=takePiece(curStr,1,strlen(curStr)-1);
    }
    while(i<strlen(curStr) && flag==0)
    {
        if(curStr[i]=='l')
        {
            indexOfFunction=i;
        }

        i++;
    }

    /*
        Coefficient
    */

    if(indexOfFunction==0)
    {
        curLog->coefficient=1;
    }
    else
    {
        partString=takePiece(curStr,0,indexOfFunction-2);
        newPoly=createPoly();
        analyzePoly(newPoly,partString);
        curLog->coefficient=newPoly->coefficient;
        free(newPoly);
    }

    /*
        Base
    */
    if(curStr[indexOfFunction+1]=='n')
    {
        curLog->base=createTerm();
        curLog->base->type=0;
        curLog->base->P=createPoly();
        curLog->base->P->coefficient=EULER;
        curLog->base->P->exponent=0;
        indexOfFirstBracket=indexOfFunction+2;
    }
    else
    {
        if(curStr[indexOfFunction+3]=='_')
        {
            i=indexOfFunction+3;
            flag=0;
            bracketCounter=0;
            while(i<strlen(curStr) && flag==0)
            {
                if(curStr[i]=='(')
                {
                    bracketCounter++;
                }
                if(curStr[i]==')')
                {
                    bracketCounter--;
                    if(bracketCounter==0)
                    {
                        flag=1;
                    }
                }
                i++;
            }
            indexOfFirstBracket=i;
            partString=takePiece(curStr,indexOfFunction+5,i-2);
            curLog->base=createTerm();
            parse(partString,curLog->base);
        }
        else
        {
            curLog->base=createTerm();
            curLog->base->type=0;
            curLog->base->P=createPoly();
            curLog->base->P->coefficient=10;
            curLog->base->P->exponent=0;
            indexOfFirstBracket=indexOfFunction+3;
        }
    }

    /*
        Resultant
    */

    i=indexOfFirstBracket;
    flag=0;
    bracketCounter=0;
    while(i<strlen(curStr) && flag==0)
    {
        if(curStr[i]=='(')
        {
            bracketCounter++;
        }
        if(curStr[i]==')')
        {
            bracketCounter--;
            if(bracketCounter==0)
            {
                flag=1;
                indexOfLastBracket=i;
            }
        }
        i++;
    }
    partString=takePiece(curStr,indexOfFirstBracket+1,indexOfLastBracket-1);
    curLog->resultant=createTerm();
    parse(partString,curLog->resultant);
    if(isNegative==1)
    {
        curLog->coefficient*=-1;
    }

}

void analyzeArc(Arc *curArc,char *curStr)
{
    /*
        arcsin - 1    arccos - 2
        arctan - 3    arccot - 4
        arcsec - 5    arccsc - 6
    */
    char *partString;
    int i,flag,indexOfFunction=-1,bracketCounter=0,indexOfFirstBracket=-1,indexOfLastBracket=-1,isNegative=0;
    Poly *newPoly;
    i=0;
    flag=0;
    if(curStr[0]=='-')
    {
        isNegative=1;
        curStr=takePiece(curStr,1,strlen(curStr)-1);
    }
    while(i<strlen(curStr) && flag==0)
    {
        if(curStr[i]=='a')
        {
            if(curStr[i+3]=='s')
            {
                if(curStr[i+4]=='i')
                {
                    curArc->func=ARCSIN;
                    indexOfFunction=i;
                    flag=1;
                }
                else
                {
                    curArc->func=ARCSEC;
                    indexOfFunction=i;
                    flag=1;
                }
            }
            else if(curStr[i+3]=='t')
            {
                curArc->func=ARCTAN;
                indexOfFunction=i;
                flag=1;
            }
            else if(curStr[i+3]=='c')
            {
                if(curStr[i+5]=='s')
                {
                    curArc->func=ARCCOS;
                    indexOfFunction=i;
                    flag=1;
                }
                else if(curStr[i+5]=='t')
                {
                    curArc->func=ARCCOT;
                    indexOfFunction=i;
                    flag=1;
                }
                else
                {
                    curArc->func=ARCCSC;
                    indexOfFunction=i;
                    flag=1;
                }
            }
        }

        i++;
    }
    /*
        Coefficient
    */

    if(indexOfFunction==0)
    {
        curArc->coefficient=1;
    }
    else
    {
        partString=takePiece(curStr,0,indexOfFunction-2);
        newPoly=createPoly();
        analyzePoly(newPoly,partString);
        curArc->coefficient=newPoly->coefficient;
        free(newPoly);
    }

    /*
        Exponent
    */

    indexOfFunction+=3;
    if(curStr[indexOfFunction+3]=='^')
    {
        i=indexOfFunction+3;
        flag=0;
        bracketCounter=0;
        while(i<strlen(curStr) && flag==0)
        {
            if(curStr[i]=='(')
            {
                bracketCounter++;
            }
            if(curStr[i]==')')
            {
                bracketCounter--;
                if(bracketCounter==0)
                {
                    flag=1;
                }
            }
            i++;
        }
        indexOfFirstBracket=i;
        partString=takePiece(curStr,indexOfFunction+5,i-2);
        curArc->exponent=createTerm();
        parse(partString,curArc->exponent);
    }
    else
    {
        curArc->exponent=createTerm();
        curArc->exponent->type=0;
        curArc->exponent->P=createPoly();
        curArc->exponent->P->coefficient=1;
        curArc->exponent->P->exponent=0;
        indexOfFirstBracket=indexOfFunction+3;
    }

    /*
        Resultant
    */

    i=indexOfFirstBracket;
    flag=0;
    bracketCounter=0;
    while(i<strlen(curStr) && flag==0)
    {
        if(curStr[i]=='(')
        {
            bracketCounter++;
        }
        if(curStr[i]==')')
        {
            bracketCounter--;
            if(bracketCounter==0)
            {
                flag=1;
                indexOfLastBracket=i;
            }
        }
        i++;
    }
    partString=takePiece(curStr,indexOfFirstBracket+1,indexOfLastBracket-1);
    curArc->resultant=createTerm();
    parse(partString,curArc->resultant);
    if(isNegative==1)
    {
        curArc->coefficient*=-1;
    }
}

void analyzeExp(Exp *curExp,char *curStr)
{
    char *partString;
    int i,flag,bracketCounter,indexOfExp,isNegative=0;
    if(curStr[0]=='-')
    {
        isNegative=1;
        curStr=takePiece(curStr,1,strlen(curStr)-1);
    }
    /*
        Base
    */
    if(curStr[0]=='(')
    {
        bracketCounter=1;
        i=1;
        flag=0;
        while(i<strlen(curStr) && flag==0)
        {
            if(curStr[i]=='(')
            {
                bracketCounter++;
            }
            if(curStr[i]==')')
            {
                bracketCounter--;
                if(bracketCounter==0)
                {
                    flag=1;
                }
            }
            i++;
        }
        indexOfExp=i;
        partString=takePiece(curStr,1,indexOfExp-2);
    }
    else
    {
        i=0;
        while(i<strlen(curStr) && curStr[i]!='^')
        {
            i++;
        }
        indexOfExp=i;
        partString=takePiece(curStr,0,indexOfExp-1);
    }
    curExp->base=createTerm();
    curExp->base->type=0;
    curExp->base->P=createPoly();
    curExp->base->P->resultant=createTerm();
    parse(partString,curExp->base->P->resultant);
    if(isNegative==1)
    {
        curExp->base->P->coefficient=-1;
        curExp->base->P->exponent=1;
    }
    else
    {
        curExp->base->P->coefficient=1;
        curExp->base->P->exponent=1;
    }
    /*
        Exponent
    */

    if(curStr[indexOfExp+1]=='(')
    {
        partString=takePiece(curStr,indexOfExp+2,strlen(curStr)-2);
    }
    else
    {
        partString=takePiece(curStr,indexOfExp+1,strlen(curStr)-1);
    }
    curExp->exponent=createTerm();
    parse(partString,curExp->exponent);

}

void analyzeFact(Fact *curFact,char *curStr)
{
    char *partString;
    int i,flag,bracketCounter,indexOfOperator,isNegative=0;
    if(curStr[0]=='-')
    {
        isNegative=1;
        curStr=takePiece(curStr,1,strlen(curStr)-1);
    }
    /*
        Find the operator
    */
    i=0;
    flag=0;
    while(i<strlen(curStr) && curStr[i]!='*' && curStr[i]!='/')
    {
        if(curStr[i]=='(')
        {
            bracketCounter=1;
            i++;
            while(i<strlen(curStr) && bracketCounter>0)
            {
                if(curStr[i]==')')
                {
                    bracketCounter--;
                }
                else if(curStr[i]=='(')
                {
                    bracketCounter++;
                }
                i++;
            }
            i--;
        }
        i++;
    }
    indexOfOperator=i;
    if(isNegative==1)
    {
        partString=takePiece(curStr,0,indexOfOperator-1);
    }
    else if(curStr[0]=='(' && curStr[indexOfOperator-1]==')')
    {
        partString=takePiece(curStr,1,indexOfOperator-2);
    }
    else
    {
        partString=takePiece(curStr,0,indexOfOperator-1);
    }

    curFact->function=createTerm();
    parse(partString,curFact->function);

    if(indexOfOperator<strlen(curStr))
    {

        partString=takePiece(curStr,indexOfOperator+1,strlen(curStr)-1);
        curFact->next=createFact();

        if(curStr[indexOfOperator]=='*')
        {
            curFact->next->op=MULTIPLY;
        }
        else if(curStr[indexOfOperator]=='/')
        {
            curFact->next->op=DIVIDE;
        }

        analyzeFact(curFact->next,partString);
    }
    else
    {
        curFact->next=NULL;
    }
}
