// Count Responders


#include "stdafx.h"
#include "CntResponders.h"
#include "AssgnPrefTbl.h"
#include "MemberTbl.h"
#include "NotePad.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"
#include "StatusTbl.h"




static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };


void CntResponders::operator() () {
MbrIter          iter(memberTbl);
MemberRcd*       rcd;
AssgnPrefRcd*    assgnPrefRcd;
String           key;
String           dsc;
int              i;
int              counts[6];
int              total;

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

  for (i = 0; i < noElements(counts); i++) counts[i] = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    StatusRcd* statusRcd = statusTbl.find(rcd->statusID);
    if (!statusRcd || statusRcd->abbreviation == _T("Fmr")) continue;

    String responder = rcd->responder.trim();

    assgnPrefRcd = assgnPrefTbl.find(rcd->assgnPrefID);   if (!assgnPrefRcd) {counts[5]++; continue;}

    key = assgnPrefRcd->apkey;

    for (i = 0; i < noElements(counts); i++)
                                      if (i >= noElements(keys) || key == keys[i]) {counts[i]++; break;}
    }

  notePad << nClrTabs << nSetRTab(72);

  for (i = 0, total = 0; i < noElements(counts); i++) {
    String k     = i < noElements(keys) ? keys[i] : _T("Nuts");
    assgnPrefRcd = assgnPrefTbl.find(k);
    dsc          = assgnPrefRcd ? assgnPrefRcd->txt : _T("Other");

    notePad << dsc << nTab << counts[i] << nCrlf;    total += counts[i];
    }

  notePad << nTab << _T("------") << nCrlf;
  notePad << _T("   Total") << nTab << total << nCrlf;
  }

