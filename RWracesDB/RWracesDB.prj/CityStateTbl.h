// CityState Table Extension Template


#pragma once
#include "CityStateMap.h"


class CityStateTbl : public CityStateTable {

public:

  CityStateTbl() : CityStateTable() {}

  CityStateRecord* get(String& city, String& state, String& zip);

  CityStateRecord* find(const long key) {CtySIter iter(*this); return iter.find(key);}

private:

  CityStateRecord* find(String& city, String& state, String& zip);
  };

