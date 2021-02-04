// Member Table Extension Template


#include "stdafx.h"
#include "MemberTable.h"


MemberRecord* MemberTable::get(String& callSign) {
MemberRecord* r = find(callSign);   if (r) return r;
MemberRecord  rcd;

  rcd.CallSign = callSign;  rcd.mark();  MemberMap::add(rcd);

  toDatabase();   return find(callSign);
  }


long MemberTable::findID(String& key) {
MmbrIter      iter(*this);
MemberRecord* rcd;

  if (key.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->BadgeNumber == key) return rcd->MemberID;

  return 0;
  }


MemberRecord* MemberTable::find(String& callSign) {
MmbrIter      iter(*this);
MemberRecord* rcd;

  if (callSign.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
    if (rcd->CallSign == callSign) return rcd;

  return 0;
  }

