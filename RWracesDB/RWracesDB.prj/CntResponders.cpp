// Count Responders


#include "stdafx.h"
#include "CntResponders.h"
#include "MapData.h"
#include "NotePad.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"




static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };


void CntResponders::operator() () {
MmbrIter         iter(memberTable);
MemberRecord*    rcd;
int              assgnPrefID;
AssgnPrefRecord* assgnPrefRcd;
String           key;
String           dsc;
int              i;
int              counts[6];
int              total;

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

  for (i = 0; i < noElements(counts); i++) counts[i] = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);
    String        responder = rcd->Responder.trim();

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    assgnPrefID  = rcd->AssgnPrefID;
    assgnPrefRcd = assgnPrefTable.find(assgnPrefID);
    if (!assgnPrefRcd) {counts[5]++; continue;}

    key = assgnPrefRcd->APKey;

    for (i = 0; i < noElements(counts); i++) {
      if (i >= noElements(keys) || key == keys[i]) {counts[i]++; break;}
      }
    }

  notePad << nSetRTab(72);   total = 0;

  for (i = 0; i < noElements(counts); i++) {
    String k     = i < noElements(keys) ? keys[i] : _T("Nuts");
    assgnPrefRcd = assgnPrefTable.find(assgnPrefTable.findID(k));
    dsc          = assgnPrefRcd ? assgnPrefRcd->Txt : _T("Other");

    notePad << dsc << nTab << counts[i] << nCrlf;    total += counts[i];
    }

  notePad << nTab << _T("------") << nCrlf;
  notePad << _T("   Total") << nTab << total << nCrlf;
  }

