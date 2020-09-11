// Entity Table Extension Template


#include "stdafx.h"
#include "EntityTbl.h"
#include "Utilities.h"


EntityRecord* EntityTbl::get(String& firstName, String& lastName, String& eMail,
                                                                        String& phone1, String& phone2) {
EntityRecord* r = find(firstName, lastName, eMail, phone1, phone2);   if (r) return r;
EntityRecord  rcd;

  rcd.FirstName = firstName; rcd.LastName = lastName; rcd.eMail = eMail;

  rcd.Phone1 = phone1; rcd.Phone2 = phone2;

  rcd.mark();  EntityTable::add(rcd);

  toDatabase();   return find(firstName, lastName, eMail, phone1, phone2);
  }


EntityRecord* EntityTbl::find(String& firstName, String& lastName, String& eMail,
                                                                        String& phone1, String& phone2) {
EntyIter      iter(*this);
EntityRecord* rcd;

  if (isEmpty(&firstName, &lastName, &eMail, &phone1, &phone2, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
    if (rcd->FirstName == firstName && rcd->LastName == lastName && rcd->eMail == eMail &&
                                              rcd->Phone1 == phone1 && rcd->Phone2 == phone2) return rcd;
  return 0;
  }

