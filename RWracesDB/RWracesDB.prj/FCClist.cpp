// FCC List Report


#include "stdafx.h"
#include "FCClist.h"
#include "MapData.h"
#include "NotePad.h"
#include "qsort.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"




void FCClist::operator() () {
MmbrIter                iter(memberTable);
MemberRecord*           rcd;
int                     i;
int                     nCallSigns;
Expandable<String, 128> callSigns;

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    callSigns += rcd->CallSign;        //[callSigns.end()]
    }

  nCallSigns = callSigns.end();    qsort(&callSigns[0], &callSigns[nCallSigns-1]);

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

  for (i = 0; i < nCallSigns; i++) notePad << callSigns[i] << nCrlf;
  }




