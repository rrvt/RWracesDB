// Count Responders


#include "stdafx.h"
#include "CntResponders.h"
#include "Database.h"
#include "MbrSortList.h"
#include "NotePad.h"


static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };


void CntResponders::operator() () {
MbrLstIter iter(mbrSortList);
MbrItem*   item;
MbrRcd*    rcd;
AsnRcd*    asnRcd;
String     key;
String     dsc;
int        i;
int        counts[6];
int        total;

  notePad.clear();

  for (i = 0; i < noElements(counts); i++) counts[i] = 0;

  for (item = iter(); item; item = iter++) {
    if (!item->curMbr) continue;

    rcd = item->rcd;

    counts[getRspClass(rcd)]++;
    }

  notePad << nClrTabs << nSetRTab(72);

  for (i = 0, total = 0; i < noElements(counts); i++) {
    String k     = i < noElements(keys) ? keys[i] : _T("Nuts");

    asnRcd = asnTbl.find(k);
    dsc    = asnRcd ? asnRcd->txt : String(_T("Other"));

    notePad << dsc << nTab << counts[i] << nCrlf;    total += counts[i];
    }

  notePad << nTab << _T("------") << nCrlf;
  notePad << _T("   Total") << nTab << total << nCrlf;
  }


int CntResponders::getRspClass(MbrRcd* rcd) {
AsnRcd* asnRcd;
String  key;
int     i;

  asnRcd = asnTbl.find(rcd->assgnPrefID);   if (!asnRcd) return 5;

  key = asnRcd->aPKey;

  for (i = 0; i < noElements(keys); i++) if (key == keys[i]) break;

  return i;
  }



#if 1
//    i = getRspClass(rcd);
#else
    //    String responder = rcd->responder.trim();
    asnRcd = asnTbl.find(rcd->assgnPrefID);   if (!asnRcd) {counts[5]++; continue;}

    key = asnRcd->aPKey;

    for (i = 0; i < noElements(counts); i++)
                                      if (i >= noElements(keys) || key == keys[i]) {counts[i]++; break;}
#endif
//#include "RWracesDB.h"
//#include "RWracesDBView.h"




