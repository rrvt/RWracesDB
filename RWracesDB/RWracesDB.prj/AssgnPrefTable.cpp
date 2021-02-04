// AssgnPref Table Extension Template


#include "stdafx.h"
#include "AssgnPrefTable.h"
#include "Utilities.h"


AssgnPrefRecord* AssgnPrefTable::get(String& aPKey, String& txt) {
AssgnPrefRecord* r = find(aPKey, txt);   if (r) return r;
AssgnPrefRecord  rcd;

  rcd.APKey = aPKey; rcd.Txt = txt;  rcd.mark();  AssgnPrefMap::add(rcd);

  toDatabase();   return find(aPKey, txt);
  }


long AssgnPrefTable::add(TCchar* aPKey, TCchar* txt) {
String arg0 = aPKey;
String arg1 = txt;
long   id;

  if (arg0.isEmpty() && arg1.isEmpty()) return 0;

  id = findID(arg0, arg1);   if (id) return id;

  AssgnPrefRecord r;  r.APKey = arg0;  r.Txt = arg1;
  r.mark();   AssgnPrefMap::add(r);

  toDatabase();   return findID(arg0, arg1);
  }


long AssgnPrefTable::findID(String& key) {
AgPfIter         iter(*this);
AssgnPrefRecord* rcd;

  if (key.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->APKey == key) return rcd->AssgnPrefID;

  return 0;
  }

long AssgnPrefTable::findID(String& aPKey, String& txt) {
AssgnPrefRecord* rcd = find(aPKey, txt);
  return rcd ? rcd->AssgnPrefID : 0;
  }


AssgnPrefRecord* AssgnPrefTable::find(String& aPKey, String& txt) {
AgPfIter         iter(*this);
AssgnPrefRecord* rcd;

  if (isEmpty(&aPKey, &txt, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
    if (rcd->APKey == aPKey && rcd->Txt == txt) return rcd;

  return 0;
  }

