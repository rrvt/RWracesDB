// CityState Table Extension Template


#pragma once
#include "CityStateMap.h"


class CtySIter {

typedef CityStateMap::MyMap MyMap;
typedef MyMap::iterator     MyIter;

MyMap& myMap;
MyIter iter;

typedef pair<MyIter, bool> Pair;

public:

enum Dir {Fwd, Rev};

  CtySIter(CityStateMap& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  CityStateRecord* operator() (Dir rev = Fwd) {
    if (rev) {iter = myMap.end();   return decr();}
    else     {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    }

  CityStateRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  CityStateRecord* operator-- (int) {return decr();}

  CityStateRecord* current() {return iter == myMap.end() ? 0 : &iter->second;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isFirst() {return iter == myMap.begin();}

  void remove() {iter = myMap.erase(iter);}

private:

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  CityStateRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  CityStateRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  CtySIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator

  friend class CityStateMap;
  friend class CityStateTable;
  };


class CityStateTable : public CityStateMap {

public:

  CityStateTable() : CityStateMap() { }

  CityStateRecord* get(String& city, String& state, String& zip);

  CityStateRecord* find(const long key) {CtySIter iter(*this); return iter.find(key);}

  long add(TCchar* city, TCchar* state, TCchar* zip);
  bool add(CityStateRecord& rcd) {return CityStateMap::add(rcd);}

  long findID(String& key);
  long findID(String& city, String& state, String& zip);

  bool toDatabase() {return CityStateMap::toDatabase();}

private:

  CityStateRecord* find(String& city, String& state, String& zip);
  };
