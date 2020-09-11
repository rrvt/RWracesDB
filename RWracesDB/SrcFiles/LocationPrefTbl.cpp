// LocationPref Table Extension Template


#include "stdafx.h"
#include "LocationPrefTbl.h"
#include "Utilities.h"


LocationPrefRecord* LocationPrefTbl::get(String& key, String& txt) {
LocationPrefRecord* r = find(key, txt);   if (r) return r;
LocationPrefRecord  rcd;

  rcd.Key = key;    rcd.Txt = txt;    rcd.mark();  LocationPrefTable::add(rcd);

  toDatabase();   return find(key, txt);
  }


LocationPrefRecord* LocationPrefTbl::find(String& key, String& txt) {
LcPfIter            iter(*this);
LocationPrefRecord* rcd;

  if (isEmpty(&key, &txt, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->Key == key && rcd->Txt == txt) return rcd;

  return 0;
  }


struct Status {
TCchar* key;
TCchar* desc;
};


Status locPref[5]    = {{_T("A"), _T("Available to be dispatched anywhere needed")},
                        {_T("5"), _T("Available to be dispatched within 5 miles of location")},
                        {_T("1"), _T("Available to be dispatched within 1 mile of location")},
                        {_T("N"), _T("Available to accept assignments in neighborhood")},
                        {_T("O"), _T("Not available for RACES dispatch.")}
                        };




void LocationPrefTbl::FixedInit() {
int i;

  for (i = 0; i < noElements(locPref); i++) {
    Status& itm = locPref[i];
    String  key = itm.key;
    String  dsc = itm.desc;       add(key,dsc);
    }
  }


long LocationPrefTbl::add(String& key, String& dsc) {
long id;

  if (key.isEmpty()) return 0;

  id = findID(key, dsc);   if (id) return id;

  LocationPrefRecord r; r.Key = key; r.Txt = dsc; r.mark();  LocationPrefTable::add(r);

  toDatabase();  return findID(key, dsc);
  }


