// LocationPref Table Extension Template


#include "stdafx.h"
#include "LocationPrefTable.h"
#include "Utilities.h"


LocationPrefRecord* LocationPrefTable::get(String& key, String& txt) {
LocationPrefRecord* r = find(key, txt);   if (r) return r;
LocationPrefRecord  rcd;

  rcd.Key = key; rcd.Txt = txt;  rcd.mark();  LocationPrefMap::add(rcd);

  toDatabase();   return find(key, txt);
  }


long LocationPrefTable::add(TCchar* key, TCchar* txt) {
String arg0 = key;
String arg1 = txt;
long   id;

  if (arg0.isEmpty() && arg1.isEmpty()) return 0;

  id = findID(arg0, arg1);   if (id) return id;

  LocationPrefRecord r;  r.Key = arg0;  r.Txt = arg1;
  r.mark();   LocationPrefMap::add(r);

  toDatabase();   return findID(arg0, arg1);
  }


long LocationPrefTable::findID(String& key) {
LcPfIter            iter(*this);
LocationPrefRecord* rcd;

  if (key.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->Key == key) return rcd->LocationPrefID;

  return 0;
  }

long LocationPrefTable::findID(String& key, String& txt) {
LocationPrefRecord* rcd = find(key, txt);
  return rcd ? rcd->LocationPrefID : 0;
  }


LocationPrefRecord* LocationPrefTable::find(String& key, String& txt) {
LcPfIter            iter(*this);
LocationPrefRecord* rcd;

  if (isEmpty(&key, &txt, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
    if (rcd->Key == key && rcd->Txt == txt) return rcd;

  return 0;
  }

