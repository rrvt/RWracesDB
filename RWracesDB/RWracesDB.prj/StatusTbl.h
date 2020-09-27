// Status Table Extension Template


#pragma once
#include "StatusMap.h"


class StatusTbl : public StatusTable {

public:

  StatusTbl() : StatusTable() {}

  StatusRecord* get(String& abbreviation, String& description);

  StatusRecord* find(const long key) {SttsIter iter(*this); return iter.find(key);}

  long          add(String& key, String& dsc);

  long          findID(String& abbr) {StatusRecord* rcd = find(abbr);  return rcd ? rcd->StsID : 0;}
  const String& findAbbr(const long key);

  void          FixedInit();

private:

  StatusRecord* find(String& abbr);
  StatusRecord* find(String& abbreviation, String& description);
  };

