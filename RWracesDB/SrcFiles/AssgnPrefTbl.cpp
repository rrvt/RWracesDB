// AssgnPref Table Extension


#include "stdafx.h"
#include "AssgnPrefTbl.h"
#include "Utilities.h"


struct Status {
TCchar* key;
TCchar* desc;
};

Status asnPref[6]    = {{_T("P"), _T("RACES is first call, ready to be dispatched immediately")},
                        {_T("E"), _T("RACES is second call, ready to be dispatched immediately")},
                        {_T("G"), _T("Will probably respond, may take some time to assemble equipment")},
                        {_T("A"), _T("ARES only")},
                        {_T("L"), _T("Last resort resource")},
                        {_T("O"), _T("Pending regained health")}
                        };


AssgnPrefRecord* AssgnPrefTbl::get(String& aPKey, String& txt) {
AssgnPrefRecord* r = find(aPKey, txt);   if (r) return r;
AssgnPrefRecord  rcd;

  rcd.APKey = aPKey;    rcd.Txt = txt;    rcd.mark();  AssgnPrefTable::add(rcd);

  toDatabase();   return find(aPKey, txt);
  }


AssgnPrefRecord* AssgnPrefTbl::find(String& aPKey, String& txt) {
AgPfIter         iter(*this);
AssgnPrefRecord* rcd;

  if (isEmpty(&aPKey, &txt, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->APKey == aPKey && rcd->Txt == txt) return rcd;
  return 0;
  }


long AssgnPrefTbl::findID(String key) {
AgPfIter         iter(*this);
AssgnPrefRecord* rcd;

  if (key.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->APKey == key) return rcd->AssgnPrefID;

  return 0;
  }



long AssgnPrefTbl::add(String& key, String& dsc) {
long id ;

  if (key.isEmpty()) return 0;

  id = findID(key, dsc);   if (id) return id;

  AssgnPrefRecord r;   r.APKey = key; r.Txt = dsc; r.mark();   AssgnPrefTable::add(r);

  toDatabase();   return findID(key, dsc);
  }


void AssgnPrefTbl::FixedInit() {
int i;

  for (i = 0; i < noElements(asnPref); i++) {
    Status& itm = asnPref[i];
    String  key = itm.key;
    String  dsc = itm.desc;     add(key, dsc);
    }
  }

