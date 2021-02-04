// Entity Table Extension Template


#include "stdafx.h"
#include "EntityTable.h"
#include "Utilities.h"


EntityRecord* EntityTable::get(String& firstName, String& lastName, String& eMail, String& phone1, String& phone2) {
EntityRecord* r = find(firstName, lastName, eMail, phone1, phone2);   if (r) return r;
EntityRecord  rcd;

  rcd.FirstName = firstName; rcd.LastName = lastName; rcd.eMail = eMail; rcd.Phone1 = phone1; rcd.Phone2 = phone2;
  rcd.mark();  EntityMap::add(rcd);

  toDatabase();   return find(firstName, lastName, eMail, phone1, phone2);
  }


long EntityTable::findID(String& key) {
EntyIter      iter(*this);
EntityRecord* rcd;

  if (key.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->FirstName == key) return rcd->EntityID;

  return 0;
  }

long EntityTable::findID(String& firstName, String& lastName, String& eMail, String& phone1, String& phone2) {
EntityRecord* rcd = find(firstName, lastName, eMail, phone1, phone2);
  return rcd ? rcd->EntityID : 0;
  }


EntityRecord* EntityTable::find(String& firstName, String& lastName, String& eMail, String& phone1, String& phone2) {
EntyIter      iter(*this);
EntityRecord* rcd;

  if (isEmpty(&firstName, &lastName, &eMail, &phone1, &phone2, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
    if (rcd->FirstName == firstName && rcd->LastName == lastName && rcd->eMail == eMail && rcd->Phone1 == phone1 && rcd->Phone2 == phone2) return rcd;

  return 0;
  }

