// FCC List Report


#include "pch.h"
#include "FCClist.h"
#include "MbrSortList.h"
#include "MbrTbl.h"
#include "NotePad.h"


void FCClist::operator() () {
MbrLstIter              iter(mbrSortList);
MbrItem*                item;
int                     i;
Expandable<String, 128> data;

  for (item = iter(); item; item = iter++) if (item->curMbr) data = item->rcd->callSign;

  notePad.clear();

  for (i = 0; i < data.end(); i++) notePad << data[i] << nCrlf;
  }



//#include "Database.h"
//#include "qsort.h"
//#include "RWracesDB.h"
//#include "RWracesDBView.h"

