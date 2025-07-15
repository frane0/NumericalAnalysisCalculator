#include <stdio.h>
#include <stdlib.h>
#include "term.h"

Term *createTerm()
{
    Term *newTerm;
    newTerm=(Term *)malloc(sizeof(Term));
    if(newTerm==NULL)
    {
        printf("Memory allocation for a new Term failed.\n");
        return NULL;
    }
    newTerm->P=NULL;
    newTerm->T=NULL;
    newTerm->L=NULL;
    newTerm->A=NULL;
    newTerm->E=NULL;
    newTerm->F=NULL;
    newTerm->next=NULL;
    return newTerm;
}
Poly *createPoly()
{
    Poly *newPoly;
    newPoly=(Poly *)malloc(sizeof(Poly));
    if(newPoly==NULL)
    {
        printf("Memory allocation for a new Poly failed.\n");
        return NULL;
    }
    newPoly->resultant=NULL;
    newPoly->coefficient=1;
    newPoly->exponent=0;
    return newPoly;
}
Trig *createTrig()
{
    Trig *newTrig;
    newTrig=(Trig *)malloc(sizeof(Trig));
    if(newTrig==NULL)
    {
        printf("Memory allocation for a new Trig failed.\n");
        return NULL;
    }
    newTrig->exponent=NULL;
    newTrig->resultant=NULL;
    newTrig->coefficient=1;
    return newTrig;
}
Log *createLog()
{
    Log *newLog;
    newLog=(Log *)malloc(sizeof(Log));
    if(newLog==NULL)
    {
        printf("Memory allocation for a new Log failed.\n");
        return NULL;
    }
    newLog->base=NULL;
    newLog->resultant=NULL;
    newLog->coefficient=1;
    return newLog;
}
Arc *createArc()
{
    Arc *newArc;
    newArc=(Arc *)malloc(sizeof(Arc));
    if(newArc==NULL)
    {
        printf("Memory allocation for a new Arc failed.\n");
        return NULL;
    }
    newArc->exponent=NULL;
    newArc->resultant=NULL;
    newArc->coefficient=1;
    return newArc;
}
Exp *createExp()
{
    Exp *newExp;
    newExp=(Exp *)malloc(sizeof(Exp));
    if(newExp==NULL)
    {
        printf("Memory allocation for a new Exp failed.\n");
        return NULL;
    }
    newExp->exponent=NULL;
    newExp->base=NULL;
    return newExp;
}
Fact *createFact()
{
    Fact *newFact;
    newFact=(Fact *)malloc(sizeof(Fact));
    if(newFact==NULL)
    {
        printf("Memory allocation for a new Fact failed.\n");
        return NULL;
    }
    newFact->function=NULL;
    newFact->op=MULTIPLY;
    newFact->next=NULL;
    return newFact;
}
