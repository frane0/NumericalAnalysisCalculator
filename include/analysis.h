#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "term.h"

void analyzePoly(Poly *,char *);
void analyzeTrig(Trig *,char *);
void analyzeLog(Log *,char *);
void analyzeArc(Arc *,char *);
void analyzeExp(Exp *,char *);
void analyzeFact(Fact *,char *);

#endif
