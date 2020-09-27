// Member Table Extension


#include "stdafx.h"
#include "MemberTbl.h"



MemberRecord* MemberTbl::get(String& callSign) {
MemberRecord* r = find(callSign);     if (r) return r;
MemberRecord  rcd;

  rcd.CallSign = callSign;  rcd.mark();  MemberTable::add(rcd);

  return find(callSign);                                      // toDatabase();
  }


MemberRecord* MemberTbl::find(String& callSign) {
MmbrIter      iter(*this);
MemberRecord* rcd;

  if (callSign.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->CallSign == callSign) return rcd;

  return 0;
  }

