#ifndef TERM_H
#define TERM_H

typedef struct genericTerm{
    enum type{
        POLY, TRIG, LOG, ARC, EXP, FACT
    };
    Poly* P;
    Trig* T;
    Log*  L;
    Arc*  A;
    Exp*  E;
    Fact* F;
    struct genericTerm* next;
}Term;

typedef struct polynomial{
    double exponent;
    double coefficient;
    struct genericTerm* resultant;
}Poly;

typedef struct trigonometric{
    enum func{
        SIN, COS, TAN,
        COT, SEC, CSC
    };
    struct genericTerm* exponent;
    double coefficient;
    struct genericTerm* resultant;
}Trig;

typedef struct logarithmic{
    double coefficient;
    struct genericTerm* base;
    struct genericTerm* resultant;
}Log;

typedef struct inverseTrigonometric{
    enum func{
        ARCSIN, ARCCOS, ARCTAN,
        ARCCOT, ARCSEC, ARCCSC
    };
    struct genericTerm* exponent;
    double coefficient;
    struct genericTerm* resultant;
}Arc;

typedef struct exponential{
    struct genericTerm* exponent;
    struct genericTerm* base;
}Exp;

typedef struct factor{
    enum op{
        MULTIPLY, DIVIDE
    };
    struct genericTerm* function;
    struct factor* next;
}Fact;

Term *createTerm(void);
Poly *createPoly(void);
Trig *createTrig(void);
Log *createLog(void);
Arc *createArc(void);
Exp *createExp(void);
Fact *createFact(void);

#endif
