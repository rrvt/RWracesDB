// Member Table Extension Template


#pragma once
#include "MemberMap.h"


class MemberTbl : public MemberTable {

public:

  MemberTbl() : MemberTable() {}

  MemberRecord* get(String& callSign);

  MemberRecord* find(const long key) {MmbrIter iter(*this); return iter.find(key);}

private:

  MemberRecord* find(String& callSign);
  };

