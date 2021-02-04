// CityState Table Extension Template


#include "stdafx.h"
#include "CityStateTable.h"
#include "Utilities.h"


CityStateRecord* CityStateTable::get(String& city, String& state, String& zip) {
CityStateRecord* r = find(city, state, zip);   if (r) return r;
CityStateRecord  rcd;

  rcd.City = city; rcd.State = state; rcd.Zip = zip;
  rcd.mark();  CityStateMap::add(rcd);

  toDatabase();   return find(city, state, zip);
  }


long CityStateTable::add(TCchar* city, TCchar* state, TCchar* zip) {
String arg0 = city;
String arg1 = state;
String arg2 = zip;
long   id;

  if (arg0.isEmpty() && arg1.isEmpty() && arg2.isEmpty()) return 0;

  id = findID(arg0, arg1, arg2);   if (id) return id;

  CityStateRecord r;  r.City = arg0;  r.State = arg1;  r.Zip = arg2;
  r.mark();   CityStateMap::add(r);

  toDatabase();   return findID(arg0, arg1, arg2);
  }


long CityStateTable::findID(String& key) {
CtySIter         iter(*this);
CityStateRecord* rcd;

  if (key.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->City == key) return rcd->CityStateID;

  return 0;
  }

long CityStateTable::findID(String& city, String& state, String& zip) {
CityStateRecord* rcd = find(city, state, zip);
  return rcd ? rcd->CityStateID : 0;
  }


CityStateRecord* CityStateTable::find(String& city, String& state, String& zip) {
CtySIter         iter(*this);
CityStateRecord* rcd;

  if (isEmpty(&city, &state, &zip, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
    if (rcd->City == city && rcd->State == state && rcd->Zip == zip) return rcd;

  return 0;
  }

