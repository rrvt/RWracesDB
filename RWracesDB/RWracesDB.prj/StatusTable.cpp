// Status Table Extension Template


#include "stdafx.h"
#include "StatusTable.h"
#include "Utilities.h"


StatusRecord* StatusTable::get(String& abbreviation, String& description) {
StatusRecord* r = find(abbreviation, description);   if (r) return r;
StatusRecord  rcd;

  rcd.Abbreviation = abbreviation; rcd.Description = description;  rcd.mark();  StatusMap::add(rcd);

  toDatabase();   return find(abbreviation, description);
  }


long StatusTable::add(TCchar* abbreviation, TCchar* description) {
String arg0 = abbreviation;
String arg1 = description;
long   id;

  if (arg0.isEmpty() && arg1.isEmpty()) return 0;

  id = findID(arg0, arg1);   if (id) return id;

  StatusRecord r;  r.Abbreviation = arg0;  r.Description = arg1;
  r.mark();   StatusMap::add(r);

  toDatabase();   return findID(arg0, arg1);
  }


long StatusTable::findID(String& key) {
SttsIter      iter(*this);
StatusRecord* rcd;

  if (key.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->Abbreviation == key) return rcd->StsID;

  return 0;
  }

long StatusTable::findID(String& abbreviation, String& description) {
StatusRecord* rcd = find(abbreviation, description);
  return rcd ? rcd->StsID : 0;
  }


StatusRecord* StatusTable::find(String& abbreviation, String& description) {
SttsIter      iter(*this);
StatusRecord* rcd;

  if (isEmpty(&abbreviation, &description, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
    if (rcd->Abbreviation == abbreviation && rcd->Description == description) return rcd;

  return 0;
  }

