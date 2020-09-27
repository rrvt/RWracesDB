// CityState Table Extension


#include "stdafx.h"
#include "CityStateTbl.h"
#include "Utilities.h"


CityStateRecord* CityStateTbl::get(String& city, String& state, String& zip) {
CityStateRecord* r = find(city, state, zip);     if (r) return r;
CityStateRecord  rcd;

  rcd.City = city;    rcd.State = state;    rcd.Zip = zip;    rcd.mark();  CityStateTable::add(rcd);

  toDatabase();   return find(city, state, zip);
  }


CityStateRecord* CityStateTbl::find(String& city, String& state, String& zip) {
CtySIter         iter(*this);
CityStateRecord* rcd;

  if (isEmpty(&city, &state, &zip, 0)) return 0;

  if (!state || !*state) state = _T("CA");

  String zp = zip;   zp = sanitizeZip(zp);

  for (rcd = iter(); rcd; rcd = iter++)
                              if (rcd->City == city && rcd->State == state && rcd->Zip == zp) return rcd;
  return 0;
  }


