// FCC List Report


#include "stdafx.h"
#include "FCClist.h"
#include "MemberTbl.h"
#include "NotePad.h"
#include "qsort.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"
#include "StatusTbl.h"




void FCClist::operator() () {
MbrIter                 iter(memberTbl);
MemberRcd*              rcd;
int                     i;
int                     nCallSigns;
Expandable<String, 128> callSigns;

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->statusID;
    StatusRcd* statusRcd = statusTbl.find(statusID);

    if (!statusRcd || statusRcd->abbreviation == _T("Fmr")) continue;

    callSigns += rcd->callSign;        //[callSigns.end()]
    }

  nCallSigns = callSigns.end();    qsort(&callSigns[0], &callSigns[nCallSigns-1]);

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

  for (i = 0; i < nCallSigns; i++) notePad << callSigns[i] << nCrlf;
  }




