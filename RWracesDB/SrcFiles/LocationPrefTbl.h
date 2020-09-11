// LocationPref Table Extension Template


#pragma once
#include "LocationPrefMap.h"


class LocationPrefTbl : public LocationPrefTable {

public:

  LocationPrefTbl() : LocationPrefTable() {}

  LocationPrefRecord* get(String& key, String& txt);

  LocationPrefRecord* find(const long key) {LcPfIter iter(*this); return iter.find(key);}

  void                FixedInit();

  long                add(String& key, String& dsc);
  long                findID(String& key, String& dsc)
                        {LocationPrefRecord* rcd = find(key, dsc); return rcd ? rcd->LocationPrefID : 0;}

private:

  LocationPrefRecord* find(String& key, String& txt);
  };

