// AssgnPref Table Extension Template


#pragma once
#include "AssgnPrefMap.h"


class AssgnPrefTbl : public AssgnPrefTable {

public:

  AssgnPrefTbl() : AssgnPrefTable() {}

  AssgnPrefRecord* get(String& aPKey, String& txt);

  AssgnPrefRecord* find(const long key) {AgPfIter iter(*this); return iter.find(key);}

  long             add(String& key, String& dsc);

  void             FixedInit();
  long             findID(String key);
  long             findID(String& key, String& dsc)
                              {AssgnPrefRecord* rcd = find(key, dsc); return rcd ? rcd->AssgnPrefID : 0;}

private:

  AssgnPrefRecord* find(String& aPKey, String& txt);
  };

